#include "Camera.h"

Camera* Camera::__instance = NULL;
Camera::Camera()
{
	cam_y = 240;
	cam_vy = 0.0;
}

void Camera::Update(DWORD dt)
{
	cam_y += cam_vy * dt;
}