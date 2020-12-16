#pragma once
#include <Camera.h>
#include<iostream>
#include<vector>
#include "FrameAction.h"
#include "RenderActor.h"
namespace PhysXFarcade {
	void Awake();
	void Update();
	void RecieveInput(unsigned char input,int x,int y);
	void HandleMouse(int button, int state, int x, int y);
	void HandleMotion(int x, int y);
	void Rendering();

	void SetCamera(Camera* cam);
}
