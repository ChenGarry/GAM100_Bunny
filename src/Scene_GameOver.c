//---------------------------------------------------------
// file:	Scene_DigiPenLogo.c
// author:	Garry Chen
// brief:	Game over scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_GameOver.h"
#include "SceneManager.h"
#include <time.h>
#include "GameManager.h"

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
static clock_t start_t;
static PSound clap_s;
static float score;

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SceneGameOverInit()
{
	start_t = clock();
	textSize(40);
	clap_s = loadSound("./Assets/Crowds-Medium-ApplauseCheer.wav", 0);
	sound(clap_s);
	score = (float)time_score / CLOCKS_PER_SEC;
}

//---------------------------------------------------------
// Update the DigiPen Logo scene.
void SceneGameOverUpdate()
{
	char str[100];
	int sec = 10 - (clock() - start_t) / CLOCKS_PER_SEC;

	background(30, 30, 30);
	fill(255, 255, 255, 255);
	sprintf_s(str, 100, "You survive %.2f sec", score);
	text(str, canvasWidth / 2 - 130, 80);
	text("Press R to try again", canvasWidth/2 - 120, 160);
	sprintf_s(str, 100, "... %i", sec);
	text(str, canvasWidth/2 - 50, 240);
	text("Press Enter to end the game", canvasWidth / 2 - 180, 320);

	if (keyPressed(KEY_R))
	{
		SceneManagerSetNextScene(SCENE_GAME);
	}
	if (keyPressed(KEY_ENTER) || sec < 0)
	{
		SceneManagerSetNextScene(SCENE_CREDITS);
	}

}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

