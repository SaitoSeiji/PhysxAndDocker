#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<time.h>
#include<sstream>
using namespace std;
class CSVOutPuter
{
	vector<float> _outData;
	int _setDataDistance;
	int _nowCount;
	int _maxDataSize;//������f�[�^�T�C�Y���傫���ꍇ�͊Ԉ��������
	string _title;
public:
	CSVOutPuter(string title,int distance,int datasize);
	void TryAddData(float data);
	string GetOutPutText();
	void OutPutCSV();
};

