#pragma once

#include "PxPhysicsAPI.h"
using namespace physx;
class IJudgePartial
{
public:
	//‚Ç‚Ì•”•ª‹óŠÔ‚ÉŠ‘®‚·‚é‚©‚ğ”»’è‚·‚é
	virtual int JudgePartialSpaceNumber(PxVec3 pos) {
		return 0;
	}
};

