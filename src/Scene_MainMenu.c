//---------------------------------------------------------
// file:	Scene_MainMenu.c
// author:	Garry Chen
// brief:	Main menu scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_MainMenu.h"
#include "SceneManager.h"
#include "Engine.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static BUTTON start_b;
static BUTTON exit_b;
static BUTTON credit_b;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Initialize the scene manager.
void SceneMainMenuInit()
{
	PColor color1 = { 150, 150, 150, 150 };
	initButton (&start_b , canvasWidth / 2 - 80, 350, 160, 80, color1, 0, "Start");
	initButton(&exit_b, canvasWidth / 2 - 120, 570, 240, 80, color1, 0 ,"Exit Game");
	initButton(&credit_b, canvasWidth / 2 - 85, 460, 170, 80, color1, 0, "Credit");
	
}

//------------------------------------------------------------------------------
// Update the scene manager.
void SceneMainMenuUpdate()
{
	updateData();
	drawScene();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
static void updateData()
{
	updateButton(&start_b);
	if(start_b.state == 3)
		SceneManagerSetNextScene(SCENE_GAME);
	updateButton(&credit_b);
	if(credit_b.state == 3)
		SceneManagerSetNextScene(SCENE_CREDITS);
	updateButton(&exit_b);
	if (exit_b.state == 3)
		Terminate();
}

static void updateButton(BUTTON *b)
{
	if (pointInRect(mouseX, mouseY, b->x, b->y, b->width, b->height))
	{
		b->state = 1;
		if (mouseIsDown(MOUSE_BUTTON_LEFT))
		{
			b->state = 2;
		}
		if (mouseReleased(MOUSE_BUTTON_LEFT))
		{
			b->state = 3;
		}
	}
	else
	{
		b->state = 0;
	}
}

static void drawScene()
{
	background(0, 0, 0);
	fill(180, 180, 180, 255);
	textSize(160);
	text("Bunny Hops", canvasWidth / 2 - 340, 200);
	textSize(40);
	drawButton(&start_b);
	drawButton(&credit_b);
	drawButton(&exit_b);
	drawBunny(200, 180);
}

static void drawButton(BUTTON *b)
{
	float x, y;
	x = b->x;
	y = b->y;
	if (b->state == 0)
		fillColor(b->color);
	else if (b->state == 1)
	{
		fill(255, 255, 255, 255);
	}
	else if (b->state == 2)
	{
		fill(255, 255, 255, 255);
		x = b->x+4;
		y = b->y+4;
	}

	rect(x, y, b->width, b->height);
	fill(30, 30, 30, 255);
	text(b->text, x + 40, y + 50);
}

static void initButton(BUTTON *b, float x, float y, float width, float height, PColor color, int state, char *str)
{
	b->x = x;
	b->y = y;
	b->width = width;
	b->height = height;
	b->color = color;
	b->state = state;
	strcpy(b->text, str);
}

static void drawBunny(float x, float y)
{
	fill(255, 255, 255, 255);
	noStroke();
	ellipse(x + 20, y + 10, 20, 11);
	noStroke();
	ellipseRotated(x + 35, y - 4, 5, 10, 60);
	ellipseRotated(x + 15, y - 5, 5, 10, 45);
	fill(200, 0, 0, 255);
	rect(x + 12, y + 5, 4, 8);
	rect(x + 20, y + 5, 4, 8);
}