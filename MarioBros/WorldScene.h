#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Map.h"

#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	8

class CWorldScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;

	vector<LPGAMEOBJECT> Pipes;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_OBJECTS(string line);

	void _ParseSection_MAP(string line);

public:
	CWorldScene(int id, LPCWSTR filePath);
	Map* map;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

class CWorldSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CWorldSceneKeyHandler(CScene* s) :CSceneKeyHandler(s) {};
};

typedef CWorldScene* LPWORLDSCENE;