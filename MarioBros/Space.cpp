#include "Space.h"

#include "Map.h"
#include "Camera.h"
#include"debug.h"


CSpace* CSpace::__instance = NULL;

CSpace* CSpace::GetInstance()
{
	if (__instance == NULL) __instance = new CSpace();
	return __instance;
}


CSpace::~CSpace()
{
}