#pragma once

#include "PxPhysicsAPI.h"
using namespace physx;
class IJudgePartial
{
public:
	//どの部分空間に所属するかを判定する
	virtual int JudgePartialSpaceNumber(PxVec3 pos) {
		return 0;
	}
};

