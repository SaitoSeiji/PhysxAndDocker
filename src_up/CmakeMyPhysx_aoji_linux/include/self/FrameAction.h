#pragma once
#include <string>
#include "DtCulcurator.h"

using namespace std;
class FrameAction
{
	DtCulcurator _dtCulc;
	float _frameRate = 0;
	float _dtSum = 0;
public:
	FrameAction(float frameRate);
	//�o�ߎ��Ԃ̍X�V
	void Update();
	//�ݒ肵���t���[���Ăяo���Ԋu�𒴂��Ă��邩�̊m�F
	bool IsOverFrameRate();
	//���݂̌o�ߎ��Ԃ̎擾
	float GetProgressTime();
	//�o�ߎ��Ԃ����Z�b�g
	void Refresh();
};

