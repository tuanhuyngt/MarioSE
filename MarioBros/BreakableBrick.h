#pragma once
#include "GameObject.h"
#include "Coin.h"

#define BRICK_BBOX_WIDTH	16
#define BRICK_BBOX_HEIGHT	16
#define BREAKABLE_BRICK_STATE_BREAK_DOWN	2
#define COIN_STATE_TRANSFORMS_BRICK	4
#define BREAKABLE_BRICK_STATE_IS_UP	5

#define OBJECT_TYPE_BREAKABLE_BRICK	30
#define OBJECT_TYPE_COIN	31

#define ID_ANI_COIN 80005
#define ID_ANI_BREAKABLE_BRICK 10001
#define ID_ANI_BREAKABLE_BRICK_IS_UP	10002


#define BREAKBLE_BRICK_VY	0.05f
class BreakableBrick :
	public CGameObject
{
public:
	int isBlocking;
	float startY;
	bool InitCoin;
	ULONGLONG ChangeBackToBrickTime;
	bool isBreakDown;

	BreakableBrick(float x, float y) : CGameObject(x, y) {
		startY = y;
		type = OBJECT_TYPE_BREAKABLE_BRICK;
		vy = 0;
		InitCoin = isBreakDown = false;
		ChangeBackToBrickTime = 0;
		isBlocking = 1;
	}

	void Render();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return isBlocking; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		y += vy * dt;
		if (startY - y >= 5 && vy < 0)
		{
			vy = -vy;
		}
		if (vy > 0 && y >= startY)
		{
			y = startY;
			vy = 0;
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		if (!isBreakDown)
		{
			l = x - BRICK_BBOX_WIDTH / 2;
			t = y - BRICK_BBOX_HEIGHT / 2;
			r = l + BRICK_BBOX_WIDTH;
			b = t + BRICK_BBOX_HEIGHT;
		}
	};

	void SetState(int state) {
		switch (state) {
		case BREAKABLE_BRICK_STATE_BREAK_DOWN:
			isBreakDown = true;
			break;
		case BREAKABLE_BRICK_STATE_IS_UP:
			vy = -BREAKBLE_BRICK_VY;
			break;
		default:break;
		}
		CGameObject::SetState(state);
	}
};

