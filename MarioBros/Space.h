#pragma once

#include <iostream>
#include <fstream>
#include <map>

#include "Collision.h"
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"

#define COLUMN_WIDTH = 176

class CSpace
{

	//
	static CSpace* __instance;

	map<int, vector<LPGAMEOBJECT>>objects;


public:
	bool IsWorldMap;
	CSpace()
	{
		for (int i = 1; i < 17; i++)
		{
			objects[i] = vector<LPGAMEOBJECT>();
		}
	}
	~CSpace();

	map<int, vector<LPGAMEOBJECT>> LoadObj()
	{
		return objects;
	}

	void SetObj(LPGAMEOBJECT obj)
	{
		for (int i = 1; i < 17; i++)
		{
			objects.at(i).push_back(obj);
			objects.at(i).at(i)->Delete();
		}
	}

	int GetColumnForObject(float x)
	{
		int result = x / 176 + 1;
		return result;
	}

	void AddObjToColumn(LPGAMEOBJECT obj, int column)
	{
		objects[column].push_back(obj);
	}

	vector<LPGAMEOBJECT> GetObjectsInSpace(float x)
	{
		int column = GetColumnForObject(x);
		if (column == 1)
		{
			vector<LPGAMEOBJECT> bgObject = objects[1];
			vector<LPGAMEOBJECT> endObject = objects[2];

			return Merge(bgObject, endObject);
		}
		else if (column == 16)
		{
			vector<LPGAMEOBJECT> bgObject = objects[15];
			vector<LPGAMEOBJECT> endObject = objects[16];
		}
		else
		{
			vector<LPGAMEOBJECT> bgObject = objects[column-1];
			vector<LPGAMEOBJECT> midObject = objects[column];
			vector<LPGAMEOBJECT> endObject = objects[column + 1];
			vector<LPGAMEOBJECT> temp = Merge(bgObject, midObject);
			return Merge(temp, endObject);
		}
	}


	vector<LPGAMEOBJECT> Merge(vector<LPGAMEOBJECT> objSource, vector<LPGAMEOBJECT> objDest)
	{
		for (int i = 0; i < objDest.size(); i++)
		{
			objSource.push_back(objDest[i]);
		}
		return objSource;
	}

	//
	static CSpace* GetInstance();

};