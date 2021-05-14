//---------------------------------------------------------
// file:	SceneManager.c
// author:	Garry Chen
// brief:	Basic scene management system
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "SceneManager.h"
#include "SceneTable.h"
#include <stdio.h>
#include <stdbool.h>

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

typedef struct
{
	SCENE	current;	// Index of the current scene.
	SCENE	previous;	// Index of the previous scene.
	SCENE	next;		// Index of the next scene.

} SceneTrackingData;

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------

static SceneTrackingData sceneTracking;

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

static bool	SceneIsChanging();

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the scene manager.
void SceneManagerInit()
{
	size(1280, 720);
	// Set the current scene to invalid.
	sceneTracking.current = SCENE_INVALID;

	// Set the initial scene to launch the game.
	sceneTracking.next = SCENE_INITIAL;
}

//---------------------------------------------------------
// Update the scene manager.
void SceneManagerUpdate()
{
	if (SceneIsChanging())
	{
		// Exit the current scene.
		SceneExecuteExit(sceneTracking.current);

		// Assign the new scene value.
		sceneTracking.current = sceneTracking.next;

		// Initialize the new scene.
		SceneExecuteInit(sceneTracking.current);
	}

	// Update the current scene.
	SceneExecuteUpdate(sceneTracking.current);
}

//---------------------------------------------------------
// Set the next scene to run.
void SceneManagerSetNextScene(SCENE nextScene)
{
	if (SceneIsValid(nextScene))
	{
		sceneTracking.next = nextScene;
	}
#ifdef _DEBUG
	else
	{
		// In debug mode, print a message that an error has occurred.
		printf("\nERROR: Invalid scene: %d\n", nextScene);
	}
#endif
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Determine if a scene change has been requested.
static bool	SceneIsChanging()
{
	return (sceneTracking.current != sceneTracking.next);
}
