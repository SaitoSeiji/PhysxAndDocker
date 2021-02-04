#pragma once
#include "IPhysxObjectCreator.h"
class StaticObjectCreator :
    public IPhysxObjectCreator
{
public:

    PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry,string key, bool isKinematic, const PxVec3& velocity = PxVec3(0)) override;
    PxRigidStatic* createStatic(const PxTransform& t, const PxGeometry& geometry,string key) override;
};

