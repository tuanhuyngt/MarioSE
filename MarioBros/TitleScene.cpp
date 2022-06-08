#include "TitleScene.h"
#include <iostream>
#include <fstream>

#include "Animations.h"
#include "debug.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_OBJECTS	6

#define MAX_SCENE_LINE 1024

CTitleScene::CTitleScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CTitleSceneKeyHandler(this);
}


void CTitleScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return;

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CTitleScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CTitleScene::_ParseSection_OBJECTS(string line)
{
}



void CTitleScene::Load()
{
	ifstream f;
	f.open(sceneFilePath);

	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	

		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	backgroundSpr = CSprites::GetInstance()->Get(SPRITE_TITLE_BACKGROUND_ID);
	onePlayerArrowSpr = CSprites::GetInstance()->Get(SPRITE_TITLE_ARROW_ID);
	twoPlayerArrowSpr = CSprites::GetInstance()->Get(SPRITE_TITLE_ARROW_ID);
	num3Ani = CAnimations::GetInstance()->Get(ANIMATION_NUM_3_ID);

	Camera::GetInstance()->SetCamPos(0, 0);
}

void CTitleScene::Update(DWORD dt)
{
}

void CTitleScene::Render()
{
	backgroundSpr->Draw(125, 116);
	num3Ani->Render(124, 119);

	switch (playType)
	{
	case ONE_PLAYER_TYPE:
		onePlayerArrowSpr->Draw(61, 159);
		break;
	case TWO_PLAYER_TYPE:
		twoPlayerArrowSpr->Draw(61, 178);
		break;
	default:
		break;
	}
}

void CTitleScene::Unload()
{
	backgroundSpr = NULL;
	onePlayerArrowSpr = NULL;
	twoPlayerArrowSpr = NULL;
	num3Ani = NULL;
}

void CTitleSceneKeyHandler::KeyState(BYTE* states)
{
}

void CTitleSceneKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_UP:
		((CTitleScene*)scence)->SetPlayType(ONE_PLAYER_TYPE);
		break;
	case DIK_DOWN:
		((CTitleScene*)scence)->SetPlayType(TWO_PLAYER_TYPE);
		break;
	case DIK_W:
		switch (((CTitleScene*)scence)->GetPlayType())
		{
		case ONE_PLAYER_TYPE:
			CGame::GetInstance()->SwitchScene(1);
			break;
		case TWO_PLAYER_TYPE:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void CTitleSceneKeyHandler::OnKeyUp(int KeyCode)
{
}
