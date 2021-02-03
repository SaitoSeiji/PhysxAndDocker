#include "PhysXFarcade.h"
using namespace std;

//extern void initPhysics(bool init);
//extern void stepPhysics(float dt);
//extern void keyPress(unsigned char key, const PxTransform& camera);
namespace PhysXFarcade {
	Camera* _sCamera;
	FrameAction  _physcsFrameActor = FrameAction(1.0f / (50.0f));
	float _physicsTimeScale = 1.0f;//うまくいかない場合は1にする
	bool inited = false;
	bool _isActive_update = true;//trueならupdateの処理を行う
	bool _isActive_rendering = true;//trueならレンダリングの処理を行う
	//void Awake()
	//{
	//	//initPhysics(true);
	//}
	void Awake(IPhysxEnvirement& env, IPhysxObjectCreator& objc) {
		PhysxMain::SetPhysxEnvirement(env);
		PhysxMain::SetObjectCreator(objc);
		PhysxMain::InitPhysics(true);
		inited = true;
	}
	void Update()
	{
		if (!_isActive_update) {
			_physcsFrameActor.Refresh();
			return;
		}
		_physcsFrameActor.Update();

		float idledt = _physcsFrameActor.GetProgressTime();
		//cout << "idledt " << idledt << " sec" << "\n";
		//フレーム処理

		if (_physcsFrameActor.IsOverFrameRate()) {
			auto start = chrono::system_clock::now();
			float dt = _physcsFrameActor.GetProgressTime();
			float stepDt = dt * _physicsTimeScale;
			_physcsFrameActor.Refresh();
			PhysxMain::StepPhysics(stepDt);
			/*stepPhysics(stepDt);*/
			//auto dur = chrono::system_clock::now() - start;
			//auto misec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
			//float sec = misec / 1000000.0f;
			//_outFactory.Update("simulateTime", sec);
			//_outFactory.Update("objectCount", GetObjectCount());
			//cout << "pSimulate: " << sec << ",interval: " << dt / _physicsTimeScale << "\n";
			//cout << GetObjectCount() << "\n";
			//cout << "pSimulate: " << sec << ",interval: " << dt / _physicsTimeScale << ": isOver:" << (sec > dt / _physicsTimeScale) << "\n";
			//cout << "pSimulate: " << sec << ",interval: " << dt / _physicsTimeScale << ": intervalOver:" << (0.03f<dt/_physicsTimeScale) << "\n";

			//cout<<  "physics simultare: " << sec << "sec\n";
			//cout << "coal interval    : " << dt << "sec" << "\n";
			//cout << "physcs_step " << dt << " sec" << "\n";
		}
	}

	void RecieveInput(unsigned char input, int x, int y)
	{
		if (input == 27) {
			//cout << "output file\n";
			exit(0);
		}

		_sCamera->handleKey(input, x, y);
		//keyPress(input, _sCamera->getTransform());
		PhysxMain::KeyPress(input, _sCamera->getTransform());
	}

	void HandleMouse(int button, int state, int x, int y) {
		_sCamera->handleMouse(button, state, x, y);
	}

	void HandleMotion(int x, int y) {
		_sCamera->handleMotion(x, y);
	}

	void Rendering()
	{
		//if (!_isRendering)return;
		if (!_isActive_rendering)return;
		if (_sCamera == NULL)return;
		RenderActor::startRender(_sCamera->getEye(), _sCamera->getDir());
		PxScene* scene;
		PxGetPhysics().getScenes(&scene, 1);
		PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
		if (nbActors)
		{
			std::vector<PxRigidActor*> actors(nbActors);
			scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
			RenderActor::renderActors(&actors[0], static_cast<PxU32>(actors.size()), true);
		}
		RenderActor::finishRender();//ダブルバッファリングをしてる
	}


	void SetCamera(Camera* cam)
	{
		_sCamera = cam;
	}

	bool IsInited() {
		return inited;
	}


	void SetActive_update(bool flag) {
		//_isActive_update = flag;
	}
	void SetActive_rendering(bool flag) {
		//_isActive_rendering = flag;
	}
}