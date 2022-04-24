#pragma once
#include <Windows.h>
#include "Utils.h"
#define SCREEN_WIDTH 252
#define SCREEN_HEIGHT 272
class Camera
{
public:
	float cam_x, cam_y, cam_vx, cam_vy = 0;
public:
	static Camera* __instance;

	static Camera* GetInstance()
	{
		if (__instance == NULL) __instance = new Camera();
		return __instance;
	}
	Camera();

	void SetCamPos(float x, float y) {
		cam_x = x;
		cam_y = y;
	};

	void GetCamPos(float& x, float& y) {
		x = cam_x;
		y = cam_y;
	}
};

