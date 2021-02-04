#pragma once
#include<functional>
#include <Camera.h>
#include<iostream>
#include "RenderActor.h"
#include "FrameAction.h"
namespace GLUTCommandController
{
	void StartDisplay(const char* name, double posx=100, double posy=100);
	void StartDisplay_guiOff();

	void AddCallbacl_awake(function<void()> func);
	void AddCallbacl_input(function<void(unsigned char, int x, int y)> func);
	void AddCallbacl_mouse(function<void(int, int, int, int)> func);
	void AddCallbacl_motion(function<void(int, int)> func);
	void AddCallbacl_idle(function<void()> func);
	void AddCallbacl_render(function<void()> func);
	/*function<void()> _awakeCallback=nullptr;
	function<void(unsigned char,int x,int y)> _inputCallback = nullptr;
	function<void(int, int, int, int)> _mouseCallback = nullptr;
	function<void(int, int)> _motionCallback = nullptr;
	function<void()> _idleCallback = nullptr;
	function<void()> _renderCallback = nullptr;*/

	Camera* GetCamera();

	//Camera* _sCamera;
	/*void(*_awakeCallback)(string);
	void(*_inputCallback)(string,unsigned char);
	void(*_idleCallback)(string);
	void(*_renderCallback)(string);*/
};

