#pragma once
#include <Windows.h>
#include "Utils.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
class Camera
{
	float MarioVX;
	float MarioVY = 0;
	float MarioX;
	float MarioY;
	bool MarioIsOnPlatForm, MarioIsFlying, MarioIsInHiddenMap;
	float cam_x, cam_y, cam_vx, cam_vy = 0;
public:
	
	static Camera* __instance;

	static Camera* GetInstance()
	{
		if (__instance == NULL) __instance = new Camera();
		return __instance;
	}
	Camera();

	void GetMarioInfo(float vx, float vy, float x, float y, bool isOnPlatform, bool isFlying, bool isInHiddenMap)
	{
		MarioVY = vy;
		MarioX = x;
		MarioY = y;
		MarioIsOnPlatForm = isOnPlatform;
		MarioIsFlying = isFlying;
		MarioIsInHiddenMap = isInHiddenMap;
	}

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
		return !(objX < cam_x - 20 || objX - cam_x>SCREEN_WIDTH + 20 || objY < cam_y || objY - cam_y > SCREEN_HEIGHT);
	}

	void Update(DWORD dt);
};

