#include "StaticObjectCreator.h"
#include<sstream>

PxRigidDynamic* StaticObjectCreator::createDynamic(const PxTransform& t, const PxGeometry& geometry,string key, bool isKinematic, const PxVec3& velocity)
{
    PxRigidDynamic* dynamic = PxCreateDynamic(*_gPhysics, t, geometry, *_gMaterial, 10.0f);
    dynamic->setAngularDamping(0.5f);
    dynamic->setLinearVelocity(velocity);
    _gScene->addActor(*dynamic);

    dynamic->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);//static‚É‚µ‚½‚©‚Á‚½‚¯‚Ç‘å•Ï‚¾‚Á‚½‚©‚çkinematic‚É‚·‚é‚±‚Æ‚Å‘Î‰ž‚µ‚½
    
    AddObjectData(dynamic, _judegePartial->JudgePartialSpaceNumber(t.p), true, isKinematic, geometry, key);
    //AddObjectData(dynamic, _envirement->JudgePartialSpaceNumber(t.p), true,isKinematic,geometry,key);
    return dynamic;
}

PxRigidStatic* StaticObjectCreator::createStatic(const PxTransform& t, const PxGeometry& geometry,string key)
{
    PxRigidStatic* static_actor = PxCreateStatic(*_gPhysics, t, geometry, *_gMaterial);
    _gScene->addActor(*static_actor);
    AddObjectData(static_actor, _judegePartial->JudgePartialSpaceNumber(t.p), false, true, geometry, key);
    //AddObjectData(static_actor, _envirement->JudgePartialSpaceNumber(t.p), false,true,geometry,key);

    return static_actor;
}
