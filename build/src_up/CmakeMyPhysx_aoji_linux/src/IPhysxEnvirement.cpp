#include "IPhysxEnvirement.h"

using namespace std;
//string IPhysxEnvirement::GetLog(int containerCount) {
//	stringstream ss;
//
//	auto dataHolderList = _physxObjectCreator->_dataHolderList;
//	if (containerCount == -1) {
//		for (int i = 0; i < dataHolderList.size(); i++) {
//			auto dataHolder = dataHolderList[i];
//			for (auto itr = dataHolder->_datalist.begin(); itr != dataHolder->_datalist.end(); ++itr) {
//				//�����Ńf�[�^�̏��������������肵�Ă��邪�A�{���͂����ƌ��߂���
//				//\n�@�f�[�^�u���b�N�̐؂�ځ@;�@�f�[�^�̂̐؂��
//				auto obj = itr->second;
//				auto tr = obj->_objectData->getGlobalPose().p;
//				auto qr = obj->_objectData->getGlobalPose().q;
//				ss << "container:" << i << ";";
//				ss << "label:" << itr->first << ";";
//				ss << "isDynamic:" << obj->_isDynamic << ";";
//				ss << "isKinematic:" << obj->_isKinematic << ";";
//				ss << "obj_tr:" << tr.x << "," << tr.y << "," << tr.z << ";";
//				ss << "obj_qr:" << qr.x << "," << qr.y << "," << qr.z << "," << qr.w << ";";
//				ss << "obj_geometory:" << obj->_geometoryInfo << ";" << "\n";
//			}
//		}
//	}
//	else {
//		if (containerCount >= dataHolderList.size())return "";
//		auto dataHolder = dataHolderList[containerCount];
//		for (auto itr = dataHolder->_datalist.begin(); itr != dataHolder->_datalist.end(); ++itr) {
//			//�����Ńf�[�^�̏��������������肵�Ă��邪�A�{���͂����ƌ��߂���
//			//\n�@�f�[�^�u���b�N�̐؂�ځ@;�@�f�[�^�̂̐؂��
//			auto obj = itr->second;
//			auto tr = obj->_objectData->getGlobalPose().p;
//			auto qr = obj->_objectData->getGlobalPose().q;
//			ss << "container:" << containerCount << ";";
//			ss << "label:" << itr->first << ";";
//			ss << "isDynamic:" << obj->_isDynamic << ";";
//			ss << "isKinematic:" << obj->_isKinematic << ";";
//			ss << "obj_tr:" << tr.x << "," << tr.y << "," << tr.z << ";";
//			ss << "obj_qr:" << qr.x << "," << qr.y << "," << qr.z << "," << qr.w << ";";
//			ss << "obj_geometory:" << obj->_geometoryInfo << ";" << "\n";
//		}
//	}
//
//
//	return ss.str();
//}

string IPhysxEnvirement::CreateLog(int serch,int send) {

	stringstream ss;
	auto dataHolderList = _physxObjectCreator->_dataHolderList;
	if (serch >= dataHolderList.size())return "";
	auto dataHolder = dataHolderList[serch];
	for (auto itr = dataHolder->_datalist.begin(); itr != dataHolder->_datalist.end(); ++itr) {
		//�����Ńf�[�^�̏��������������肵�Ă��邪�A�{���͂����ƌ��߂���
		//\n�@�f�[�^�u���b�N�̐؂�ځ@;�@�f�[�^�̂̐؂��
		auto obj = itr->second;
		auto tr = obj->_objectData->getGlobalPose().p;
		auto qr = obj->_objectData->getGlobalPose().q;
		ss << "container:" << send << ";";
		ss << "label:" << itr->first << ";";
		ss << "isDynamic:" << obj->_isDynamic << ";";
		ss << "isKinematic:" << obj->_isKinematic << ";";
		ss << "obj_tr:" << tr.x << "," << tr.y << "," << tr.z << ";";
		ss << "obj_qr:" << qr.x << "," << qr.y << "," << qr.z << "," << qr.w << ";";
		ss << "obj_geometory:" << obj->_geometoryInfo << ";" << "\n";
	}

	return ss.str();
}

//�f�[�^���󂯎���Ċ��ɔ��f
//��{�I��override���Ďg���̂Ńe���v���[�g�I�Ȃ���
//���擾���������؂�o������
void IPhysxEnvirement::ReflectData2Envirement() {
	if (_gScene == NULL)return;
	//vector<string> objectDataList= MyExtention::Split(reflect, '\n');
	//for (int i = 0; i < objectDataList.size(); i++) {
	//	vector<string> labelList = MyExtention::Split(objectDataList[i], ';');

	//	//label�̒��o
	//	string label = MyExtention::Split(labelList[1], ':')[1];
	//	if (_physxObjectCreator->FindObject(label, 0) != NULL) {
	//		continue;
	//	}
	//	else {
	//		cout << label << endl;
	//	}
	//	//IsDynamic�̒��o
	//	bool isDynamic = MyExtention::Split(labelList[2], ':')[1] == "1";
	//	//IsKinematic�̒��o
	//	bool isKinematic = MyExtention::Split(labelList[3], ':')[1] == "1";
	//	//transform�̒��o
	//	string trText = MyExtention::Split(labelList[4], ':')[1];
	//	vector<string> trValues = MyExtention::Split(trText, ',');
	//	PxVec3* pos = new PxVec3(stof( trValues[0]), stof(trValues[1]), stof(trValues[2]));

	//	//quatanion�̒��o
	//	string quatText = MyExtention::Split(labelList[5], ':')[1];
	//	vector<string> quatValues = MyExtention::Split(quatText, ',');
	//	PxQuat* quat = new PxQuat(stof(quatValues[0]), stof(quatValues[1]), stof(quatValues[2]), stof(quatValues[3]));

	//	//geometory
	//	string geoinfo= MyExtention::Split(labelList[6], ':')[1];

	//	if (isDynamic)_physxObjectCreator->createDynamic(PxTransform(*pos, *quat), *ObjectData_toHolder::ConvertText2Geometry(geoinfo),label,isKinematic);
	//	else _physxObjectCreator->createStatic(PxTransform(*pos, *quat), *ObjectData_toHolder::ConvertText2Geometry(geoinfo),label);

	//	//std::this_thread::sleep_for(std::chrono::milliseconds(1));//�d�����Ă߂�����҂��Ȃ��Ƃ����Ȃ��@�I�u�W�F�N�g�������@�����P�����玡���邩���H
	//}
	////cout <<"reflectData="<< _reflectData << endl;
}

void IPhysxEnvirement::InitPhysicsEnviourment()
{
}

void IPhysxEnvirement::UpdateEnviroment(float dt)
{
}

void IPhysxEnvirement::keyPress(unsigned char key, const PxTransform& camera)
{
}
//
//int IPhysxEnvirement::JudgePartialSpaceNumber(PxVec3 pos) {
//	return 0;
//}
