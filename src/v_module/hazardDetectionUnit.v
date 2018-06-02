module HazardDetectionUnit(IF_IDRegisterRs,IF_IDRegisterRt,ID_EXRegisterRt,ID_EXMemRead,PCWrite,IF_IDWrite,ID_EXRegMuxCon);
 input [4:0] IF_IDRegisterRs,IF_IDRegisterRt,ID_EXRegisterRt;
 input ID_EXMemRead;
 output PCWrite, IF_IDWrite, ID_EXRegMuxCon;

 reg PCWrite, IF_IDWrite, ID_EXRegMuxCon;

 always@(IF_IDRegisterRs,IF_IDRegisterRt,ID_EXRegisterRt,ID_EXMemRead)
 if(ID_EXMemRead&((ID_EXRegisterRt == IF_IDRegisterRs)|(ID_EXRegisterRt == IF_IDRegisterRt)))
 begin //stall
 PCWrite = 0;
 IF_IDWrite = 0;
 ID_EXRegMuxCon = 1;
 end
 else
 begin //don't stall
 PCWrite = 1;
 IF_IDWrite = 1;
 ID_EXRegMuxCon = 0;

 end
endmodule