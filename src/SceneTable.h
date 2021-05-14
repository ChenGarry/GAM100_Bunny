//---------------------------------------------------------
// file:	SceneTable.h
// author:	Garry Chen
// brief:	Table of scene values and options
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include <stdbool.h>

typedef enum
{
	// Special Game States
	SCENE_INVALID = -1,

	// Normal Game States:
	SCENE_DIGIPEN_LOGO,
	SCENE_MAIN_MENU,
	SCENE_GAME,
	SCENE_GAMEOVER,
	SCENE_CREDITS,

	// Bookkeeping States:
	SCENE_MAX,

	// Specify the initial game state
	SCENE_INITIAL = SCENE_DIGIPEN_LOGO,

} SCENE;

//---------------------------------------------------------
// Public Structures:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

// Determine if the game state is valid.
extern bool SceneIsValid(SCENE gameState);

// Execute the Init function for the current game state.
extern void SceneExecuteInit(SCENE gameState);

// Execute the Update function for the current game state.
extern void SceneExecuteUpdate(SCENE gameState);

// Execute the Exit function for the current game state.
extern void SceneExecuteExit(SCENE gameState);

//---------------------------------------------------------

