#pragma once
#include "GameObject.h"
#include "Mario.h"

#define FIREBULLET_BBOX_WIDTH	8
#define FIREBULLET_BBOX_HEIGHT	8

#define ID_ANI_FIREBULLET	1607200

class FireBullet :
	public CGameObject
{
public:

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void Render() override;

	int IsCollidable() override { return 1; };
	int IsBlocking() override { return 0; }
	void OnNoCollision(DWORD dt) override;

	void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt) override;
	bool isActivate;
	FireBullet(float x, float y) :CGameObject(x, y) {
		isActivate = false;
	}
	void SetState(int state) override;
};

