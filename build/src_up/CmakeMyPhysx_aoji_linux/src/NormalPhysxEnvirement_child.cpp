#include "NormalPhysxEnvirement_child.h"

void NormalPhysxEnvirement_child::CreateStack_ballpool(int lx, float height, int lz, float ballsize) {
    //for (int x = 0; x < lx; x++) {
    //    for (int z = 0; z < lz; z++) {
    //        _physxObjectCreator->createDynamic(PxTransform((PxVec3(x, height, z) * (ballsize + 1))), PxSphereGeometry(ballsize));
    //    }
    //}
}

void NormalPhysxEnvirement_child::ChengeBallSpeed(float dv) {
    _ballSpeed += dv;
    if (_ballSpeed < 0)_ballSpeed = 0;
}

void NormalPhysxEnvirement_child::InitPhysicsEnviourment()
{
    WebSocketppFarcade::SetBackMessage([&] {
        //������������update�~�߂Ȃ��Ƃ��߂Ȃ̂Ŏ~�߂Ă�
        string result = _hashLog;
        return result;
        });
    ReflectData2Envirement();
    HashLogSet();
}

void NormalPhysxEnvirement_child::UpdateEnviroment(float dt)
{
    if (!wallmoveFlag)return;
    if (moveWall == NULL) {
        auto temp = _physxObjectCreator->FindObject("moveWall", 0);
        if (temp != NULL)moveWall = (PxRigidDynamic*)temp->_objectData;
    }
    if (moveWall == NULL)return;
    PxVec3 pos = moveWall->getGlobalPose().p;
    if (isUp && pos.z > maxpos)isUp = false;
    else if (!isUp && pos.z < minpos)isUp = true;
    float sign = 0;
    sign = (isUp) ? -1.0f : 1.0f;
    PxTransform next_position(moveWall->getGlobalPose().p - PxVec3(0.0f, 0.0f, dt * wallSpeed * sign));//�ʒu�݂̂��w�肵�Ă��邪�A�p�x���w��ł����
    moveWall->setKinematicTarget(next_position);
}


void NormalPhysxEnvirement_child::keyPress(unsigned char key, const PxTransform& camera)
{
    switch (toupper(key))
    {
    case ' ': {
        //_physxObjectCreator->createDynamic_inPlay(camera, PxBoxGeometry(2.0f, 2.0f, 2.0f), camera.rotate(PxVec3(-0.3f, 0, -1)) * _ballSpeed);
        _physxObjectCreator->createDynamic(camera, PxBoxGeometry(2.0f, 2.0f, 2.0f),"", false, camera.rotate(PxVec3(-0.3f, 0, -1)) * _ballSpeed);
        break;
    }
    case 'Q':ChengeBallSpeed(10.0f); break;
    case 'E':ChengeBallSpeed(-5.0f); break;
    case 'B':
        //CreateStack_ballpool(length_x, height, length_z, _ballsize);
        break;
    case 'X':
        wallmoveFlag = !wallmoveFlag;
        break;
    }
}

void NormalPhysxEnvirement_child::ReflectData2Envirement()
{
    if (_gScene == NULL)return;



    vector<string> objectDataList = MyExtention::Split(reflectData, '\n');
    for (int i = 0; i < objectDataList.size(); i++) {
        vector<string> labelList = MyExtention::Split(objectDataList[i], ';');

        //container�̒��o
        string container= MyExtention::Split(labelList[0], ':')[1];
        _containerCount = stoi(container);
        //label�̒��o
        string label = MyExtention::Split(labelList[1], ':')[1];
        if (_physxObjectCreator->FindObject(label, 0) != NULL) {
            continue;
        }
        else {
            cout << label << endl;
        }
        //IsDynamic�̒��o
        bool isDynamic = MyExtention::Split(labelList[2], ':')[1] == "1";
        //IsKinematic�̒��o
        bool isKinematic = MyExtention::Split(labelList[3], ':')[1] == "1";
        //transform�̒��o
        string trText = MyExtention::Split(labelList[4], ':')[1];
        vector<string> trValues = MyExtention::Split(trText, ',');
        PxVec3* pos = new PxVec3(stof(trValues[0]), stof(trValues[1]), stof(trValues[2]));

        //quatanion�̒��o
        string quatText = MyExtention::Split(labelList[5], ':')[1];
        vector<string> quatValues = MyExtention::Split(quatText, ',');
        PxQuat* quat = new PxQuat(stof(quatValues[0]), stof(quatValues[1]), stof(quatValues[2]), stof(quatValues[3]));

        //geometory
        string geoinfo = MyExtention::Split(labelList[6], ':')[1];

        if (isDynamic)_physxObjectCreator->createDynamic(PxTransform(*pos, *quat), *ObjectData_toHolder::ConvertText2Geometry(geoinfo), label, isKinematic);
        else _physxObjectCreator->createStatic(PxTransform(*pos, *quat), *ObjectData_toHolder::ConvertText2Geometry(geoinfo), label);

        //std::this_thread::sleep_for(std::chrono::milliseconds(1));//�d�����Ă߂�����҂��Ȃ��Ƃ����Ȃ��@�I�u�W�F�N�g�������@�����P�����玡���邩���H
    }

}

//int NormalPhysxEnvirement_child::JudgePartialSpaceNumber(PxVec3 pos) {
//    return 0;
//    /*int parialLine = 0;
//    if (pos.x > parialLine)return 0;
//    else return 1;*/
//}

void NormalPhysxEnvirement_child::HashLogSet() {
    _hashLog = CreateLog(0, _containerCount);
}