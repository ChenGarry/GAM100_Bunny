//---------------------------------------------------------
// file:	SceneTable.c
// author:	Garry Chen
// brief:	Table of scene values and options
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "SceneManager.h"
#include "SceneTable.h"

// Include all game state headers here.
#include "Scene_DigiPenLogo.h"
#include "Scene_MainMenu.h"
#include "Scene_Game.h"
#include "Scene_GameOver.h"
#include "Scene_Credits.h"
//#include "Scene_Game.h"
//#include "Scene_GameOver.h"

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

typedef void(*SceneFunctionName)();

typedef struct
{
	SceneFunctionName	sceneInit;		// Pointer to a scene initialization function.
	SceneFunctionName	sceneUpdate;	// Pointer to a scene update function.
	SceneFunctionName	sceneExit;		// Pointer to a scene exit function.

} SceneTableEntry;

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------

static const SceneTableEntry SceneTable[SCENE_MAX] =
{
	// DigiPen Logo
	{ SceneDigiPenLogoInit, SceneDigiPenLogoUpdate, NULL },
	// Main Menu
	{ SceneMainMenuInit, SceneMainMenuUpdate, NULL },
	// Game
	{ SceneGameInit, SceneGameUpdate, NULL },
	// Game Over
	{ SceneGameOverInit, SceneGameOverUpdate, NULL },
	// Credits
	{ SceneCreditsInit, SceneCreditsUpdate, NULL },
};

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//----------------------------------------------------------------------------*/
// Determine if the scene is valid.
bool SceneIsValid(SCENE scene)
{
	return ((0 <= scene) && (scene < SCENE_MAX));
}

//----------------------------------------------------------------------------*/
// Execute the Init function for the current scene.
void SceneExecuteInit(SCENE scene)
{
	// First validate the scene and the function pointer.
	if (SceneIsValid(scene) &&
		((*SceneTable[scene].sceneInit) != NULL))
	{
		// Execute the Init function.
		(*SceneTable[scene].sceneInit)();
	}
}

//----------------------------------------------------------------------------*/
// Execute the Update function for the current scene.
void SceneExecuteUpdate(SCENE scene)
{
	// First validate the scene and the function pointer.
	if (SceneIsValid(scene) &&
		((*SceneTable[scene].sceneUpdate) != NULL))
	{
		// Execute the Update function.
		(*SceneTable[scene].sceneUpdate)();
	}
}

//----------------------------------------------------------------------------*/
// Execute the Exit function for the current scene.
void SceneExecuteExit(SCENE scene)
{
	// First validate the scene and the function pointer.
	if (SceneIsValid(scene) &&
		((*SceneTable[scene].sceneExit) != NULL))
	{
		// Execute the Exit function.
		(*SceneTable[scene].sceneExit)();
	}
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

