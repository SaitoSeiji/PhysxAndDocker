#pragma once
#include<map>
#include <string>
#include<functional>
#include <iostream>
#include <vector>
#include "MyExtention.h"
using namespace std;
namespace OrderCommandRegister
{
//private:
//	map<string, void(*)()> _commanList_void;
//	map<string,void(*)(double input)> _commanList_double;
//	//�󂯎�����R�}���h���疽�߂������֐�
//	void CoalOrder(string command);
//	void CoalOrder(string command,string subCommand);
//public:
	void AddCommand(string key,function<void()>);
	void AddCommand(string key,function<void(double)>);
	void AddCommand(string key,function<void(string)>,char dummy);
	//�R�}���h���󂯎��֐�
	void RecieveCommand(string command);
};

