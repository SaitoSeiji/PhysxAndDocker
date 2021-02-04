#pragma once
#include "CSVOutPuter.h"
#include<vector>
#include<time.h>
#include<sstream>

using namespace std;
class CSVOutPutFactory
{
	//dictionary�I�Ɏg��
	vector<string> _keyDatas;
	vector<CSVOutPuter*> _csvDatas;
public:
	void AddDataSet(string title,int distance,int maxDataSize);
	void Update(string key, float data);
	void OutPutCSV();
};

