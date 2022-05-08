#pragma once
#pragma once
#include "GameObject.h"

#define FIRE_PIRANHAPLANT_UP_HEIGHT 16
#define FIRE_PIRANHAPLANT_ATTACK_ZONE 100

#define FIRE_PIRANHAPLANT_BBOX_WIDTH 16
#define FIRE_PIRANHAPLANT_BBOX_HEIGHT 34

#define MAX_ATTACK_ZONE	150
#define MIN_ATTACK_ZONE	100

#define FIRE_PIRANHAPLANT_STATE_UP	1
#define FIRE_PIRANHAPLANT_STATE_DOWN	2

#define ID_ANI_FIREPLANT_LEFT_DOWN		210000
#define ID_ANI_FIREPLANT_RIGHT_DOWN		210001
#define ID_ANI_FIREPLANT_LEFT_UP		210002
#define ID_ANI_FIREPLANT_RIGHT_UP		210003

#define ID_ANI_FIREPLANT_ATTACK_LEFT_DOWN		210004
#define ID_ANI_FIREPLANT_ATTACK_RIGHT_DOWN		210005
#define ID_ANI_FIREPLANT_ATTACK_LEFT_UP			210006
#define ID_ANI_FIREPLANT_ATTACK_RIGHT_UP		210007

class FirePiranhaPlant :
	public CGameObject
{
public:
	float ax;
	float ay;
	int aniId;

	float minY, maxY;

	bool isAttack;
	float enemyX, enemyY;
	DWORD CalcAtkTime;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; };

public:
	void GetEnemyPos(float EnemyX, float EnemyY) {
		enemyX = EnemyX;
		enemyY = EnemyY;
	}
	FirePiranhaPlant(float x, float y) :CGameObject(x, y) {
		minY = y - FIRE_PIRANHAPLANT_UP_HEIGHT * 2 - 8;
		maxY = y + FIRE_PIRANHAPLANT_UP_HEIGHT - 8;
		SetState(FIRE_PIRANHAPLANT_STATE_UP);
		enemyX = enemyY = 0;
	};
	virtual void SetState(int state);
};

