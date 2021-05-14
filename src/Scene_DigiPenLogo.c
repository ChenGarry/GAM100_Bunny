//---------------------------------------------------------
// file:	Scene_DigiPenLogo.c
// author:	Garry Chen
// brief:	DigiPen Logo scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_DigiPenLogo.h"
#include "SceneManager.h"
#include <time.h>
#include <stdio.h>
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
static clock_t start_t; // Start time of this scene
static PImage digipen_logo;
static float star_array[10][6];
static float fadeA, fade_txt;
//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------
static void star__shape(float x, float y, float scale, float degreed)
{
	beginShape();
	noStroke();
	// Original star shape vertex positions
	vec2_t position[11] = { 0, -50, 14, -20 , 47, -15 , 23, 7 , 29, 40 , 0, 25 , -29, 40 , -23, 7 , -47, -15 , -14, -20, x, y };
	int i;

	// Scale, roatate and center to position (x,y) then drew the point.
	for (i = 0; i < 10; i++)
	{
		position[i] = vec2_scale(position[i], scale);
		position[i] = mat3_mult_vec2(mat3_rotate(degreed), position[i]);
		position[i] = vec2_add(position[i], position[10]);
		vertex(position[i].x, position[i].y);
	}
	endShape();
}

static void init_star_array(int indics)
{
	// Initial position to be ranfom top left position.
	star_array[indics][0] = randomRange(-40 - canvasWidth, canvasHeight - 40); // Position x
	star_array[indics][1] = randomRange(-50.0, 0);                        // Position y
	// Initial star__shape's input data
	star_array[indics][2] = randomRange(0.5, 1.0);                         // scaling rate
	star_array[indics][3] = 0;                                            // Current roatate degreed
	star_array[indics][4] = randomRange(5, 10);                           // Roataion speed
	star_array[indics][5] = randomRange(0.5, 1.5);                         // Moving speed scaling
}
//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SceneDigiPenLogoInit()
{
	int i;
	textSize(40);
	// Store current time to be start time.
	start_t = clock();
	fadeA = 1.0;
	fade_txt = 0;
	digipen_logo = loadImage("./Assets/DigiPen_WHITE_1024px.png");
	for (i = 0; i < 10; i++)
		init_star_array(i);
}

//---------------------------------------------------------
// Update the DigiPen Logo scene.
void SceneDigiPenLogoUpdate()
{
	 // Sec is the time passed in second after the start time.
	float sec = (float)(clock() - start_t) / CLOCKS_PER_SEC;
	background(0, 0, 0);
	if (sec < 2)
	{
		image(digipen_logo, canvasWidth / 2, canvasHeight / 2, 780, 190);
	}
	else if (sec < 10 && sec > 2)
	{
		int i;
		if (fadeA >= 0)
		{
			imageAlpha(digipen_logo, canvasWidth / 2, canvasHeight / 2, 780, 190, fadeA);
			fadeA -= 0.01f;
		}
		else
		{
			text("Press Enter To Continue", canvasWidth / 2 - 170, canvasHeight / 2 - 5);
		}
		for (i = 0; i < 10; i++)
		{
			star__shape(star_array[i][0], star_array[i][1], star_array[i][2], star_array[i][3]);
			// New degreed = current degreed + roatate speed
			star_array[i][3] += star_array[i][4];
			// New position = current position + speed scaling * base speed 
			star_array[i][0] += star_array[i][5] * 5;
			star_array[i][1] += star_array[i][5] * 4;
			// Initial star_array[i] if current one is out of bound
			if (star_array[i][0] > canvasWidth + 50 || star_array[i][1] > canvasHeight + 50)
				init_star_array(i);
		}
		if(keyIsDown(KEY_ENTER))
			SceneManagerSetNextScene(SCENE_MAIN_MENU);
	}
	else
		SceneManagerSetNextScene(SCENE_MAIN_MENU);
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------

