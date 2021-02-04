#pragma once
#include<iostream>
#include<fstream>
#include <GL/glut.h>
#include <vector>
#include<chrono>
#include "PxPhysicsAPI.h"
#include "Camera.h"
#include "RenderActor.h"
#include "FrameAction.h"
#include "CSVOutPutFactory.h"

using namespace std;
using namespace physx;
extern void initPhysics(bool init);
extern void stepPhysics(float dt);
extern void cleanupPhysics();
extern void keyPress(unsigned char key, const PxTransform& camera);
extern int GetObjectCount();
namespace {
	Camera* sCamera;
	bool _isRendering = true;
	void refreshRender();

	void motionCallback(int x, int y)
	{
		sCamera->handleMotion(x, y);
	}

	CSVOutPutFactory _outFactory;
	void keyboardCallback(unsigned char key, int x, int y)
	{
		if (key == 27) {
			_outFactory.OutPutCSV();
			cout << "output file\n";
			exit(0);
		}

		if (key == 'n') {
			_isRendering = !_isRendering;
			cout << "rendering:" << _isRendering<<"\n";
			if(!_isRendering)refreshRender();
		}

		if (!sCamera->handleKey(key, x, y)) {}
			keyPress(key, sCamera->getTransform());
	}
	void mouseCallback(int button, int state, int x, int y)
	{
		sCamera->handleMouse(button, state, x, y);
	}
	float _physicsTimeScale = 1.0f;//���܂������Ȃ��ꍇ��1�ɂ���
	FrameAction  _physcsFrameActor = FrameAction(1.0f / (50.0f));
	FrameAction _renderFrameActor= FrameAction(1.0f/30.0f);
	void idleCallback()
	{
		//�o�ߎ��Ԃ̍X�V
		_physcsFrameActor.Update();
		_renderFrameActor.Update();

		float idledt = _physcsFrameActor.GetProgressTime();
		cout << "idledt " << idledt << " sec" << "\n";
		//�t���[������
		
		if (_physcsFrameActor.IsOverFrameRate()) {
			auto start = chrono::system_clock::now();
			float dt = _physcsFrameActor.GetProgressTime();
			float stepDt = dt * _physicsTimeScale;
			_physcsFrameActor.Refresh();
			stepPhysics(stepDt);
			auto dur = chrono::system_clock::now()-start;
			auto misec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
			float sec = misec / 1000000.0f;
			_outFactory.Update("simulateTime", sec);
			_outFactory.Update("objectCount",GetObjectCount());
			//cout << "pSimulate: " << sec << ",interval: " << dt / _physicsTimeScale << "\n";
			//cout << GetObjectCount() << "\n";
			//cout << "pSimulate: " << sec << ",interval: " << dt / _physicsTimeScale << ": isOver:" << (sec > dt / _physicsTimeScale) << "\n";
			//cout << "pSimulate: " << sec << ",interval: " << dt / _physicsTimeScale << ": intervalOver:" << (0.03f<dt/_physicsTimeScale) << "\n";
			
			//cout<<  "physics simultare: " << sec << "sec\n";
			//cout << "coal interval    : " << dt << "sec" << "\n";
			//cout << "physcs_step " << dt << " sec" << "\n";
		}
		if (_renderFrameActor.IsOverFrameRate()) {
			//cout << "render_step " << _renderFrameActor.GetProgressTime() << " sec" << "\n";
			//auto start = chrono::system_clock::now();
			_renderFrameActor.Refresh();
			glutPostRedisplay();
			//auto end = chrono::system_clock::now();
			//auto dur = end - start;
			//auto msec = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
			//cout<<"render simultare: " << msec << "nano sec\n";
		}
	}

	void timerCallback(int militime) {
		cout << "timer collback\n";
		//stepPhysics(CalcDt());
		glutTimerFunc(500, timerCallback, 1);
	}
	void renderCallback() {
		if (!_isRendering)return;
		RenderActor::startRender(sCamera->getEye(), sCamera->getDir());
		PxScene* scene;
		PxGetPhysics().getScenes(&scene, 1);
		PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
		if (nbActors)
		{
			std::vector<PxRigidActor*> actors(nbActors);
			scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
			RenderActor::renderActors(&actors[0], static_cast<PxU32>(actors.size()), true);
		}
		RenderActor::finishRender();//�_�u���o�b�t�@�����O�����Ă�
	}
	//��ʂ���I�u�W�F�N�g������
	void refreshRender() {
		RenderActor::startRender(sCamera->getEye(), sCamera->getDir());
		RenderActor::finishRender();
	}
	void exitCallback(void)
	{
		delete sCamera;
		cleanupPhysics();
	}
}
void renderLoop() {
	cout << "test render\n";
	sCamera = new Camera(PxVec3(0.0f, 50.0f, 50.0f), PxVec3(0.0f, -0.1f, -0.7f));

	RenderActor::setupDefaultWindow("test");
	RenderActor::setupDefaultRenderState();

	_outFactory.AddDataSet("objectCount", 10);
	_outFactory.AddDataSet("simulateTime", 10);

	glutIdleFunc(idleCallback);
	glutDisplayFunc(renderCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);
	//glutTimerFunc(500, timerCallback, 1);
	motionCallback(0, 0);
	atexit(exitCallback);

	initPhysics(true);
	glutMainLoop();

}