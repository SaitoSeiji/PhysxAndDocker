#include "FrameAction.h"

FrameAction::FrameAction(float frameRate) {
	_frameRate = frameRate;
}
//�o�ߎ��Ԃ̍X�V
void FrameAction::Update() {
	if (!_dtCulc.IsStarted()) {
		_dtCulc.Start();
		return;
	}
	float dt = _dtCulc.CalcDt_sec();
	_dtSum += dt;
}
//�ݒ肵���t���[���Ăяo���Ԋu�𒴂��Ă��邩�̊m�F
bool FrameAction::IsOverFrameRate() {
	return _dtSum >= _frameRate;
}
//���݂̌o�ߎ��Ԃ̎擾
float FrameAction::GetProgressTime() {
	return _dtSum;
}
//�o�ߎ��Ԃ����Z�b�g
void FrameAction::Refresh() {
	_dtSum = 0;
	_dtCulc.Reset();
}