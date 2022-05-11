#pragma once
#include "GameObject.h"

#define TAIL_BBOX_WIDTH 8
#define TAIL_BBOX_HEIGHT 3

class MarioTail :
	public CGameObject
{
public:
	float ax;
	float ay;

	bool IsAttack;

	DWORD attackTime;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	int level, goombaPhase;
	virtual void SetState(int state) {};
};

