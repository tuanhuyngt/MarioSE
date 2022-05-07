#pragma once
#include "GameObject.h"
class Pipe :
	public CGameObject
{
public:
	int Width, Height, TileSize;
	Pipe(float x, float y, int width, int height) : CGameObject(x, y) {
		Width = width;
		Height = height;
	}
	void Render() {};
	void Update(DWORD dt) {
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; };
	int IsCollidable() { return 1; }
};


