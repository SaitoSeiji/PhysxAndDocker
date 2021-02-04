﻿#pragma once
#include<iostream>
#include<sstream>
#include"MyExtention.h"
#include "PxPhysicsAPI.h"
#include "IPhysxObjectCreator.h"
#include <thread>
#include <chrono>
#include<string>
#include <queue>
#include "IJudgePartial.h"

//class IPhysxObjectCreator;//循環参照対策　そのうち循環参照じたいをやめる

using namespace physx;
using namespace std;
 class IPhysxEnvirement
{
protected:
	//queue< string >_reflectData;//受け取ったシーンのデータを保管する変数
	PxScene* _gScene = NULL;
	IPhysxObjectCreator* _physxObjectCreator=NULL;
	//ObjectDataHolder* _dataHolder = NULL;

	//string GetLog(int containercount);
	string CreateLog(int serchContainer,int sendContainer);

public:
	IPhysxEnvirement(){}
	virtual void InitPhysicsEnviourment();
	virtual void UpdateEnviroment(float dt);
	virtual void keyPress(unsigned char key, const PxTransform& camera);

	void SetScene(PxScene& gScene) {
		_gScene = &gScene;
	}
	void SetObjectCreator(IPhysxObjectCreator& objCrtr) {
		_physxObjectCreator = &objCrtr;
	}

	 virtual void SetReflectData(string data) {
		 //_reflectData=data;

		 //while (_reflectData.size() > 4)_reflectData.pop();
	}

	//データを受け取って環境に反映
	virtual void ReflectData2Envirement();

	//どの部分空間に所属するかを判定する
	//virtual int JudgePartialSpaceNumber(PxVec3 pos);
	virtual IJudgePartial* GetJudgePartial() { return new IJudgePartial(); }


	//ログを前もって生成
	virtual void HashLogSet() {}
};

