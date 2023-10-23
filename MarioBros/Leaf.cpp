#include "Leaf.h"

void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isInnited)
	{
		vy = LEAF_GRAVITY * dt;
		LeafMoving();
		DebugOut(L">>> LeafMoving >>> \n");
	}
	else if (vy != 0)
	{
		if (startY - y > LEAF_HEIGHT*2)
			SetState(LEAF_STATE_FALLING);
	}
	x += vx * dt;
	y += vy * dt;
}

void Leaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_LEAF_FALLING_LEFT;
	if (vx >= 0)aniId = ID_ANI_LEAF_FALLING_RIGHT;
	else aniId = ID_ANI_LEAF_FALLING_LEFT;
	animations->Get(aniId)->Render(x, y);
}

void Leaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_WIDTH / 2;
	top = y - LEAF_HEIGHT / 2;
	right = left + LEAF_WIDTH;
	bottom = top + LEAF_HEIGHT;
}

void Leaf::SetState(int state)
{
	switch (state) {
	case LEAF_STATE_INNIT:
		vy = -LEAF_INNIT_SPEED;
		break;
	case LEAF_STATE_FALLING:
		vy = 0;
		vx = -LEAF_VX_SPEED;
		isInnited = true;
		MovingTime = GetTickCount64();
		break;
	default:break;
	}
}

void Leaf::LeafMoving()
{
	if (GetTickCount64() - MovingTime >= 600)
	{
		vx = -vx;
		MovingTime = GetTickCount64();
	}
}

