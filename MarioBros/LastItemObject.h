#pragma once
#include "GameObject.h"
#include "debug.h"
#define LAST_ITEM_BBOX_SIZE 16

#define LAST_ITEM_IS_MUSHROOM 1
#define LAST_ITEM_IS_FLOWER 2
#define LAST_ITEM_IS_STAR 3

#define ID_ANI_LAST_ITEM	17072002

#define ID_ANI_END_WORLD_TEXT_MUSHROOM	17072003
#define ID_ANI_END_WORLD_TEXT_FLOWER	17072004
#define ID_ANI_END_WORLD_TEXT_STAR	17072005

#define END_TEXT_Y	52
class LastItemObject :
	public CGameObject
{
public:
	int LastItemType;
	bool IsChosen;
	ULONGLONG ChangeItemTime;
	int IsBlocking() { return 0; }

	LastItemObject(float x, float y) : CGameObject(x, y) {
		LastItemType = 0;
		IsChosen = false;
		ChangeItemTime = 0;
	}
	void Render();;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	void GetBoundingBox(float& l, float& t, float& r, float& b);;

	void SetState(int state) {}
};

