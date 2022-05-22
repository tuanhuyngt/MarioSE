#include "BreakableBrick.h"

void BreakableBrick::Render()
{
	int aniId = -1;
	CAnimations* animations = CAnimations::GetInstance();

	if (type == OBJECT_TYPE_COIN)
	{
		aniId = ID_ANI_COIN;
		animations->Get(aniId)->Render(x, y);
	}
	else {
		aniId = ID_ANI_BREAKABLE_BRICK;
		animations->Get(aniId)->Render(x, y);
	}

}
