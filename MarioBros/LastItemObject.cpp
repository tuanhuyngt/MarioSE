#include "LastItemObject.h"

void LastItemObject::Render()
{
	if (!IsChosen)
	{
		int aniId = ID_ANI_LAST_ITEM;
		CAnimations* animations = CAnimations::GetInstance();
		if (animations->Get(aniId))
			animations->Get(aniId)->Render(x, y);
	}
	else if (IsChosen)
	{
		int aniId = ID_ANI_LAST_ITEM + LastItemType;
		CAnimations* animations = CAnimations::GetInstance();
		if (animations->Get(aniId))
			animations->Get(aniId)->Render(x, y - END_TEXT_Y);
	}
}

void LastItemObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsChosen)
	{
		if (ChangeItemTime == 0)
			ChangeItemTime = GetTickCount64();
		else if (GetTickCount64() - ChangeItemTime >= 100 && GetTickCount64() - ChangeItemTime < 200)
		{
			LastItemType = LAST_ITEM_IS_MUSHROOM;
		}
		else if (GetTickCount64() - ChangeItemTime >= 200 && GetTickCount64() - ChangeItemTime < 300)
		{
			LastItemType = LAST_ITEM_IS_FLOWER;
		}
		else if (GetTickCount64() - ChangeItemTime >= 300 && GetTickCount64() - ChangeItemTime < 400)
		{
			LastItemType = LAST_ITEM_IS_STAR;
			ChangeItemTime = 0;
		}
	}
	if (CGame::GetInstance()->resetLastItem)
	{
		CGame::GetInstance()->resetLastItem = IsChosen = false;
		ChangeItemTime = 0;
	}
}

void LastItemObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!IsChosen)
	{
		l = x - LAST_ITEM_BBOX_SIZE / 2;
		t = y - LAST_ITEM_BBOX_SIZE / 2;
		r = l + LAST_ITEM_BBOX_SIZE;
		b = t + LAST_ITEM_BBOX_SIZE;
	}
}
