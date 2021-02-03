#include "MyPhysxController.h"
#include "MyExtention.h"
#include "GLUTCommandController.h"
#include<vector>
 #include <chrono>
 #include <thread>
#include "IPhysxEnvirement.h"
#include "NormalPhysxEnvirement.h"
#include "NormalPhysxEnvirement_child.h"
#include "IPhysxObjectCreator.h"
#include "StaticObjectCreator.h"
using namespace std;
namespace MyPhysxController {
	void MainLoop_switch(string input) {


		//�R�}���h�Ɗ֐��̑Ή��̍쐬
		string command_init_glut = "glut_init";
		string command_init_physx = "physx_init";
		string command_update = "physx_update";
		string command_input = "physx_input";
		string command_motion = "physx_motion";
		string command_mouse = "physx_mouse";
		string command_render = "physx_rendering";
		string command_env_objectData = "envirement_objectdata";

	
		OrderCommandRegister::AddCommand(command_update, PhysXFarcade::Update);
		OrderCommandRegister::AddCommand(command_render, PhysXFarcade::Rendering);
		OrderCommandRegister::AddCommand(command_input,
			[=](string input) {
				try {
					vector<string>vec = MyExtention::Split(input, ',');
					int x = stoi(vec[1]);
					int y = stoi(vec[2]);
					PhysXFarcade::RecieveInput(vec[0][0], x, y);
				}
				catch (exception) {
					cout << "input exception:command_input:input=" << input << endl;
				}
			}, 'd');
		OrderCommandRegister::AddCommand(command_motion,
			[=](string input) {
				try {
					vector<string>vec = MyExtention::Split(input, ',');
					int x = stoi(vec[0]);
					int y = stoi(vec[1]);
					PhysXFarcade::HandleMotion(x, y);
				}
				catch (exception) {
					cout << "input exception:command_motion:input=" << input << endl;
				}
			}, 'd');
		OrderCommandRegister::AddCommand(command_mouse,
			[=](string input) {
				try {
					vector<string>vec = MyExtention::Split(input, ',');
					int button = stoi(vec[0]);
					int state = stoi(vec[1]);
					int x = stoi(vec[2]);
					int y = stoi(vec[3]);
					PhysXFarcade::HandleMouse(button, state, x, y);
				}
				catch (exception) {
					cout << "input exception:command_mouse:input=" << input << endl;
				}
			}, 'd');

		//�X���b�h�Ȃǂ̊֌W��Enveirment�ɃA�N�Z�X�ł��Ȃ������̂ŁAIPhysxEnveirment�̊֐��𒼐ڎg�킸�APhysxMain�Ɋ֐�������čs���Ă���
		//���̂�����������
		OrderCommandRegister::AddCommand(command_env_objectData, [&](string input) {
			PhysxMain::ReflectEnv(input);
			}, 'd');
		//�R�}���h�Ăяo���̓o�^ �ǂ�����Ăяo�����ŏ���������===============================================================
		if (input.substr(0, 4) == "glut") {//glut���疽��

			OrderCommandRegister::AddCommand(command_init_physx, [&]() {
				PhysXFarcade::Awake(*new NormalPhysxEnvirement(), *new StaticObjectCreator());
				PhysXFarcade::SetCamera(GLUTCommandController::GetCamera());
				});


			//GLUT�ƃR�}���h�̑Ή��̍쐬
			GLUTCommandController::AddCallbacl_awake([=]() {
				OrderCommandRegister::RecieveCommand(command_init_physx);
				//WebSocketppFarcade::Send(command_init_glut);
				});
			GLUTCommandController::AddCallbacl_idle( [=]() {
				OrderCommandRegister::RecieveCommand(command_update);
				//WebSocketppFarcade::Send(command_update);
			});
			GLUTCommandController::AddCallbacl_render([=]() {
				OrderCommandRegister::RecieveCommand(command_render);
				//WebSocketppFarcade::Send(command_render);
			});
			GLUTCommandController::AddCallbacl_input([=](unsigned char c, int x, int y) {
				stringstream ss;
				ss << command_input << "," << c << "," << x << "," << y;
				string command = ss.str();
				OrderCommandRegister::RecieveCommand(command);
				//WebSocketppFarcade::Send(command);
			});
			GLUTCommandController::AddCallbacl_motion([=](int x, int y) {
				stringstream ss;
				ss << command_motion << "," << x << "," << y;
				string command = ss.str();
				OrderCommandRegister::RecieveCommand(command);
				//WebSocketppFarcade::Send(command);
			});
			GLUTCommandController::AddCallbacl_mouse([=](int button, int state, int x, int y) {
				stringstream ss;
				ss << command_mouse << "," << button << "," << state << "," << x << "," << y;
				string command = ss.str();
				OrderCommandRegister::RecieveCommand(command);
				//WebSocketppFarcade::Send(command);
			});
			//�ԓ��f�[�^�̏���
			WebSocketppFarcade::SetReplayMessage(PhysxMain::ReflectEnv);
			GLUTCommandController::StartDisplay("client",1000,100);

			/*std::thread th([] {GLUTCommandController::StartDisplay("client", 1000, 100); });
			th.detach();*/
			/*std::thread th(
				[] {GLUTCommandController::StartDisplay("client", 1000, 100); }
			);
			th.join();*/
		}
		else if (input.substr(0, 9) == "websocket") {//websocket���疽��

			OrderCommandRegister::AddCommand(command_init_physx, [&]() {//���̏�����
				PhysXFarcade::Awake(*new NormalPhysxEnvirement_child(), *new IPhysxObjectCreator());
				PhysXFarcade::SetCamera(GLUTCommandController::GetCamera());
				});
			//GLUT�ƃR�}���h�̑Ή��̍쐬
			GLUTCommandController::AddCallbacl_awake([=]() {

				OrderCommandRegister::RecieveCommand(command_init_physx);
			});
			GLUTCommandController::AddCallbacl_render([=]() {
				OrderCommandRegister::RecieveCommand(command_render);
			});

			GLUTCommandController::AddCallbacl_idle([=]() {
				OrderCommandRegister::RecieveCommand(command_update);
				});GLUTCommandController::AddCallbacl_input([=](unsigned char c, int x, int y) {
				stringstream ss;
				ss << command_input << "," << c << "," << x << "," << y;
				string command = ss.str();
				OrderCommandRegister::RecieveCommand(command);
				//WebSocketppFarcade::Send(command);
			});
			GLUTCommandController::AddCallbacl_motion([=](int x, int y) {
				stringstream ss;
				ss << command_motion << "," << x << "," << y;
				string command = ss.str();
				OrderCommandRegister::RecieveCommand(command);
				//WebSocketppFarcade::Send(command);
			});
			GLUTCommandController::AddCallbacl_mouse([=](int button, int state, int x, int y) {
				stringstream ss;
				ss << command_mouse << "," << button << "," << state << "," << x << "," << y;
				string command = ss.str();
				OrderCommandRegister::RecieveCommand(command);
				//WebSocketppFarcade::Send(command);
			}); 


			//webSocket�ő����Ă������b�Z�[�W���R�}���h�Ƃ��ČĂ�
			WebSocketppFarcade::SetRecieveMessage(OrderCommandRegister::RecieveCommand);

			//���������߂̎󂯎��
			OrderCommandRegister::AddCommand(command_init_glut, [] {
				//GLUTCommandController::StartDisplay("server");

				//StartDisplay����Ə������~�܂���serverListen�ł��Ȃ��Ȃ�̂ŕʃX���b�h�ŌĂ�ł���
				//�G�Ɏ��������̂ł��̂������ɂȂ肻��
				//���u���̕`��̓f�o�b�O�p�Ȃ̂ł���܂���Ȃ����ȁH

				if (PhysXFarcade::IsInited())return;
				std::thread th([] {GLUTCommandController::StartDisplay("server",100,100); });
				th.detach();
				});
		}
		else if (input.substr(0, 9) == "ws_offgui") {
			OrderCommandRegister::AddCommand(command_init_physx, [&]() {
				PhysXFarcade::Awake(*new NormalPhysxEnvirement(), *new IPhysxObjectCreator());
				PhysXFarcade::SetCamera(GLUTCommandController::GetCamera());
				});

			//GLUT�ƃR�}���h�̑Ή��̍쐬
			GLUTCommandController::AddCallbacl_awake([=]() {
				OrderCommandRegister::RecieveCommand(command_init_physx);
				});

			GLUTCommandController::AddCallbacl_idle([=]() {
				OrderCommandRegister::RecieveCommand(command_update);
				});
			//webSocket�ő����Ă������b�Z�[�W���R�}���h�Ƃ��ČĂ�
			WebSocketppFarcade::SetRecieveMessage(OrderCommandRegister::RecieveCommand);

			//���������߂̎󂯎��
			OrderCommandRegister::AddCommand(command_init_glut, [] {
				std::thread th([] {GLUTCommandController::StartDisplay_guiOff(); });
				th.detach();
				});
		}
	}
	//
	//void MainLoop_switch(string input) {

	//	GLUTCommandController glutCommandController;

	//	//�R�}���h�Ɗ֐��̑Ή��̍쐬
	//	string command_init_glut = "glut_init";
	//	string command_init_physx = "physx_init";
	//	string command_update = "physx_update";
	//	string command_input = "physx_input";
	//	string command_motion = "physx_motion";
	//	string command_mouse = "physx_mouse";
	//	string command_render = "physx_rendering";

	//	OrderCommandRegister::AddCommand(command_init_physx, [&]() {
	//		PhysXFarcade::Awake();
	//		PhysXFarcade::SetCamera(glutCommandController._sCamera);
	//		});
	//	OrderCommandRegister::AddCommand(command_update, PhysXFarcade::Update);
	//	OrderCommandRegister::AddCommand(command_render, PhysXFarcade::Rendering);
	//	OrderCommandRegister::AddCommand(command_input,
	//		[=](string input) {
	//			try {
	//				vector<string>vec = MyExtention::Split(input, ',');
	//				int x = stoi(vec[1]);
	//				int y = stoi(vec[2]);
	//				PhysXFarcade::RecieveInput(vec[0][0], x, y);
	//			}
	//			catch (exception) {
	//				cout << "input exception:command_input:input=" << input << endl;
	//			}
	//		}, 'd');
	//	OrderCommandRegister::AddCommand(command_motion,
	//		[=](string input) {
	//			try {
	//				vector<string>vec = MyExtention::Split(input, ',');
	//				int x = stoi(vec[0]);
	//				int y = stoi(vec[1]);
	//				PhysXFarcade::HandleMotion(x, y);
	//			}
	//			catch (exception) {
	//				cout << "input exception:command_motion:input=" << input << endl;
	//			}
	//		}, 'd');
	//	OrderCommandRegister::AddCommand(command_mouse,
	//		[=](string input) {
	//			try {
	//				vector<string>vec = MyExtention::Split(input, ',');
	//				int button = stoi(vec[0]);
	//				int state = stoi(vec[1]);
	//				int x = stoi(vec[2]);
	//				int y = stoi(vec[3]);
	//				PhysXFarcade::HandleMouse(button, state, x, y);
	//			}
	//			catch (exception) {
	//				cout << "input exception:command_mouse:input=" << input << endl;
	//			}
	//		}, 'd');

	//	//�R�}���h�Ăяo���̓o�^ �ǂ�����Ăяo�����ŏ���������
	//	if (input.substr(0, 4) == "glut") {
	//		//GLUT�ƃR�}���h�̑Ή��̍쐬
	//		glutCommandController._awakeCallback = [=]() {
	//			OrderCommandRegister::RecieveCommand(command_init_physx);
	//			WebSocketppFarcade::Send(command_init_glut);
	//		};
	//		glutCommandController._idleCallback = [=]() {
	//			OrderCommandRegister::RecieveCommand(command_update);
	//			//WebSocketppFarcade::Send(command_update);
	//		};
	//		glutCommandController._renderCallback = [=]() {
	//			OrderCommandRegister::RecieveCommand(command_render);
	//			//WebSocketppFarcade::Send(command_render);
	//		};
	//		glutCommandController._inputCallback = [=](unsigned char c, int x, int y) {
	//			stringstream ss;
	//			ss << command_input << "," << c << "," << x << "," << y;
	//			string command = ss.str();
	//			OrderCommandRegister::RecieveCommand(command);
	//			//WebSocketppFarcade::Send(ss.str());
	//		};
	//		glutCommandController._motionCallback = [=](int x, int y) {
	//			stringstream ss;
	//			ss << command_motion << "," << x << "," << y;
	//			string command = ss.str();
	//			OrderCommandRegister::RecieveCommand(command);
	//			//WebSocketppFarcade::Send(ss.str());
	//		};
	//		glutCommandController._mouseCallback = [=](int button, int state, int x, int y) {
	//			stringstream ss;
	//			ss << command_mouse << "," << button << "," << state << "," << x << "," << y;
	//			string command = ss.str();
	//			OrderCommandRegister::RecieveCommand(command);
	//			//WebSocketppFarcade::Send(ss.str());
	//		};

	//		glutCommandController.StartDisplay("client");
	//	}
	//	else if (input.substr(0, 9) == "websocket") {

	//		//GLUT�ƃR�}���h�̑Ή��̍쐬
	//		glutCommandController._awakeCallback = [=]() {
	//			OrderCommandRegister::RecieveCommand(command_init_physx);
	//		};
	//		glutCommandController._renderCallback = [=]() {
	//			OrderCommandRegister::RecieveCommand(command_render);
	//		};
	//		//webSocket�ő����Ă������b�Z�[�W���R�}���h�Ƃ��ČĂ�
	//		WebSocketppFarcade::SetRecieveMessage(OrderCommandRegister::RecieveCommand);

	//		//���������߂̎󂯎��
	//		OrderCommandRegister::AddCommand(command_init_glut, [&] {
	//			glutCommandController.StartDisplay("server");
	//			});
	//	}
	//}

	//void MainLoop_client() {

	//	GLUTCommandController glutCommandController;

	//	//�R�}���h�Ɗ֐��̑Ή��̍쐬
	//	string command_init_glut = "glut_init";
	//	string command_init_physx = "physx_init";
	//	string command_update = "physx_update";
	//	string command_input = "physx_input";
	//	string command_motion = "physx_motion";
	//	string command_mouse = "physx_mouse";
	//	string command_render = "physx_rendering";
	//	OrderCommandRegister::AddCommand(command_init_physx, [&]() {
	//		PhysXFarcade::Awake();
	//		PhysXFarcade::SetCamera(glutCommandController._sCamera);
	//		});
	//	OrderCommandRegister::AddCommand(command_update, PhysXFarcade::Update);
	//	OrderCommandRegister::AddCommand(command_render, PhysXFarcade::Rendering);


	//	OrderCommandRegister::AddCommand(command_input,
	//		[=](string input) {
	//			try {
	//				vector<string>vec = MyExtention::Split(input, ',');
	//				int x = stoi(vec[1]);
	//				int y = stoi(vec[2]);
	//				PhysXFarcade::RecieveInput(vec[0][0], x, y);
	//			}
	//			catch (exception) {
	//				cout << "input exception:command_input:input="<<input << endl;
	//			}
	//		}, 'd');

	//	OrderCommandRegister::AddCommand(command_motion,
	//		[=](string input) {
	//			try {
	//				vector<string>vec = MyExtention::Split(input, ',');
	//				int x = stoi(vec[0]);
	//				int y = stoi(vec[1]);
	//				PhysXFarcade::HandleMotion(x, y);
	//			}
	//			catch (exception) {
	//				cout << "input exception:command_motion:input=" << input << endl;
	//			}
	//		}, 'd');
	//	OrderCommandRegister::AddCommand(command_mouse,
	//		[=](string input) {
	//			try {
	//				vector<string>vec = MyExtention::Split(input, ',');
	//				int button = stoi(vec[0]);
	//				int state = stoi(vec[1]);
	//				int x = stoi(vec[2]);
	//				int y = stoi(vec[3]);
	//				PhysXFarcade::HandleMouse(button,state,x, y);
	//			}
	//			catch (exception) {
	//				cout << "input exception:command_mouse:input=" << input << endl;
	//			}
	//		}, 'd');

	//	//GLUT�ƃR�}���h�̑Ή��̍쐬
	//	glutCommandController._awakeCallback = [=]() { 
	//		OrderCommandRegister::RecieveCommand(command_init_physx);
	//		//WebSocketppFarcade::Send(command_init_glut);
	//	};
	//	glutCommandController._idleCallback = [=]() { 
	//		OrderCommandRegister::RecieveCommand(command_update); 
	//		//WebSocketppFarcade::Send(command_update);
	//	};
	//	glutCommandController._renderCallback = [=]() {
	//		OrderCommandRegister::RecieveCommand(command_render);
	//		//WebSocketppFarcade::Send(command_render);
	//	};
	//	glutCommandController._inputCallback = [=](unsigned char c, int x, int y) {
	//		stringstream ss;
	//		ss << command_input << "," << c << "," << x << "," << y;
	//		string command = ss.str();
	//		OrderCommandRegister::RecieveCommand(command);
	//		//WebSocketppFarcade::Send(ss.str());
	//	};
	//	glutCommandController._motionCallback = [=](int x, int y) {
	//		stringstream ss;
	//		ss << command_motion << "," << x << "," << y;
	//		string command = ss.str();
	//		OrderCommandRegister::RecieveCommand(command);
	//		//WebSocketppFarcade::Send(ss.str());
	//	};
	//	glutCommandController._mouseCallback = [=](int button,int state,int x, int y) {
	//		stringstream ss;
	//		ss << command_mouse <<","<<button<<","<<state<< "," << x << "," << y;
	//		string command = ss.str();
	//		OrderCommandRegister::RecieveCommand(command);
	//		//WebSocketppFarcade::Send(ss.str());
	//	};

	//	glutCommandController.StartDisplay("client");

	//}

	//void MainLoop_server() {

	//	//GLUTCommandController glutCommandController;
	//	////�R�}���h�Ɗ֐��̑Ή��̍쐬
	//	//string command_init_glut = "glut_init";
	//	//string command_init_physx = "physx_init";
	//	//string command_update = "physx_update";
	//	//string command_input = "physx_input";
	//	//string command_render = "physx_rendering";

	//	//OrderCommandRegister::AddCommand(command_init_glut, [&]() { glutCommandController.StartDisplay("server"); });
	//	//OrderCommandRegister::AddCommand(command_init_physx, [&]() {
	//	//	PhysXFarcade::Awake();
	//	//	PhysXFarcade::SetCamera(glutCommandController._sCamera);
	//	//	});
	//	//OrderCommandRegister::AddCommand(command_update, PhysXFarcade::Update);
	//	//OrderCommandRegister::AddCommand(command_input, PhysXFarcade::RecieveInput, 'd');
	//	//OrderCommandRegister::AddCommand(command_render, PhysXFarcade::Rendering);
	//	////GLUT�ƃR�}���h�̑Ή��̍쐬
	//	//glutCommandController._awakeCallback = [=]() {
	//	//	OrderCommandRegister::RecieveCommand(command_init_physx);
	//	//};
	//	//glutCommandController._renderCallback = [=]() {
	//	//	OrderCommandRegister::RecieveCommand(command_render);
	//	//};

	//	//WebSocketppFarcade::SetRecieveMessage(OrderCommandRegister::RecieveCommand);
	//}
}