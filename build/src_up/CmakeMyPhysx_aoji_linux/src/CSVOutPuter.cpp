#pragma once
#include "CSVOutPuter.h"
#include <iomanip>
using namespace std;

string CreateTextName();
CSVOutPuter::CSVOutPuter(string title,int count,int datasize) {
	_setDataDistance = count;
	_maxDataSize=datasize;
	_nowCount = 0;
	_title = "_"+title;
}

void CSVOutPuter::TryAddData(float data) {
	_nowCount++;
	if (_nowCount == _setDataDistance) {
		_nowCount = 0;
		_outData.push_back(data);
	}
}

string CSVOutPuter::GetOutPutText() {
	stringstream ss;

	double outputDistance = 1.0;
	double nowDistance = 0;
	if (_outData.size() > _maxDataSize) {
		outputDistance = _outData.size() /(double) _maxDataSize;
	}

	for (int i = 0; i < _outData.size(); i++) {

		nowDistance+=1;
		if (nowDistance >= outputDistance) {
			nowDistance -= outputDistance;
			ss << _outData[i]<<",";
		}
	}
	return  ss.str().substr(0,ss.str().length()-1);
}
void CSVOutPuter::OutPutCSV() {
	string textName = CreateTextName();
	ofstream outputFile(_title+textName);
	outputFile << GetOutPutText();
	outputFile.close();
}

string CreateTextName() {
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	stringstream ss;
	ss  << "_outData_"
		<< tm->tm_year + 1900<<"_"
		<< tm->tm_mon + 1 << "_"
		<< tm->tm_mday << "_"
		<< tm->tm_hour << "_"
		<< tm->tm_min << "_"
		<< tm->tm_sec
		<< ".csv";
	return ss.str();
}