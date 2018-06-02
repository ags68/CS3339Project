#ifndef HAZARD_DETECTION_UNIT_H
#define HAZARD_DETECTION_UNIT_H

void hazardDetectionUnit(
        int  IF_ID_RegisterRs,
        int  IF_ID_RegisterRt,
        int  ID_EX_RegisterRt,
        int  ID_EX_MemRead,
        bool &PCWrite,
        bool &IF_ID_Write,
        int  &ID_EX_RegMux
        );

#endif
