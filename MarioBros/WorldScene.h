#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Map.h"

class CWorldScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;

	vector<LPGAMEOBJECT> Pipes;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_MAP(string line);

	void LoadAssets(LPCWSTR assetFile);

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
