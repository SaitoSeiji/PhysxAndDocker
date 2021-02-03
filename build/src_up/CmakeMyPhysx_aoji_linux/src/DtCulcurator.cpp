#include "DtCulcurator.h"
using namespace std;
using namespace chrono;

void DtCulcurator::Start() {
	Reset();
	isInited = true;
}
bool DtCulcurator::IsStarted() {
	return isInited;
}

float DtCulcurator::CalcDt_sec() {
	if (!IsStarted()) {
		cerr << "����������Ă��܂���";
		return -1;
	}
	auto now = system_clock::now();
	auto dur = now - beforePoint; 
	beforePoint = now;
	auto misec = duration_cast<std::chrono::microseconds>(dur).count();
	float sec = misec / 1000000.0f;
	return sec;
	
}

void DtCulcurator::Reset() {

	auto now = chrono::system_clock::now();
	beforePoint = now;
	
}