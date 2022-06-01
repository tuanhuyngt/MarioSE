#pragma once
#include "GameObject.h"
class ColorBox :
	public CGameObject
{
	int Width;
	int Height;
public:
	ColorBox(int W, int H)
	{
		Width = W;
		Height = H;
		type = 6;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual int GetWidth() { return Width; }
	void Render() override;
	void DirectBlocking(int& l, int& t, int& r, int& b) override
	{ l = 0; t = 1; b = 0; r = 0; }
};

