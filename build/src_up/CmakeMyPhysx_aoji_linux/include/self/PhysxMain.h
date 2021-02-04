#pragma once
#include <iostream>
#include "PxPhysicsAPI.h"
#include "IPhysxEnvirement.h"
#include "IPhysxObjectCreator.h"
#include "IJudgePartial.h"

//class IPhysxEnvirement;//�z�Q�Ƒ΍�@���̂����z�Q�Ƃ���������߂�
//class IPhysxObjectCreator;//�z�Q�Ƒ΍�@���̂����z�Q�Ƃ���������߂�
using namespace physx;
namespace PhysxMain
{
	void InitPhysics(bool init);
	void KeyPress(unsigned char key, const PxTransform& camera);
	void StepPhysics(float dt);

	void SetPhysxEnvirement(IPhysxEnvirement& env);
	void SetObjectCreator(IPhysxObjectCreator& objc);
	void ReflectEnv(string input);
};

