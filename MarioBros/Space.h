#pragma once

#include <vector>
#include "GameObject.h"

class Unit
{
	friend class CSpace;

private:
	CSpace* space;
	LPGAMEOBJECT obj;
	float x;
	float y;

	Unit* prev;
	Unit* next;

public:
	Unit(CSpace* space, LPGAMEOBJECT obj, float x, float y);

	void Move(float x, float y);
	LPGAMEOBJECT GetObj() { return this->obj; }
};

class CSpace
{
	int map_width;
	int map_height;

	int cell_width;
	int cell_height;

	int nums_col;
	int nums_row;

	vector<vector<Unit*>> cells;

public:
	CSpace(int map_width, int map_height, int cell_width = 256, int cell_height = 688);
	~CSpace();

	void Add(Unit* unit);
	void Move(Unit* unit, float x, float y);
	void Get(float camX, float camY, vector<Unit*>& listUnits);

	void Out();
};

