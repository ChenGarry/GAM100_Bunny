//---------------------------------------------------------
// file:	Scene_Credits.c
// author:	Garry Chen
// brief:	Credits scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_Credits.h"
#include "SceneManager.h"
#include <time.h>

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------
PImage credits;
static clock_t start_t;

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the Credits scene.
void SceneCreditsInit()
{
	start_t = clock();
	credits = loadImage("./Assets/credits.jpg");
}

//---------------------------------------------------------
// Update the Credits scene.


void SceneCreditsUpdate()
{
	int sec = 10 - (clock() - start_t) / CLOCKS_PER_SEC;
	image(credits, canvasWidth/2, canvasHeight/2, canvasWidth, canvasHeight);
	fill(255, 255, 255, 255);
	text("Press R return to menu", 20, 40);
	text("", 20, 80);

	if (keyPressed(KEY_R))
	{
		SceneManagerSetNextScene(SCENE_MAIN_MENU);
	}
	if (sec < 0)
	{
		SceneManagerSetNextScene(SCENE_MAIN_MENU);
	}

}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

