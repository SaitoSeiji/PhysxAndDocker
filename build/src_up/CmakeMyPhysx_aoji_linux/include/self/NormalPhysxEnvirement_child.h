#pragma once
#include "IPhysxEnvirement.h"
#include "WebSocketppFarcade.h"
class NormalPhysxEnvirement_child :
    public IPhysxEnvirement
{
	int length_x = 10;
	int height = 10;
	int length_z = 10;
	float _ballsize = 1.0f;
	PxRigidDynamic* moveWall = NULL;
	bool wallmoveFlag = false;
	bool isUp = true;
	float maxpos = -40;
	float minpos = -55;
	float wallSpeed = 10;
	float _ballSpeed = 100;

	int _containerCount = -1;//©•ª‚ª‰½”ÔƒRƒ“ƒeƒi‚È‚Ì‚©‚Ìî•ñ

	string _hashLog = "";

	string reflectData;
public:
	void InitPhysicsEnviourment() override;
	void UpdateEnviroment(float dt) override;
	void keyPress(unsigned char key, const PxTransform& camera) override;
	void ReflectData2Envirement() override;
	//int JudgePartialSpaceNumber(PxVec3 pos)override;
	void HashLogSet() override;
	void SetReflectData(string data) override {
		reflectData = data;
	}

	void CreateStack_ballpool(int lx, float height, int lz, float ballsize);
	void ChengeBallSpeed(float dv);
};

