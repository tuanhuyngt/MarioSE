#pragma once
#include <Windows.h>
#include "Utils.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
class Camera
{
public:
	float cam_x, cam_y, cam_vx, cam_vy = 0;
	bool IsFollowingMario;
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

	float GetCamPosX()
	{
		return cam_x;
	}

	float GetCamPosY()
	{
		return cam_y;
	}
	void SetCamPosX(float x)
	{
		cam_x = x;
	}

	bool IsInCam(float objX, float objY)
	{
		return !(objX < cam_x || objX - cam_x>SCREEN_WIDTH || objY < cam_y || objY - cam_y > SCREEN_HEIGHT);
	}
	
	void Update(DWORD dt);
};

