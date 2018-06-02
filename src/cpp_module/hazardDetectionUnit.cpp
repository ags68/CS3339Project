#include "hazardDetectionUnit.h"

void hazardDetectionUnit(
        int  IF_ID_RegisterRs,
        int  IF_ID_RegisterRt,
        int  ID_EX_RegisterRt,
        int  ID_EX_MemRead,
        bool &PCWrite,
        bool &IF_ID_Write,
        int  &ID_EX_RegMux
){
	
	if (ID_EX_MemRead && ((ID_EX_RegisterRt == IF_ID_RegisterRs) || (ID_EX_RegisterRt == IF_ID_RegisterRt)))		//now stalling
	{
		PCWrite = false;
		IF_ID_Write = false;
		ID_EX_RegMux = 1;
	}
	else																											//not stalling
	{
		PCWrite = true;
		IF_ID_Write = true;
		ID_EX_RegMux = 0;
	}
}