#include "MarioTail.h"
#include "debug.h"

void MarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = x + TAIL_BBOX_WIDTH;
	bottom = y + TAIL_BBOX_HEIGHT;
}

void MarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void MarioTail::Render()
{
	DebugOut(L">>> Tail rendered >>> \n");
	RenderBoundingBox();
}
