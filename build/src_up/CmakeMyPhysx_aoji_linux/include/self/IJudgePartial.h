#pragma once

#include "PxPhysicsAPI.h"
using namespace physx;
class IJudgePartial
{
public:
	//�ǂ̕�����Ԃɏ������邩�𔻒肷��
	virtual int JudgePartialSpaceNumber(PxVec3 pos) {
		return 0;
	}
};

