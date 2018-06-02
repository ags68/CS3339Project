#include "processor.h"
#include "alu.h"
#include "aluControl.h"
#include "controlUnit.h"
#include "forwardingUnit.h"
#include "hazardDetectionUnit.h"
#include "mux.h"

void processor::load(int inst, int instAddr){
    // Load inst into memory location instAddr in Memory Unit
    memoryUnit.write(instAddr, inst);
}

void processor::readReg(int regNumber, int &regValue){
    int dummyVal = 0;
    registerFile.read(regNumber, 0, regValue, dummyVal);
}

void processor::clock(){
    // Update register structs here
    IF_ID_read = IF_ID_write;
    ID_EX_read =ID_EX_write;
    EX_MEM_read = EX_MEM_write;
    MEM_WB_read = MEM_WB_write;

    // WB first so registers are updated before they are read in ID stage.
    WBstage();
    // ID second so control lines are set for IF stage.
    IDstage();
    IFstage();
    EXstage();
    MEMstage();

}

void processor::IFstage(){
    // Fetch instruction from memory
    int instr = 0;
    memoryUnit.read(PC, instr);

    // Only write IF/ID register if IF_IDWrite asserted
    if(IF_IDWrite){
        // If IFFlush asserted, zero out IF/ID register
        if(IFFlush){
            IF_ID_write.PC          = 0;
            IF_ID_write.opCode      = 0;
            IF_ID_write.registerRs = 0;
            IF_ID_write.registerRt = 0;
            IF_ID_write.registerRd  = 0;
            IF_ID_write.shamt       = 0;
            IF_ID_write.funct       = 0;
            IF_ID_write.immediate   = 0;
            IF_ID_write.address     = 0;
        }
        // Otherwise, split out instruction into individual fields for use in ID stage.
        else{
            IF_ID_write.PC          = PC + 4;
            IF_ID_write.opCode      = (instr >> 26) & 0x3F;
            IF_ID_write.registerRs  = (instr >> 21) & 0x1F;
            IF_ID_write.registerRt  = (instr >> 16) & 0x1F;
            IF_ID_write.registerRd  = (instr >> 11) & 0x1F;
            IF_ID_write.shamt       = (instr >> 6) & 0x1F;
            IF_ID_write.funct       = instr & 0x3F;
            IF_ID_write.immediate   = instr & 0xFFFF;
            IF_ID_write.address     = instr & 0x03FFFFFF;
        }
    }

    // Update PC according to PCWrite and PCSrc
    if(PCWrite){
        PC = PCSrc ? targetAddr : PC +4;
    }

}

void processor::IDstage(){
    // Sign extend immediate value.
    if(IF_ID_read.immediate & 0x8000){
        ID_EX_write.immediate  = IF_ID_read.immediate | 0xFFFF0000;
    }
    else{
        ID_EX_write.immediate  = IF_ID_read.immediate;
    }

    // Decode opCode.
    int regDst, branch, memRead, memWrite, memtoReg, aluOp, aluSrc, regWrite, jump;
    regDst = branch = memRead = memWrite = memtoReg = aluOp = aluSrc = regWrite = jump = 0;
    controlUnit(IF_ID_read.opCode, regDst, branch, memRead, memWrite, memtoReg, aluOp, aluSrc, regWrite, jump);

    // Read reg file
    registerFile.read(IF_ID_read.registerRs, IF_ID_read.registerRt, ID_EX_write.readData1, ID_EX_write.readData2);

    // Detect hazards
    int ID_EX_RegMux = 0;
    hazardDetectionUnit(
        IF_ID_read.registerRs,
        IF_ID_read.registerRt,
        ID_EX_read.registerRt,
        ID_EX_read.memRead,
        PCWrite,
        IF_IDWrite,
        ID_EX_RegMux
        );

    // Flush control lines to EX stage if hazard detected
    mux_2x1(regDst, 0, ID_EX_RegMux, ID_EX_write.regDst);
    mux_2x1(regWrite, 0, ID_EX_RegMux, ID_EX_write.regWrite);
    mux_2x1(memRead, 0, ID_EX_RegMux, ID_EX_write.memRead);
    mux_2x1(memtoReg, 0, ID_EX_RegMux, ID_EX_write.memtoReg);
    mux_2x1(aluOp, 0, ID_EX_RegMux, ID_EX_write.aluOp);
    mux_2x1(memWrite, 0, ID_EX_RegMux, ID_EX_write.memWrite);
    mux_2x1(aluSrc, 0, ID_EX_RegMux, ID_EX_write.aluSrc);

    // Determine if branch and figure out target address
    const int jrFunct = 8;
    if(IF_ID_read.funct == jrFunct && IF_ID_read.opCode == 0){
        targetAddr = ID_EX_write.readData1;
        IFFlush = 1;
        ID_EX_write.regWrite = 0;
        PCSrc = 1;
    }
    else if(jump){
        // Multiply by four same as shift left by 2
        // Address space doesn't use top bits, so no need to get those from PC.
        targetAddr = IF_ID_read.address * 4;
        IFFlush = 1;
        PCSrc = 1;
    }
    else if(branch && ID_EX_write.readData1 == ID_EX_write.readData2){
        // Multiply by four same as shift left by 2
        targetAddr = IF_ID_read.PC + (ID_EX_write.immediate * 4);
        IFFlush = 1;
        PCSrc = 1;
    }
    else{
        IFFlush = 0;
        PCSrc = 0;
    }

    // Set pass through values in ID/EX register
    ID_EX_write.PC = IF_ID_read.PC;
    ID_EX_write.registerRs = IF_ID_read.registerRs;
    ID_EX_write.registerRt = IF_ID_read.registerRt;
    ID_EX_write.registerRd = IF_ID_read.registerRd;
    ID_EX_write.shamt      = IF_ID_read.shamt;
    ID_EX_write.funct      = IF_ID_read.funct;

}

void processor::EXstage(){
    
    //Variables needed for control unit and muxes.
    int forwardA, forwardB, upperMux, lowerMux, tertiaryMux;
    forwardingUnit(
    ID_EX_read.registerRs, ID_EX_read.registerRt, EX_MEM_read.regWrite, EX_MEM_read.registerRd,
    MEM_WB_read.registerRd, MEM_WB_read.regWrite, forwardA, forwardB);

    //Upper and lower mux code
    mux_3x1(ID_EX_read.readData1, WBData, EX_MEM_read.aluResult, forwardA, upperMux);
    mux_3x1(ID_EX_read.readData2, WBData, EX_MEM_read.aluResult, forwardB, lowerMux);
    mux_2x1(lowerMux, ID_EX_read.immediate,ID_EX_read.aluSrc, tertiaryMux);

    //Calling alu and storing it's output into a variable to pass later.
    int aluOutput, aluOperation;
    bool zeroBoolean = false;

    aluControl(ID_EX_read.aluOp, ID_EX_read.funct, aluOperation);
    alu(upperMux, tertiaryMux, aluOperation, zeroBoolean, aluOutput);

    //Forwarding alut results.
    EX_MEM_write.aluResult = aluOutput;
    EX_MEM_write.readData2 = lowerMux;

    //Mandatory forwarding
    EX_MEM_write.PC       = ID_EX_read.PC;
    EX_MEM_write.regWrite = ID_EX_read.regWrite;
    EX_MEM_write.memRead  = ID_EX_read.memRead;
    EX_MEM_write.memtoReg = ID_EX_read.memtoReg;
    EX_MEM_write.memWrite = ID_EX_read.memWrite;

    //Bottom-most MUX
    int dataToWrite = 0;
    mux_3x1(ID_EX_read.registerRt, ID_EX_read.registerRd, 31, ID_EX_read.regDst, dataToWrite);
    EX_MEM_write.registerRd = dataToWrite;
}

void processor::MEMstage(){

    // Read if memRead
    if(EX_MEM_read.memRead){
        memoryUnit.read(EX_MEM_read.aluResult, MEM_WB_write.readData);
    }

    // Write if memWrite
    if(EX_MEM_read.memWrite){
        memoryUnit.write(EX_MEM_read.aluResult, EX_MEM_read.readData2);
    }

    // Forward other values
    MEM_WB_write.PC         = EX_MEM_read.PC;
    MEM_WB_write.aluResult  = EX_MEM_read.aluResult;
    MEM_WB_write.regWrite   = EX_MEM_read.regWrite;
    MEM_WB_write.registerRd = EX_MEM_read.registerRd;
    MEM_WB_write.memtoReg   = EX_MEM_read.memtoReg;
}

void processor::WBstage(){

    // Select data to be written to register file
    mux_3x1(MEM_WB_read.aluResult, MEM_WB_read.readData, MEM_WB_read.PC, MEM_WB_read.memtoReg, WBData);
    // If regWrite is asserted, write data to register file.
    if(MEM_WB_read.regWrite){
        registerFile.write(MEM_WB_read.registerRd, WBData);
    }
}
