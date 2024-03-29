#pragma once
#include "GameObject.h"
#include "NavigationBox.h"

#define KOOPAS_GRAVITY 0.0007f
#define KOOPAS_WALKING_SPEED 0.03f
#define KOOPAS_NAVBOX_DISTANCE 2

#define KOOPAS_STATE_WALKING	1
#define KOOPAS_STATE_INSHELL	2
#define KOOPAS_STATE_INSHELL_ATTACK		3
#define KOOPAS_STATE_DIE_BY_SHELL	4
#define KOOPAS_STATE_ATTACKED_BY_TAIL	5
#define KOOPAS_STATE_REBORN  	6

#define ID_ANI_KOOPAS_WALKING_RIGHT	30000
#define ID_ANI_KOOPAS_WALKING_LEFT	30001
#define ID_ANI_KOOPAS_INSHELL	30002
#define ID_ANI_KOOPAS_INSHELL_ATTACK	30003
#define ID_ANI_KOOPAS_REBORN	30009
#define ID_ANI_KOOPAS_ATTACKED_BY_TAIL	30011
#define ID_ANI_KOOPAS_HAVE_WING_LEFT	30012
#define ID_ANI_KOOPAS_HAVE_WING_RIGHT	30013
#define ID_ANI_KOOPAS_ATTACKED_BY_TAIL_INSHELL_ATTACK	31001
#define ID_ANI_REDKOOPAS_WALKING_RIGHT	30004
#define ID_ANI_REDKOOPAS_WALKING_LEFT	30005
#define ID_ANI_REDKOOPAS_INSHELL	30006
#define ID_ANI_REDKOOPAS_INSHELL_ATTACK	30007
#define ID_ANI_REDKOOPAS_REBORN	30008
#define ID_ANI_REDKOOPAS_ATTACKED_BY_TAIL	30010
#define ID_ANI_REDKOOPAS_ATTACKED_BY_TAIL_INSHELL_ATTACK	31000

#define NORMAL_KOOPAS	1
#define SMART_KOOPAS	2
#define PARA_KOOPAS	3

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 28
#define KOOPAS_BBOX_HIDDEN 14

#define KOOPAS_JUMP_SPEED 0.25

#define KOOPAS_DROP_OUT_Y	450
#define KOOPAS_DROP_OUT_COMPLETE	1000

#define KOOPAS_WAITING_REBORN_TIME	5000

#define KOOPAS_REBORN_TIME	3000
class Koopas : public CGameObject
{
protected:

	bool ParaKoopas;
	float ay;
	bool InShell;
	bool isHold;
	bool IsAttackedByTail;
	ULONGLONG phaseTime;

	ULONGLONG ReborningTime, WaitingRebornTime;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e);

	void GetKoopasAni(int& IdAni);
	void GetRedKoopasAni(int& IdAni);
	void GetParaKoopasAni(int& IdAni);
	void HandleKoopasReborn() {
		if (state == KOOPAS_STATE_INSHELL)
		{
			if (GetTickCount64() - WaitingRebornTime >= KOOPAS_WAITING_REBORN_TIME)
				SetState(KOOPAS_STATE_REBORN);
		}
		else if (state == KOOPAS_STATE_REBORN)
		{
			if (GetTickCount64() - ReborningTime >= KOOPAS_REBORN_TIME)
			{
				SetState(KOOPAS_STATE_WALKING);
			}
		}
	}
public:
	NavigationBox* NavBox;

	int level;
	bool IsAttack;
	Koopas(float x, float y, int Level);
	virtual void SetState(int state);

	void HandleKoopasDropOut() {
		if (y > KOOPAS_DROP_OUT_Y)
			y = KOOPAS_DROP_OUT_COMPLETE;
	}

	void SetHolding(bool value)
	{
		this->isHold = value;
	}
};