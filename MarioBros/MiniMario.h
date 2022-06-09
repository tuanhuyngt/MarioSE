#pragma once
#include "GameObject.h"
#include "Station.h"

#define WORLD_MARIO_BBOX_WIDTH	14
#define WORLD_MARIO_BBOX_HEIGHT	16

class CMiniMario : public CGameObject
{
	CStation* curStation = NULL;

public:

	CStation* GetCurrentStation() { return curStation; }
	void SetCurrentStation(CStation* station) { curStation = station; }

	CMiniMario(float x, float y) : CGameObject(x, y)
	{
		
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnCollisionWithNextStation(CGameObject* obj, vector<LPGAMEOBJECT>* coObjs);

	void GoLeft();
	void GoTop();
	void GoRight();
	void GoBottom();
};

