#pragma once
#include "GameObject.h"
#include "debug.h"
#define LEAF_GRAVITY 0.0015f

#define LEAF_WIDTH  16
#define LEAF_HEIGHT  14

#define LEAF_INNIT_SPEED    0.1f

#define LEAF_STATE_INNIT 1
#define LEAF_STATE_FALLING 2

#define ID_ANI_LEAF_FALLING_RIGHT   80001
#define ID_ANI_LEAF_FALLING_LEFT   80002
#define LEAF_VX_SPEED 0.05f
class Leaf :
    public CGameObject
{
protected:
    bool isInnited;
    float startY;
    ULONGLONG MovingTime;
public:
    Leaf(float x, float y) :CGameObject(x, y) {
        isInnited = false;
        startY = y;
        isitem = true;
        MovingTime = 0;
    }
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;

    void Render() override;

    void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;

    void SetState(int state) override;

    void LeafMoving();

    int IsBlocking() override
    {
        return 0;
    }
    int IsCollidable() override
    {
        return 1;
    }
};

