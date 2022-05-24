#include "BreakableBrickEffect.h"

BreakableBrickEffect::BreakableBrickEffect(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
}

void BreakableBrickEffect::Update(DWORD dt)
{
	vy += 0.001f * dt;
	x += vx * (float)dt;
	y += vy * (float)dt;
}

void BreakableBrickEffect::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_EFFECT_BREALABLE_BRICK;
	animations->Get(aniId)->Render(x, y);
}
