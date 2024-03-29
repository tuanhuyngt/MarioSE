#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"

#include "BreakableBrick.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Camera.h"
#include "Map.h"
#include "ColorBox.h"
#include "QuestionBrick.h"
#include "SampleKeyEventHandler.h"
#include "Koopas.h"
#include "Pipe.h"
#include "FirePiranhaPlant.h"
#include "PiranhaPlant.h"
#include "HUD.h"
#include "LastItemObject.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
	space = new CSpace(3072, 688);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define SCENE_SECTION_MAP	3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

Map* map;

void CPlayScene::_ParseSection_SPRITES(string line)
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

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_MAP(string line) {
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
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: {
		int goombaLevel = atoi(tokens[3].c_str());
		obj = new CGoomba(x, y, goombaLevel);
		unit = new Unit(space, obj, x, y);
		break;
	}
	case OBJECT_TYPE_KOOPAS: {
		int koopasLevel = atoi(tokens[3].c_str());
		obj = new Koopas(x, y, koopasLevel);
		unit = new Unit(space, obj, x, y);
		break;
	}
	case OBJECT_TYPE_BRICK: obj = new CBrick(x,y); break;
	case OBJECT_TYPE_QUESTIONBRICK: {
		int item = atoi(tokens[3].c_str());
		obj = new QuestionBrick(x, y, item);
		unit = new Unit(space, obj, x, y);
		break;
	}
	case OBJECT_TYPE_FIREPIRANHAPLANT:
	{
		obj = new FirePiranhaPlant(x, y);
		unit = new Unit(space, obj, x, y);
		break;
	}
	case OBJECT_TYPE_PIRANHAPLANT:
	{
		obj = new PiranhaPlant(x, y);
		unit = new Unit(space, obj, x, y);
		break;
	}
	case OBJECT_TYPE_INNIT_COIN: {
		int type = atoi(tokens[3].c_str());
		obj = new CCoin(x, y, type);
		unit = new Unit(space, obj, x, y);
		break;
	}
	case OBJECT_TYPE_PIPE: {
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		int type = atoi(tokens[5].c_str());
		obj = new Pipe(x, y, width, height, type);
		Pipes.push_back(obj);
		unit = new Unit(space, obj, x, y);
		break;
	}
	case OBJECT_TYPE_BREAKBLEBRICK: {
		bool HaveButton = false;
		int Item = atoi(tokens[3].c_str());
		if (Item == 1)
		{
			HaveButton = true;
			ButtonP* buttonP = new ButtonP();
			buttonP->SetPosition(0, 0);
			objects.push_back(buttonP);
			BreakableBrick* Brkbrick = new BreakableBrick(x, y, HaveButton);
			Brkbrick->buttonP = buttonP;
			obj = Brkbrick;
		}
		else obj = new BreakableBrick(x, y, HaveButton);
		unit = new Unit(space, obj, x, y);
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
		unit = new Unit(space, obj, x, y);
		break;
	}

	case OBJECT_TYPE_COLORBOX:
	{
		int width, height;
		width = atoi(tokens[3].c_str());
		height = atoi(tokens[4].c_str());
		obj = new ColorBox(width, height);
		unit = new Unit(space, obj, x, y);
		break;
	}

	case OBJECT_TYPE_LAST_ITEM:
	{
		obj = new LastItemObject(x, y);
		unit = new Unit(space, obj, x, y);
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

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
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

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[MAP]") { section = SCENE_SECTION_MAP; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
	Camera::GetInstance()->SetCamPos(0, 240);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> Mario;

	GetObjectFromGrid();

	for (size_t i = 1; i < objects.size(); i++)
	{
		if (dynamic_cast<QuestionBrick*>(objects[i]))
		{
			QuestionBrick* QBrick = dynamic_cast<QuestionBrick*>(objects[i]);
			if (!QBrick->innitItemSuccess)
				AddItemToQBrick(QBrick, i);
		}
		coObjects.push_back(objects[i]);
	}
	Mario.push_back(objects[0]);

	/*for (size_t i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<FirePiranhaPlant*>(objects[i]))
		{
			FirePiranhaPlant* Fplant = dynamic_cast<FirePiranhaPlant*>(objects[i]);
			Fplant->GetEnemyPos(player->GetX(), player->GetY());
			objects[i]->Update(dt, &Mario);
		}
		else {
			if (Camera::GetInstance()->IsInCam(objects[i]->GetX(), objects[i]->GetY()) || dynamic_cast<CMario*>(objects[i]))
				objects[i]->Update(dt, &coObjects);
		}
	}*/

	for (size_t i = 0; i < listObjects.size(); i++)
	{
		if (dynamic_cast<FirePiranhaPlant*>(listObjects[i]))
		{
			FirePiranhaPlant* Fplant = dynamic_cast<FirePiranhaPlant*>(listObjects[i]);
			Fplant->GetEnemyPos(player->GetX(), player->GetY());
			listObjects[i]->Update(dt, &Mario);
		}
		else {
			listObjects[i]->Update(dt, &coObjects);
		}
	}
	player->Update(dt, &coObjects);

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	Camera::GetInstance()->Update(dt);
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	map->Draw();

	/*for (int i = 1; i < objects.size(); i++)
	{
		if (!dynamic_cast<Pipe*>(objects[i]))
			objects[i]->Render();
	}
	objects[0]->Render();

	for (int i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Render();
	}*/

	for (int i = 0; i < listObjects.size(); i++)
	{
		if (!dynamic_cast<Pipe*>(listObjects[i]))
			listObjects[i]->Render();
	}
	player->Render();

	for (int i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Render();
	}

	HUD::GetInstance()->Draw();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
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
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	//vector<LPGAMEOBJECT>::iterator it;
	//for (it = objects.begin(); it != objects.end(); it++)
	//{
	//	LPGAMEOBJECT o = *it;
	//	if (o->IsDeleted())
	//	{
	//		delete o;
	//		*it = NULL;
	//	}
	//}

	//// NOTE: remove_if will swap all deleted items to the end of the vector
	//// then simply trim the vector, this is much more efficient than deleting individual items
	//objects.erase(
	//	std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
	//	objects.end());
}

void CPlayScene::GetObjectFromGrid()
{
	listUnits.clear();
	listObjects.clear();

	float camX;
	float camY;

	Camera::GetInstance()->GetCamPos(camX, camY);

	space->Get(camX, camY, listUnits);

	//DebugOut(L"%d \n", listUnits.size());

	for (UINT i = 0; i < listUnits.size(); i++)
	{
		LPGAMEOBJECT obj = listUnits[i]->GetObj();
		listObjects.push_back(obj);
	}
}