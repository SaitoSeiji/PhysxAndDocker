#include "OrderCommandRegister.h"
using namespace std;
namespace OrderCommandRegister {
	map<string, function<void()>> _commanList_void;
	map<string, function<void(double)>> _commanList_double;
	map<string, function<void(string)>> _commanList_string;
	/*map<string, void(*)()> _commanList_void;
	map<string, void(*)(double input)> _commanList_double;
	map<string, void(*)(unsigned char input)> _commanList_char;*/

	void CoalOrder(string command) {
		auto itr = _commanList_void.find(command);
		if (itr != _commanList_void.end()) {
			_commanList_void[command]();
		}
		else {
			cout << "not found command:" << command << endl;
		}
	}
	void CoalOrder(string command, string subCommand) {
		auto itr_double = _commanList_double.find(command);
		auto itr_char = _commanList_string.find(command);
		if (itr_double != _commanList_double.end()) {
			try {
				double num = stod(subCommand);
				_commanList_double[command](num);
			}
			catch (const std::invalid_argument& e) {
				std::cout << e.what(); // "stoi: no conversion"
				std::cout << "�ϊ��Ɏ��s���܂���" << subCommand << endl;
			}
		}
		else if (itr_char != _commanList_string.end()) {
			_commanList_string[command](subCommand);
		}
		else {
			cout << "not found command:" << command << endl;
		}
	}


	//�R�}���h�󂯎��@��؂蕶����','�@��؂��Ă�����2�ڂ̕�������f�[�^�Ƃ��ė��p
	void RecieveCommand(string command) {
		vector<string> vec = MyExtention::Split(command, ',');
		if (vec.size() == 1) {
			CoalOrder(vec[0]);
		}
		else if (vec.size() >= 2) {
			int size = vec[0].size()+1;
			string subCommand = command.substr(size);
			CoalOrder(vec[0],subCommand );
		}
	}

	void AddCommand(string key, function<void()> command) {
		_commanList_void[key] = command;
	}
	void AddCommand(string key, function<void(string)> command,char dummy) {
		_commanList_string[key] = command;
	}
	void AddCommand(string key, function<void(double)> command) {
		_commanList_double[key] = command;
	}
	//void AddCommand(string key, void(*command)()) {
	//	_commanList_void[key] = command;
	//}
	//void AddCommand(string key, void(*command)(double input)) {
	//	_commanList_double[key] = command;
	//}
	//void AddCommand(string key, void(*command)(unsigned char input)) {
	//	_commanList_char[key] = command;
	//}

}