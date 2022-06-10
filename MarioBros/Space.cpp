﻿#include "Space.h"

#include "debug.h"

Unit::Unit(CSpace* space, LPGAMEOBJECT obj, float x, float y)
{
	this->space = space;
	this->obj = obj;
	this->x = x;
	this->y = y;

	this->prev = NULL;
	this->next = NULL;

	space->Add(this);
}

void Unit::Move(float x, float y)
{
	space->Move(this, x, y);
}

CSpace::CSpace(int map_width, int map_height, int cell_width, int cell_height)
{
	this->map_width = map_width;
	this->map_height = map_height;

	this->cell_width = cell_width;
	this->cell_height = cell_height;

	nums_col = map_width / cell_width;
	nums_row = map_height / cell_height;

	cells.resize(nums_row);

	for (int i = 0; i < nums_row; i++)
		cells[i].resize(nums_col);

	for (int i = 0; i < nums_row; i++)
		for (int j = 0; j < nums_col; j++)
			cells[i][j] = NULL;
}

CSpace::~CSpace()
{
}

void CSpace::Add(Unit* unit)
{
	int row = (int)(unit->y / cell_height);
	int col = (int)(unit->x / cell_width);

	unit->prev = NULL;
	unit->next = cells[row][col];
	cells[row][col] = unit;

	if (unit->next != NULL)
		unit->next->prev = unit;
}

void CSpace::Move(Unit* unit, float x, float y)
{
	int old_row = (int)(unit->y / cell_height);
	int old_col = (int)(unit->x / cell_width);

	int new_row = (int)(y / cell_height);
	int new_col = (int)(x / cell_width);

	if (new_row < 0 || new_row >= nums_row || new_col < 0 || new_col >= nums_col)
		return;

	unit->x = x;
	unit->y = y;

	if (old_row == new_row && old_col == new_col)
		return;

	if (unit->prev != NULL)
	{
		unit->prev->next = unit->next;
	}

	if (unit->next != NULL)
	{
		unit->next->prev = unit->prev;
	}

	if (cells[old_row][old_col] == unit)
	{
		cells[old_row][old_col] = unit->next;
	}

	Add(unit);
}

void CSpace::Get(float camX, float camY, vector<Unit*>& listUnits)
{
	int start_col = (int)(camX / cell_width);
	int end_col = ceil((camX + SCREEN_WIDTH) / cell_width);

	for (int i = 0; i < nums_row; i++)
	{
		for (int j = start_col; j < end_col; j++)
		{
			Unit* unit = cells[i][j];

			while (unit != NULL)
			{
				if (unit->GetObj()->IsDeleted() == false)
					listUnits.push_back(unit);
				unit = unit->next;
			}
		}
	}
}

void CSpace::Out()
{
	for (int i = 0; i < nums_row; i++)
	{
		for (int j = 0; j < nums_col; j++)
		{
			int c = 0;
			Unit* unit = cells[i][j];

			while (unit)
			{
				c++;
				unit = unit->next;
			}

			DebugOut(L"Out", c);
		}
	}
}


