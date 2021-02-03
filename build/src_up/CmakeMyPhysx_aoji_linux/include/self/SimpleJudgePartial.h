#pragma once
#include "IJudgePartial.h"
class SimpleJudgePartial :
    public IJudgePartial
{
public:
    int JudgePartialSpaceNumber(PxVec3 pos) override {
        int parialLine = 0;
        if (pos.x < parialLine)return 0;
        else return 1;
    }
};

