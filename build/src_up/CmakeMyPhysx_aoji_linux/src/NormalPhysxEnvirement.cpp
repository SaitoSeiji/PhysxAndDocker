#include "NormalPhysxEnvirement.h"


void NormalPhysxEnvirement::CreateStack_ballpool(float xstart, float height,float zstart,int xCount,int zCount, float ballsize) {
    for (int x = 0; x < xCount; x++) {
        for (int z = 0; z < zCount; z++) {
            _physxObjectCreator->createDynamic(PxTransform((PxVec3(xstart,height,zstart)+PxVec3(x, height, z) * (ballsize + 1))), PxSphereGeometry(ballsize));
        }
    }
}

void NormalPhysxEnvirement::ChengeBallSpeed(float dv) {
    _ballSpeed += dv;
    if (_ballSpeed < 0)_ballSpeed = 0;
}

void NormalPhysxEnvirement::InitPhysicsEnviourment()
{

    WebSocketppFarcade::Send("host", 0);

    //moveWall = _physxObjectCreator->createDynamic(PxTransform(PxVec3(8, 0, -5)), PxBoxGeometry(16.0f, 40.0f, 1.0f), "moveWall", true);
    _physxObjectCreator->createDynamic(PxTransform(PxVec3(-42, 0, -55)), PxBoxGeometry(16.0f, 40.0f, 1.0f), "moveWall", true);
    _physxObjectCreator->createDynamic(PxTransform(PxVec3(-42, 0, -25)), PxBoxGeometry(16.0f, 40.0f, 1.0f), "", true);
    _physxObjectCreator->createDynamic(PxTransform(PxVec3(-25, 0, -43)), PxBoxGeometry(1.0f, 40.0f, 16.0f), "", true);
    _physxObjectCreator->createDynamic(PxTransform(PxVec3(-59, 0, -43)), PxBoxGeometry(1.0f, 40.0f, 16.0f), "", true);


    _physxObjectCreator->createDynamic(PxTransform(PxVec3(50, 0, -55)), PxBoxGeometry(16.0f, 40.0f, 1.0f), "moveWall", true);
    _physxObjectCreator->createDynamic(PxTransform(PxVec3(50, 0, -25)), PxBoxGeometry(16.0f, 40.0f, 1.0f), "", true);
    _physxObjectCreator->createDynamic(PxTransform(PxVec3(67, 0, -43)), PxBoxGeometry(1.0f, 40.0f, 16.0f), "", true);
    _physxObjectCreator->createDynamic(PxTransform(PxVec3(33, 0, -43)), PxBoxGeometry(1.0f, 40.0f, 16.0f), "", true);

    for (int i = 0; i < 10; i++) {
        CreateStack_ballpool(-50, height + i * _ballsize,-50,length_x, length_z, _ballsize);
    }
    for (int i = 0; i < 10; i++) {
        CreateStack_ballpool(42, height + i * _ballsize,-50, length_x, length_z, _ballsize);
    }
}

void NormalPhysxEnvirement::UpdateEnviroment(float dt)
{
    if (_connected) {//���U�������Ă����󂯎�鏈��

        _nowCharge += dt;
        if (_nowCharge > 0.1f) {
            if (isWaiting.size() > 0 && !isWaiting[targetClinet]) {
                isWaiting[targetClinet] = true;
                WebSocketppFarcade::Send("back", targetClinet);
            }
            targetClinet = (targetClinet == 0) ? 1 : 0;
            _nowCharge = 0;
        }

        //_nowCharge += dt;
        //if (_nowCharge > 0.3f) {
        //    WebSocketppFarcade::Send("back", targetClinet);
        //    targetClinet = (targetClinet == 0) ? 1 : 0;
        //    _nowCharge = 0;
        //}
    }
    else if(_connectWait) {
        _nowCharge += dt;
        if (_nowCharge > 1.0f) {
            if (isWaiting.size() > 0 ) {
                WebSocketppFarcade::Send("back", targetClinet);
            }
            targetClinet = (targetClinet == 0) ? 1 : 0;
            _nowCharge = 0;
        }
    }

    //if (!wallmoveFlag)return;
    //if (moveWall1 == NULL) {
    //    auto temp = _physxObjectCreator->FindObject("moveWall", 0);
    //    if (temp != NULL)moveWall1 = (PxRigidDynamic*)temp->_objectData;
    //    auto temp2 = _physxObjectCreator->FindObject("moveWall", 1);
    //    if (temp2 != NULL)moveWall2 = (PxRigidDynamic*)temp2->_objectData;
    //}
    //if (moveWall1 == NULL||moveWall2==NULL)return;

    //PxVec3 pos = moveWall1->getGlobalPose().p;
    //if (isUp && pos.z > maxpos)isUp = false;
    //else if (!isUp && pos.z < minpos)isUp = true;
    //float sign = (isUp) ? -1.0f : 1.0f;

    //PxTransform next_position1(moveWall1->getGlobalPose().p - PxVec3(0.0f, 0.0f, dt * wallSpeed * sign));//�ʒu�݂̂��w�肵�Ă��邪�A�p�x���w��ł����
    //moveWall1->setKinematicTarget(next_position1);
    //
    //PxTransform next_position2(moveWall2->getGlobalPose().p - PxVec3(0.0f, 0.0f, dt * wallSpeed * sign));//�ʒu�݂̂��w�肵�Ă��邪�A�p�x���w��ł����
    //moveWall2->setKinematicTarget(next_position2);
}


void NormalPhysxEnvirement::keyPress(unsigned char key, const PxTransform& camera)
{
    switch (toupper(key))
    {
    case ' ': {
        _physxObjectCreator->createDynamic(camera, PxBoxGeometry(2.0f, 2.0f, 2.0f),"",false, camera.rotate(PxVec3(-0.3f, 0, -1)) * _ballSpeed);
        break;
        }
    case 'Q':ChengeBallSpeed(10.0f); break;
    case 'E':ChengeBallSpeed(-5.0f); break;
    case 'B':
        CreateStack_ballpool(-50, height, -50, length_x, length_z, _ballsize);
        CreateStack_ballpool(42, height, -50, length_x, length_z, _ballsize);
        break;

    case 'V': {
        wallmoveFlag = !wallmoveFlag;
        stringstream ss;
        ss << "physx_input" << "," << "V" << "," << "0" << "," << "0";
        string command = ss.str();
        WebSocketppFarcade::Send(ss.str());
        break; 
        }
    case 'C': {
        stringstream ss;
        for (int i = 0;i< _physxObjectCreator->_dataHolderList.size(); i++) {
            ss << CreateLog(i, i);
        }
        cout << ss.str() << endl;
        break; }
    case 'X': {
        for (int i = 0; i < clientCount; i++) {
            stringstream ss;
            //string log = GetLog(i);
            string log = CreateLog(i, i);
            if (log == "")continue;
            ss << "envirement_objectdata," << log;
            WebSocketppFarcade::Send(ss.str(), i);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));//��C�ɑ���ƃG���[�f���̂ő҂��Ă�@�����R�[�h
            WebSocketppFarcade::Send("glut_init", i);
        }
        _connectWait = true;
        break; }
    case 'Z':
        //WebSocketppFarcade::Send("back", -1);
       /*for (int i=0; i <clientCount; i++) {

            WebSocketppFarcade::Send("back", i);
        }*/
        break;
    }
}
void NormalPhysxEnvirement::ReflectData2Envirement() {
    if (_gScene == NULL)return;

    //������������update�~�߂Ȃ��Ƃ��߂Ȃ̂Ŏ~�߂Ă�
    //PhysXFarcade::SetActive_update(false);
    //PhysXFarcade::SetActive_rendering(false); 
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));//������ƒ����@10���Ƃ��߂������@�����R�[�h�Ȃ̂Ŏ�������
    //for (int k = 0; k < _reflectData.size(); k++) {
    if (returnData.size() <= 0)return;
    for (int i = 0; i < returnData.size(); i++) {
        vector<string> objectDataList = MyExtention::Split(returnData[i], '\n');
        returnData[i] = "";
        for (int i = 0; i < objectDataList.size(); i++) {
            vector<string> labelList = MyExtention::Split(objectDataList[i], ';');
            if (labelList.size() != 7)break;
            //container�̒��o
            string container = MyExtention::Split(labelList[0], ':')[1];
            int containerCount = stoi(container);
            //label�̒��o
            string label = MyExtention::Split(labelList[1], ':')[1];

            //transform�̒��o
            string trText = MyExtention::Split(labelList[4], ':')[1];
            vector<string> trValues = MyExtention::Split(trText, ',');
            PxVec3* pos = new PxVec3(stof(trValues[0]), stof(trValues[1]), stof(trValues[2]));

            //quatanion�̒��o
            string quatText = MyExtention::Split(labelList[5], ':')[1];
            vector<string> quatValues = MyExtention::Split(quatText, ',');
            PxQuat* quat = new PxQuat(stof(quatValues[0]), stof(quatValues[1]), stof(quatValues[2]), stof(quatValues[3]));

            //�Ή�����I�u�W�F�N�g�̈ʒu�𔽉f
            auto targetObject = _physxObjectCreator->FindObject(label, containerCount);
            if (targetObject == NULL)continue;
            auto transform = targetObject->_objectData->getGlobalPose();
            transform.p = *pos;
            transform.q = *quat;
            targetObject->_objectData->setGlobalPose(transform);

            //std::this_thread::sleep_for(std::chrono::milliseconds(1));//�d�����Ă߂�����҂��Ȃ��Ƃ����Ȃ��@�I�u�W�F�N�g�������@�����P�����玡���邩���H
        }
    }
        //PhysXFarcade::SetActive_rendering(true);
        //PhysXFarcade::SetActive_update(true);
    //}
}
//int NormalPhysxEnvirement::JudgePartialSpaceNumber(PxVec3 pos) {
//    int parialLine = 0;
//    if (pos.x < parialLine)return 0;
//    else return 1;
//}

void NormalPhysxEnvirement::SetReflectData(string data) {
    if (returnData.size() == 0) {
        returnData.push_back("");
        returnData.push_back(""); 
        isWaiting.push_back(false);
        isWaiting.push_back(false);
    }

    vector<string> objectDataList = MyExtention::Split(data, '\n');

    vector<string> labelList = MyExtention::Split(objectDataList[0], ';');
    if (labelList.size() != 7)return;
    //container�̒��o
    string container = MyExtention::Split(labelList[0], ':')[1];
    int containerCount = stoi(container);
    returnData[containerCount] = data;
    cout << "returnData:" << containerCount;
    isWaiting[containerCount] = false;


    _connected = true;
}