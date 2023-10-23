#include "Station.h"

#include "debug.h"

CStation::CStation(int id, bool left, bool top, bool right, bool bottom)
{
	sceneId = id;
	canLeft = left;
	canTop = top;
	canRight = right;
	canBottom = bottom;

	SetBoundingBox();
}

void CStation::Render()
{
	DebugOut(L">>> Rendered >>> \n");
	RenderBoundingBox();
}

void CStation::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x + 5;
	top = y + 5;
	right = left + WORLD_STATION_BBOX_WIDTH + 5;
	bottom = top + WORLD_STATION_BBOX_HEIGHT + 5;*/

	left = x - WORLD_STATION_BBOX_WIDTH / 2;
	top = y - WORLD_STATION_BBOX_HEIGHT / 2;
	right = left + WORLD_STATION_BBOX_WIDTH;
	bottom = top + WORLD_STATION_BBOX_HEIGHT;
}

void CStation::SetBoundingBox()
{
	/*left = x;
	top = y;
	right = left + WORLD_STATION_BBOX_WIDTH;
	bottom = top + WORLD_STATION_BBOX_HEIGHT;*/
}
