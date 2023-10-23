#include "MiniMario.h"
#include "AssetIDs.h"

void CMiniMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += vx * dt;
	y += vy * dt;

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i)))
		{
			OnCollisionWithNextStation(coObjects->at(i), coObjects);
		}
	}
}

void CMiniMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_SPRITE_MINI_MARIO;
	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CMiniMario::OnCollisionWithNextStation(CGameObject* obj, vector<LPGAMEOBJECT>* coObjs)
{
	// World Station
	if (dynamic_cast<CStation*>(obj))
	{
		CStation* station = dynamic_cast<CStation*>(obj);
		if (curStation == NULL)
		{
			curStation = station;
		}
		if (curStation == station)
			return;

		if (vx > 0 && x >= (station->GetX()) -5)
		{
			vx = 0;
			curStation = station;
		}
		if (vx < 0 && x  <= (station->GetX()) - 3)
		{
			vx = 0;
			curStation = station;
		}
		if (vy > 0 && y >= (station->GetY()) - 5)
		{
			vy = 0;
			curStation = station;
		}
		if (vy < 0 && y <= (station->GetY()) - 3)
		{
			vy = 0;
			curStation = station;
		}
	}
}

void CMiniMario::GoLeft()
{
	if (curStation->canLeft && vx == 0 && vy == 0)
	{
		vx = -0.15f;
	}
}

void CMiniMario::GoTop()
{
	if (curStation->canTop && vx == 0 && vy == 0)
	{
		vy = -0.15f;
	}
}

void CMiniMario::GoRight()
{
	if (curStation->canRight && vx == 0 && vy == 0)
	{
		vx = 0.15f;
	}
}

void CMiniMario::GoBottom()
{
	if (curStation->canBottom && vx == 0 && vy == 0)
	{
		vy = 0.15f;
	}
}

void CMiniMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - WORLD_MARIO_BBOX_WIDTH / 2;
	t = y - WORLD_MARIO_BBOX_HEIGHT / 2;
	r = l + WORLD_MARIO_BBOX_WIDTH;
	b = t + WORLD_MARIO_BBOX_HEIGHT;
}


