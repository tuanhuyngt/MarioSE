#include "Mushroom.h"

void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    if (isInnited)
    {
        vy += MUSHROOM_GRAVITY * dt;
    }
    else if (vy != 0)
    {
        float mushroominitY = startY - y;
        if (mushroominitY > MUSHROOM_HEIGHT + 1)
            SetState(MUSHROOOM_STATE_INNITED);
    }
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Mushroom::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{
    if (e->ny != 0 && e->obj->IsBlocking())
    {
        vy = 0;
    }
    else if (e->nx != 0 && e->obj->IsBlocking())
    {
        vx = -vx;
    }
}

void Mushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
    left = x - MUSHROOM_WIDTH / 2;
    top = y - MUSHROOM_HEIGHT / 2;
    right = left + MUSHROOM_WIDTH;
    bottom = top + MUSHROOM_HEIGHT;
}


void Mushroom::Render() {
    CAnimations* animations = CAnimations::GetInstance();
    if (animations->Get(ID_ANI_MUSHROOM))
        animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
    else RenderBoundingBox();
}

void Mushroom::SetState(int state) {
    switch (state) {
    case MUSHROOOM_STATE_BEING_INNITED:
        vy = -MUSHROOM_INNIT_SPEED;
        break;
    case MUSHROOOM_STATE_INNITED:
        vy = 0;
        isInnited = true;
        vx = MUSHROOM_SPEED;
        break;
    default:break;
    }
}