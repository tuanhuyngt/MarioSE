#include "WorldScene.h"

#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"

#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Platform.h"
#include "Camera.h"
#include "Map.h"
#include "SampleKeyEventHandler.h"
#include "HUD.h"
#include "LastItemObject.h"
#include "MiniMario.h"
#include "Station.h"

using namespace std;

CWorldScene::CWorldScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CWorldSceneKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1

#define MAX_SCENE_LINE 1024

void CWorldScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

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

void CWorldScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CWorldScene::_ParseSection_MAP(string line) {
	vector<string> tokens = split(line);
	if (tokens.size() < 9) return;
	int IDtex = atoi(tokens[0].c_str());
	wstring mapPath = ToWSTR(tokens[1]);
	int mapRow = atoi(tokens[2].c_str());
	int mapColumn = atoi(tokens[3].c_str());
	int tileRow = atoi(tokens[4].c_str());
	int tileColumn = atoi(tokens[5].c_str());
	int tileWidth = atoi(tokens[6].c_str());
	int tileHeight = atoi(tokens[7].c_str());
	int checkWM = atoi(tokens[8].c_str());

	map = new Map(IDtex, mapPath.c_str(), mapRow, mapColumn, tileRow, tileColumn, tileWidth, tileHeight);
	if (checkWM != 0) map->IsWorldMap = true;
	else map->IsWorldMap = false;
}


/*
	Parse a line in section [OBJECTS]
*/
void CWorldScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_STATION:
	{
		int id = atoi(tokens[4].c_str());
		bool left = atoi(tokens[5].c_str()) == 1 ? true : false;
		bool top = atoi(tokens[6].c_str()) == 1 ? true : false;
		bool right = atoi(tokens[7].c_str()) == 1 ? true : false;
		bool bottom = atoi(tokens[8].c_str()) == 1 ? true : false;
		obj = new CStation(id, left, top, right, bottom);
		break;
	}
	case OBJECT_TYPE_MINI_MARIO:
	{
		if (player != NULL)
		{
			return;
		}
		obj = new CMiniMario(x, y);
		player = (CMiniMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CWorldScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
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
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
	Camera::GetInstance()->SetCamPos(0, 0);
}

void CWorldScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	//Mario.push_back(objects[0]);

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	/*Camera::GetInstance()->Update(dt);
	PurgeDeletedObjects();*/
}

void CWorldScene::Render()
{
	map->Draw();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}

	HUD::GetInstance()->Draw();
}

/*
*	Clear all objects from this scene
*/
void CWorldScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CWorldScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CWorldScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CWorldScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CWorldScene::IsGameObjectDeleted),
		objects.end());
}

void CWorldSceneKeyHandler::KeyState(BYTE* states)
{
}

void CWorldSceneKeyHandler::OnKeyDown(int KeyCode)
{
	CMiniMario* mario = (CMiniMario*)((LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_LEFT:
		mario->GoLeft();
		break;
	case DIK_UP:
		mario->GoTop();
		break;
	case DIK_RIGHT:
		mario->GoRight();
		break;
	case DIK_DOWN:
		mario->GoBottom();
		break;
	case DIK_S:
		CGame::GetInstance()->SwitchScene(ID_SCENE_1_1);
		break;
	default:
		break;
	}
}

void CWorldSceneKeyHandler::OnKeyUp(int KeyCode)
{
}