#include "ColorBox.h"

void ColorBox::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - Width / 2;
	top = y - Height / 2;
	right = left + Width;
	bottom = top + Height;
}

void ColorBox::Render()
{
}

