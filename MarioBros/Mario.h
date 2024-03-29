#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "MarioTail.h"

#include "debug.h"
#include "Koopas.h"

#define MARIO_GO_HIDDEN_MAP_SPEED 0.05f

#define HIDDEN_MAP_START_POS_X	2116
#define HIDDEN_MAP_START_POS_Y	480

#define HIDDEN_MAP_OUT_POS_X	2336
#define HIDDEN_MAP_OUT_POS_Y	400
#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_SLOWING_DOWN_X	0.00035f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_FRICTION		0.006f

#define MARIO_JUMP_SPEED_Y		0.4f
#define MARIO_JUMP_RUN_SPEED_Y	0.45f

#define MARIO_GRAVITY			0.001f

#define MARIO_JUMP_DEFLECT_SPEED  0.3f
#define MARIO_SLOW_FALLING_SPEED  0.02f
#define MARIO_FLYING_SPEED  0.15f
#define MARIO_MAX_SPEED_STACK	7

#define MARIO_SPEEDSTACK_TIME 140
#define MARIO_KICK_KOOPAS_TIME 200
#define MARIO_SLOWFALLING_TIME 300
#define RACOON_ATTACK_TIME 250
#define RACOON_IS_ATTACKED_TIME	600
#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICKKOOPAS	700

#define MARIO_STATE_ATTACK	800

#define MARIO_STATE_SLOW_FALLING	302

#define MARIO_STATE_FLYING	900

#define MARIO_STATE_TRANSFORM_RACOON	901
#define RACOON_STATE_TRANSFORM_MARIO		902
#define MARIO_STATE_RELEASE_KOOPAS	1000
#define MARIO_STATE_GO_IN_HIDDEN_MAP 1100
#define MARIO_STATE_GO_OUT_HIDDEN_MAP 1200
#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_MARIO_KICKKOOPAS_RIGHT	1701
#define ID_ANI_MARIO_KICKKOOPAS_LEFT	1700

#define ID_ANI_MARIO_HOLDKOOPAS_IDLE_RIGHT	1702
#define ID_ANI_MARIO_HOLDKOOPAS_IDLE_LEFT	1703

#define ID_ANI_MARIO_HOLDKOOPAS_WALK_RIGHT	1704
#define ID_ANI_MARIO_HOLDKOOPAS_WALK_LEFT	1705

#define ID_ANI_MARIO_HOLDKOOPAS_JUMP_RIGHT	1706
#define ID_ANI_MARIO_HOLDKOOPAS_JUMP_LEFT	1707
// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_SMALLMARIO_KICKKOOPAS_RIGHT	1801
#define ID_ANI_SMALLMARIO_KICKKOOPAS_LEFT	1800

#define ID_ANI_SMALLMARIO_HOLDKOOPAS_IDLE_RIGHT	1802
#define ID_ANI_SMALLMARIO_HOLDKOOPAS_IDLE_LEFT	1803

#define ID_ANI_SMALLMARIO_HOLDKOOPAS_WALK_RIGHT	1804
#define ID_ANI_SMALLMARIO_HOLDKOOPAS_WALK_LEFT	1805

#define ID_ANI_SMALLMARIO_HOLDKOOPAS_JUMP_RIGHT	1806
#define ID_ANI_SMALLMARIO_HOLDKOOPAS_JUMP_LEFT	1807
#define ID_ANI_RACOON_IDLE_RIGHT 1900
#define ID_ANI_RACOON_IDLE_LEFT 1901

#define ID_ANI_RACOON_WALKING_RIGHT 1902
#define ID_ANI_RACOON_WALKING_LEFT 1903

#define ID_ANI_RACOON_JUMP_WALK_RIGHT 1904
#define ID_ANI_RACOON_JUMP_WALK_LEFT 1905

#define ID_ANI_RACOON_FALLING_RIGHT 1906
#define ID_ANI_RACOON_FALLING_LEFT 1907

#define ID_ANI_RACOON_RUNNING_RIGHT 1908
#define ID_ANI_RACOON_RUNNING_LEFT 1909

#define ID_ANI_RACOON_FLYING_RIGHT 1910
#define ID_ANI_RACOON_FLYING_LEFT 1911
#define ID_ANI_RACOON_SITTING_RIGHT 1912
#define ID_ANI_RACOON_SITTING_LEFT 1913
#define ID_ANI_RACOON_BRACE_RIGHT 1914
#define ID_ANI_RACOON_BRACE_LEFT 1915
#define ID_ANI_MARIO_SLOWFALLING_RIGHT	1916
#define ID_ANI_MARIO_SLOWFALLING_LEFT	1917

#define ID_ANI_RACOON_ATTACK_RIGHT	1918
#define ID_ANI_RACOON_ATTACK_LEFT	1919
#define ID_ANI_RACOON_FALLING_FLYING_RIGHT 1920
#define ID_ANI_RACOON_FALLING_FLYING_LEFT 1921

#define ID_ANI_RACOON_EFFECT_WHEN_ATTACKED	1922

#define ID_ANI_RACOON_KICKKOOPAS_RIGHT	1923
#define ID_ANI_RACOON_KICKKOOPAS_LEFT	1924

#define ID_ANI_RACOON_HOLDINGKOOPAS_IDLE_RIGHT	1925
#define ID_ANI_RACOON_HOLDINGKOOPAS_IDLE_LEFT	1926

#define ID_ANI_RACOON_HOLDINGKOOPAS_WALKING_RIGHT	1927
#define ID_ANI_RACOON_HOLDINGKOOPAS_WALKING_LEFT	1928

#define ID_ANI_RACOON_HOLDINGKOOPAS_JUMPING_RIGHT	1929
#define ID_ANI_RACOON_HOLDINGKOOPAS_JUMPING_LEFT	1930
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON		3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	bool IsFalling;
	DWORD FallingTime;
	bool IsSlowFalling;
	DWORD SlowFallingTime;
	bool isFlying;
	DWORD FlyingTime;

	int speedStack;
	bool isHoldingKoopas;
	
	MarioTail* tail;
	Koopas* koopasHold;

	DWORD effectTime;
	DWORD SpeedStackTime;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	bool IsAttack;
	DWORD AttackTime;

	bool IsKickKoopas;
	DWORD KickKoopasTime;

	bool canGotoHiddenMap = false;
	bool goInHidden = false;
	bool goOutHidden = false;
	bool IsInHiddenMap = false;
	float StartY;
	float pipeX;

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		isFlying = false;
		IsAttack = false;
		IsKickKoopas = false;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		speedStack = 0;
		AttackTime = 0;
		SpeedStackTime = 0;
		tail = new MarioTail();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}	

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	int IsUntouchable() { return untouchable; }

	bool CheckMarioIsOnPlatform() { return isOnPlatform; };

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void IncreaseSpeedStack() {
		if (speedStack < MARIO_MAX_SPEED_STACK)
		{
			if (SpeedStackTime == 0)SpeedStackTime = GetTickCount64();
			else if (GetTickCount64() - SpeedStackTime > MARIO_SPEEDSTACK_TIME)
			{
				SpeedStackTime = 0;
				speedStack++;
			}
		}
		DebugOut(L">>> Increase Stack >>> \n");
	}

	void DecreaseSpeedStack() {
		if (SpeedStackTime == 0)SpeedStackTime = GetTickCount64();
		else if (GetTickCount64() - SpeedStackTime > MARIO_SPEEDSTACK_TIME)
		{
			SpeedStackTime = 0;
			speedStack--;
		}
		DebugOut(L">>> Decrease Stack >>> \n");
	}

	int GetMarioLevel() {
		return level;
	}

	bool IsFlying()
	{
		return isFlying;
	}

	bool IsSitting()
	{
		return isSitting;
	}

	int GetSpeedStack()
	{
		return speedStack;
	}

	void Reset()
	{
		y = 240;
		level = MARIO_LEVEL_RACOON;
		state = MARIO_STATE_IDLE;
	}

	bool CheckMarioHoldKoopas() {
		return isHoldingKoopas;
	}

	void SetStateInHiddenMap(bool value)
	{
		this->IsInHiddenMap = value;
	}

	bool CanGotoHiddenMap()
	{
		return canGotoHiddenMap;
	}

	void HandleMarioIsFlying(DWORD dt);
	void HandleMarioIsAttacked();
	void HandleMarioRunning();
	void HandleMarioStateIdle();
	void HandleMarioFalling();
	void HandleMarioKickKoopas();
	void HandleMarioHoldingKoopas();
	void HandleRacoonAttack(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void HandleMarioTransformRacoon();
	void HandleMarioUntouchable();
	void HandleMarioGoInHiddenMap(DWORD dt);
	void HandleMarioGoOutsiteMap();

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithItem(LPCOLLISIONEVENT e);
	void OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithButtonP(LPCOLLISIONEVENT e);
	void OnCollisionWithSpecialPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithLastItemObject(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};