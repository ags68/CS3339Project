#include "ProcessorTestClass.h"

void ProcessorTestClass::IFstageTest(
        int PCInitial,
        int expInstr,
        int PCSrcInitial,
        int PCWriteInitial,
        int IF_IDWriteInitial,
        int IFFlushInitial,
        int targetAddrInitial,
        int &IF_ID_PC_initial,
        int &IF_ID_opCode_initial,
        int &IF_ID_registerRs_initial,
        int &IF_ID_registerRt_initial,
        int &IF_ID_registerRd_initial,
        int &IF_ID_shamt_initial,
        int &IF_ID_funct_initial,
        int &IF_ID_immediate_initial,
        int &PCFinal,
        int &IF_ID_PC_final,
        int &IF_ID_opCode_final,
        int &IF_ID_registerRs_final,
        int &IF_ID_registerRt_final,
        int &IF_ID_registerRd_final,
        int &IF_ID_shamt_final,
        int &IF_ID_funct_final,
        int &IF_ID_immediate_final
){
    // Initialize PC and control signals from ID stage
    PC         = PCInitial;
    PCSrc      = PCSrcInitial;
    PCWrite    = PCWriteInitial;
    IF_IDWrite = IF_IDWriteInitial;
    IFFlush    = IFFlushInitial;
    targetAddr = targetAddrInitial;

    // Initialize IF/ID register
    IF_ID_write.PC         = IF_ID_PC_initial;
    IF_ID_write.opCode     = IF_ID_opCode_initial;
    IF_ID_write.registerRs = IF_ID_registerRs_initial;
    IF_ID_write.registerRt = IF_ID_registerRt_initial;
    IF_ID_write.registerRd = IF_ID_registerRd_initial;
    IF_ID_write.shamt      = IF_ID_shamt_initial;
    IF_ID_write.funct      = IF_ID_funct_initial;
    IF_ID_write.immediate  = IF_ID_immediate_initial;

    // Load expected instruction in instruction address
    memoryUnit.write(PCInitial, expInstr);

    // Execute IF Stage
    IFstage();

    // Copy out updated PC
    PCFinal = PC;

    // Copy out IF/ID register
    IF_ID_PC_final         = IF_ID_write.PC;
    IF_ID_opCode_final     = IF_ID_write.opCode;
    IF_ID_registerRs_final = IF_ID_write.registerRs;
    IF_ID_registerRt_final = IF_ID_write.registerRt;
    IF_ID_registerRd_final = IF_ID_write.registerRd;
    IF_ID_shamt_final      = IF_ID_write.shamt;
    IF_ID_funct_final      = IF_ID_write.funct;
    IF_ID_immediate_final  = IF_ID_write.immediate;
}

void ProcessorTestClass::IDstageTest(
        int regRsVal,
        int regRtVal,
        int IF_ID_PC,
        int IF_ID_opCode,
        int IF_ID_registerRs,
        int IF_ID_registerRt,
        int IF_ID_registerRd,
        int IF_ID_shamt,
        int IF_ID_funct,
        int IF_ID_immediate,
        int ID_EX_memRead_initial,
        int ID_EX_registerRt_initial,
        int &ID_EX_regDst,
        int &ID_EX_aluOp,
        int &ID_EX_aluSrc,
        int &ID_EX_memtoReg,
        int &ID_EX_regWrite,
        int &ID_EX_memRead,
        int &ID_EX_memWrite,
        int &ID_EX_readData1,
        int &ID_EX_readData2,
        int &ID_EX_registerRs,
        int &ID_EX_registerRt,
        int &ID_EX_registerRd,
        int &ID_EX_shamt,
        int &ID_EX_funct,
        int &ID_EX_immediate,
        int &PCSrcVal,
        int &PCWriteVal,
        int &IF_IDWriteVal,
        int &IFFlushVal,
        int &targetAddrVal
){
    // Initialize IF/ID interstage register
    IF_ID_read.PC         = IF_ID_PC;
    IF_ID_read.opCode     = IF_ID_opCode;
    IF_ID_read.registerRs = IF_ID_registerRs;
    IF_ID_read.registerRt = IF_ID_registerRt;
    IF_ID_read.registerRd = IF_ID_registerRd;
    IF_ID_read.shamt      = IF_ID_shamt;
    IF_ID_read.funct      = IF_ID_funct;
    IF_ID_read.immediate  = IF_ID_immediate;

    // Initialize ID/EX interstage register
    ID_EX_read.memRead = ID_EX_memRead_initial;
    ID_EX_read.registerRt = ID_EX_registerRt_initial;

    // Write register values
    registerFile.write(IF_ID_registerRs, regRsVal);
    registerFile.write(IF_ID_registerRt, regRtVal);

    // Execute ID stage
    IDstage();

    // Copy out all ID/EX interstage register values
    ID_EX_regDst     = ID_EX_write.regDst;
    ID_EX_aluOp      = ID_EX_write.aluOp;
    ID_EX_aluSrc     = ID_EX_write.aluSrc;
    ID_EX_memtoReg   = ID_EX_write.memtoReg;
    ID_EX_regWrite   = ID_EX_write.regWrite;
    ID_EX_memRead    = ID_EX_write.memRead;
    ID_EX_memWrite   = ID_EX_write.memWrite;
    ID_EX_readData1  = ID_EX_write.readData1;
    ID_EX_readData2  = ID_EX_write.readData2;
    ID_EX_registerRs = ID_EX_write.registerRs;
    ID_EX_registerRt = ID_EX_write.registerRt;
    ID_EX_registerRd = ID_EX_write.registerRd;
    ID_EX_shamt      = ID_EX_write.shamt;
    ID_EX_funct      = ID_EX_write.funct;
    ID_EX_immediate  = ID_EX_write.immediate;

    // Copy out control wires from ID stage to IF stage
    PCSrcVal = PCSrc;
    PCWriteVal = PCWrite;
    IF_IDWriteVal = IF_IDWrite;
    IFFlushVal = IFFlush;
    targetAddrVal = targetAddr;
}

void ProcessorTestClass::EXstageTest(
        int ID_EX_regDst,
        int ID_EX_aluOp,
        int ID_EX_aluSrc,
        int ID_EX_memtoReg,
        int ID_EX_regWrite,
        int ID_EX_memRead,
        int ID_EX_memWrite,
        int ID_EX_readData1,
        int ID_EX_readData2,
        int ID_EX_registerRs,
        int ID_EX_registerRt,
        int ID_EX_registerRd,
        int ID_EX_shamt,
        int ID_EX_funct,
        int ID_EX_immediate,
        int EX_MEM_regWrite_initial,
        int EX_MEM_aluResult_initial,
        int EX_MEM_registerRd_initial,
        int MEM_WB_regWrite,
        int MEM_WB_registerRd,
        int &EX_MEM_regWrite,
        int &EX_MEM_memRead,
        int &EX_MEM_memtoReg,
        int &EX_MEM_memWrite,
        int &EX_MEM_zero,
        int &EX_MEM_aluResult,
        int &EX_MEM_readData2,
        int &EX_MEM_registerRd
){
    // Initialize ID/EX interstage register
    ID_EX_read.regDst     = ID_EX_regDst;
    ID_EX_read.aluOp      = ID_EX_aluOp;
    ID_EX_read.aluSrc     = ID_EX_aluSrc;
    ID_EX_read.memtoReg   = ID_EX_memtoReg;
    ID_EX_read.regWrite   = ID_EX_regWrite;
    ID_EX_read.memRead    = ID_EX_memRead;
    ID_EX_read.memWrite   = ID_EX_memWrite;
    ID_EX_read.readData1  = ID_EX_readData1;
    ID_EX_read.readData2  = ID_EX_readData2;
    ID_EX_read.registerRs = ID_EX_registerRs;
    ID_EX_read.registerRt = ID_EX_registerRt;
    ID_EX_read.registerRd = ID_EX_registerRd;
    ID_EX_read.shamt      = ID_EX_shamt;
    ID_EX_read.funct      = ID_EX_funct;
    ID_EX_read.immediate  = ID_EX_immediate;

    // Initialize relevant fields in EX/MEM interstage register
    EX_MEM_read.regWrite   = EX_MEM_regWrite_initial;
    EX_MEM_read.registerRd = EX_MEM_registerRd_initial;

    // Initialize relevant fields in MEM/WB interstage register
    MEM_WB_read.regWrite   = MEM_WB_regWrite;
    MEM_WB_read.registerRd = MEM_WB_registerRd;

    //Execute EX stage
    EXstage();

    // Copy out EX/MEM interstage register
    EX_MEM_regWrite   = EX_MEM_write.regWrite;
    EX_MEM_memRead    = EX_MEM_write.memRead;
    EX_MEM_memtoReg   = EX_MEM_write.memtoReg;
    EX_MEM_memWrite   = EX_MEM_write.memWrite;
    EX_MEM_zero       = EX_MEM_write.zero;
    EX_MEM_aluResult  = EX_MEM_write.aluResult;
    EX_MEM_readData2  = EX_MEM_write.readData2;
    EX_MEM_registerRd = EX_MEM_write.registerRd;
}

void ProcessorTestClass::MEMstageTest(
    int initialMemVal,
    int EX_MEM_regWrite,
    int EX_MEM_memRead, 
    int EX_MEM_memtoReg, 
    int EX_MEM_memWrite,
    int EX_MEM_zero,
    int EX_MEM_aluResult,
    int EX_MEM_readData2,
    int EX_MEM_registerRd,
    int &finalMemVal,
    int &MEM_WB_regWrite,
    int &MEM_WB_memtoReg,
    int &MEM_WB_readData,
    int &MEM_WB_aluResult,
    int &MEM_WB_registerRd
){

    // Initialize EX/MEM interstage register
    EX_MEM_read.regWrite   = EX_MEM_regWrite;
    EX_MEM_read.memRead    = EX_MEM_memRead; 
    EX_MEM_read.memtoReg   = EX_MEM_memtoReg; 
    EX_MEM_read.memWrite   = EX_MEM_memWrite;
    EX_MEM_read.zero       = EX_MEM_zero;
    EX_MEM_read.aluResult  = EX_MEM_aluResult;
    EX_MEM_read.readData2  = EX_MEM_readData2;
    EX_MEM_read.registerRd = EX_MEM_registerRd;

    // write initial memory value at alu result.
    memoryUnit.write(EX_MEM_aluResult, initialMemVal);

    // Execute MEM stage
    MEMstage();

    // read out memory value at alu result.
    memoryUnit.read(EX_MEM_aluResult, finalMemVal);

    // Copy out all MEM/WB register values
    MEM_WB_regWrite   = MEM_WB_write.regWrite;
    MEM_WB_memtoReg   = MEM_WB_write.memtoReg;
    MEM_WB_readData   = MEM_WB_write.readData;
    MEM_WB_aluResult  = MEM_WB_write.aluResult;
    MEM_WB_registerRd = MEM_WB_write.registerRd;
}

void ProcessorTestClass::WBstageTest(int initialRegVal, int regWrite, int memtoReg, int readData, int aluResult, int registerRd, int &finalRegVal){
    // Initialize register that may be written
    registerFile.write(registerRd, initialRegVal);

    // Set up MEM/WB register
    MEM_WB_read.regWrite = regWrite;
    MEM_WB_read.memtoReg = memtoReg;
    MEM_WB_read.readData = readData;
    MEM_WB_read.aluResult = aluResult;
    MEM_WB_read.registerRd = registerRd;

    // Execute WB stage
    WBstage();

    // Get final value of register
    int dummyVal = 0;
    registerFile.read(registerRd, 0, finalRegVal, dummyVal);
}