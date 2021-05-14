//---------------------------------------------------------
// file:	Scene_MainMenu.h
// author:	Garry Chen
// brief:	Main menu scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------
typedef struct 
{
	float x, y;
	float width, height;
	PColor color;
	int state;
	char text[20];

} BUTTON;
//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

void SceneMainMenuInit();
void SceneMainMenuUpdate();
static void updateData();
static void updateButton(BUTTON *b);
static void initButton(BUTTON *b, float x, float y, float width, float height, PColor color, int state, char *str);
static void drawButton(BUTTON *b);
static void drawScene();
static void drawBunny(float x, float y);