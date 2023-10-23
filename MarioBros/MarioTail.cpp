#include "MarioTail.h"

#include "BreakableBrick.h"
#include "debug.h"
#include "Goomba.h"
#include "QuestionBrick.h"
#include "Koopas.h"
#include "FirePiranhaPlant.h"
#include "PiranhaPlant.h"

void MarioTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (IsAttack)
	{
		left = x - TAIL_BBOX_WIDTH / 2;
		top = y - TAIL_BBOX_HEIGHT / 2;
		right = x + TAIL_BBOX_WIDTH;
		bottom = y + TAIL_BBOX_HEIGHT;
	}
}

void MarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i)))
		{
			if (dynamic_cast<CGoomba*>(coObjects->at(i)))
				OnCollisionWithGoomba(coObjects->at(i));
			else if (dynamic_cast<QuestionBrick*>(coObjects->at(i)))
				OnCollisionWithQuestionBrick(coObjects->at(i));
			else if (dynamic_cast<Koopas*>(coObjects->at(i)))
				OnCollisionWithKoopas(coObjects->at(i));
			else if (coObjects->at(i)->GetType() == OBJECT_TYPE_BREAKABLE_BRICK)
				OnCollisionWithBreakableBrick(coObjects->at(i));
			else if (dynamic_cast<FirePiranhaPlant*>(coObjects->at(i)))
			{
				FirePiranhaPlant* fireplant = dynamic_cast<FirePiranhaPlant*>(coObjects->at(i));
				fireplant->Delete();
			}
			else if (dynamic_cast<PiranhaPlant*>(coObjects->at(i)))
			{
				PiranhaPlant* plant = dynamic_cast<PiranhaPlant*>(coObjects->at(i));
				if (!plant->isInPipe)
					plant->Delete();
			}
		}
	}
}

void MarioTail::OnCollisionWithGoomba(LPGAMEOBJECT& obj)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(obj);
	if (goomba->GetState() != GOOMBA_STATE_DIEBYSHELL)
	{
		goomba->SetNX(nx);
		goomba->SetState(GOOMBA_STATE_DIEBYSHELL);
	}
	IsAttack = false;
}

void MarioTail::OnCollisionWithQuestionBrick(LPGAMEOBJECT& obj)
{
	QuestionBrick* qbrick = dynamic_cast<QuestionBrick*>(obj);
	if (!qbrick->innitItemSuccess) {
		qbrick->SetState(QUESTION_BRICK_STATE_START_INNIT);
	}
	IsAttack = false;
}

void MarioTail::OnCollisionWithKoopas(LPGAMEOBJECT& obj)
{
	Koopas* koopas = dynamic_cast<Koopas*>(obj);
	koopas->SetNX(nx);
	if (koopas->level == PARA_KOOPAS) koopas->level = NORMAL_KOOPAS;
	koopas->SetState(KOOPAS_STATE_ATTACKED_BY_TAIL);
	IsAttack = false;
}

void MarioTail::OnCollisionWithBreakableBrick(LPGAMEOBJECT& obj)
{
	BreakableBrick* breakableBrick = dynamic_cast<BreakableBrick*>(obj);
	if (breakableBrick->haveButton && !breakableBrick->buttonCreated)
	{
		breakableBrick->SetState(BREAKABLE_BRICK_STATE_CREATE_BUTTON);
	}
	else if (!breakableBrick->haveButton) {
		breakableBrick->SetState(BREAKABLE_BRICK_STATE_BREAK_DOWN);
	}
	IsAttack = false;
}

void MarioTail::Render()
{
	DebugOut(L">>> Tail rendered >>> \n");
	RenderBoundingBox();
}
