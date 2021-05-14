//---------------------------------------------------------
// file:	Scene_DigiPenLogo.c
// author:	Garry Chen
// brief:	Game scene functions
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "C_Processing.h"
#include "Scene_Game.h"
#include "SceneManager.h"
#include <math.h>
#include "GameManager.h"

//---------------------------------------------------------
// Private Consts:
//---------------------------------------------------------
#define PROJ_COUNT 10
#define PLAT_COUNT 9
#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

typedef enum
{
	COLLIDE_NONE,
	COLLIDE_TOP,
	COLLIDE_BOTTOM,
	COLLIDE_LEFT,
	COLLIDE_RIGHT
}collision_dr;
//---------------------------------------------------------
// Private Structures:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Private Variables:
//---------------------------------------------------------
static PImage carrot;
static PLATFORM platforms[PLAT_COUNT];
static PROJECTILE projectiles[PROJ_COUNT];
static PSound jump_sound;
static time_t start_t;

//---------------------------------------------------------
// Private Function Declarations:
//---------------------------------------------------------
static void drawScene();
static void drawCharacter();
static void initPlatform(int i, float x, float y, float w, float h);
static void initprojectile(int i, float x, float y, float r, float dx, float dy);
static void takeInput();
static void drawPlatform();
static void drawprojectile();
static void updateData();
static void objectsMove();
static void checkCollision();
static bool circleRectCollision(float cx, float cy, float cr, float rx, float ry, float rw, float rh);
static bool circlesCollision(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r);
static bool rectsCollision(float rect1x, float rect1y, float rect1w, float rect1h, 
						   float rect2x, float rect2y, float rect2w, float rect2h);
static vec2_t findIntersect(vec2_t p1, vec2_t p2, vec2_t q1, vec2_t q2);
//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

//---------------------------------------------------------
// Initialize the DigiPen Logo scene.
void SceneGameInit()
{
	int i;

	start_t = clock();
	// Initialize the main character.
	Character = malloc(sizeof(struct character));
	Character->width = 40;
	Character->height = 22;
	Character->position.x = (canvasWidth - Character->width) / 2;
	Character->position.y = canvasHeight - Character->height - 150;
	Character->jump_y = Character->position.y;
	Character->face_left = 1;
	Character->in_air = -1;
	Character->velocity.x = 0;
	Character->velocity.y = 10;


	// Build borders and one platform.
	initPlatform(0, 0, 0, canvasWidth, 10);
	initPlatform(1, 0, 0, 10, canvasHeight);
	initPlatform(2, 0, canvasHeight - 10, canvasWidth, canvasHeight);
	initPlatform(3, canvasWidth - 10, 0, canvasWidth, canvasHeight);
	initPlatform(4, (canvasWidth / 2) - 100, canvasHeight - 100, 200, 10);
	initPlatform(5, (canvasWidth / 2) - 500, canvasHeight - 100, 200, 10);
	initPlatform(6, (canvasWidth / 2) + 300, canvasHeight - 100, 200, 10);
	initPlatform(7, (canvasWidth / 2) - 200, canvasHeight - 200, 200, 10);
	initPlatform(8, (canvasWidth / 2) + 200, canvasHeight - 200, 200, 10);

	// Initialize projectials.
	for (i = 0; i < PROJ_COUNT; i++)
	{
		int signx = 1, signy = 1;
		if (randomRange(-1, 1) < 0)
			signx = -1;
		if (randomRange(-1, 1) < 0)
			signy = -1;
		initprojectile(i, randomRange(20, canvasWidth - 20), randomRange(20, 50), 10, randomRange(5 , 10) * signx, randomRange(5, 10) * signy);
	}

	// Load image resources.
	carrot = loadImage("./Assets/carrot.jpg");
	jump_sound = loadSound("./Assets/Cartoons-MouthHarp-CU-Hig_6.wav",0);
}

//---------------------------------------------------------
// Update the Game scene.
void SceneGameUpdate()
{
	takeInput();
	updateData();
	drawScene();
	
}

//---------------------------------------------------------
// Private Functions:
//---------------------------------------------------------
static void drawScene()
{
	background(30, 30, 30);
	drawCharacter();
	drawPlatform();
	drawprojectile();
	fill(255, 0, 0, 255);
	// draw the text
	text("z = dash, x = jump", 20, 40);
	text("Press M to open menu", 20, 80);
	text("Press enter to gameover", 20, 120);
}

static void drawCharacter()
{
	// Draw character facing two direction.
	if (Character->face_left == 1)
	{
		fill(255, 255, 255, 255);
		noStroke();
		ellipse(Character->position.x + 20, Character->position.y + 10, 20, 11);
		noStroke();
		ellipseRotated(Character->position.x + 35, Character->position.y - 4, 5, 10, 60);
		ellipseRotated(Character->position.x + 15, Character->position.y - 5, 5, 10, 45);
		fill(200, 0, 0, 255);
		rect(Character->position.x + 12, Character->position.y + 5, 4, 8);
		rect(Character->position.x + 20, Character->position.y + 5, 4, 8);

	}
	else if (Character->face_left == 0)
	{
		fill(255, 255, 255, 255);
		noStroke();
		ellipse(Character->position.x + 20, Character->position.y + 10, 20, 11);
		noStroke();
		ellipseRotated(Character->position.x + 25, Character->position.y - 5, 5, 10, 135);
		ellipseRotated(Character->position.x + 5, Character->position.y - 4, 5, 10, 120);
		fill(200, 0, 0, 255);
		rect(Character->position.x + 24, Character->position.y + 5, 4, 8);
		rect(Character->position.x + 16, Character->position.y + 5, 4, 8);
	}
}

// Initialize a platform.
static void initPlatform(int i, float x, float y, float w, float h)
{
	platforms[i].position.x = x;
	platforms[i].position.y = y;
	platforms[i].width = w;
	platforms[i].height = h;
}

void initprojectile(int i, float x, float y, float r, float dx, float dy)
{
	projectiles[i].position.x = x;
	projectiles[i].position.y = y;
	projectiles[i].r = r;
	projectiles[i].velocity.x = dx;
	projectiles[i].velocity.y = dy;
}

// All in game input dealt here
static void takeInput()
{
	int speed = 2; // Speed modifier.
	// Press enter to go to gameover state.

	if (keyIsDown(KEY_ENTER))
	{
		SceneManagerSetNextScene(SCENE_GAMEOVER);
	}
	else if (keyPressed(KEY_M))
	{
		SceneManagerSetNextScene(SCENE_MAIN_MENU);
	}
	// Press R to restart the game.
	if (keyIsDown(KEY_R))
	{
		SceneGameInit();
		return;
	}
	// Press Z to dash.
	if (keyPressed(KEY_Z))
	{
		Character->in_air = -1;
		Character->velocity.y = 10;
		speed = 12;
	}
		
	// Press left key to move left, right key to moce right.
	if (keyIsDown(KEY_LEFT))
	{
		Character->face_left = 1;
		Character->velocity.x = -5 * speed;
	}
	else if (keyIsDown(KEY_RIGHT))
	{
		Character->face_left = 0;
		Character->velocity.x = 5 * speed;
	}
	else
		Character->velocity.x = 0;
	// Press X to jump.
	if (Character->in_air == 0)
	{
		Character->velocity.y = 10;
		if (keyIsDown(KEY_X))
		{
			Character->in_air = 1; // Change character in_air to jump up.
			Character->jump_y = Character->position.y; // Save jump_y.
			sound(jump_sound);
		}
	}
	if (Character->in_air == 1)
	{
		Character->velocity.y = -10;
		if (Character->jump_y - 140 >= Character->position.y) // Jump limit is 140 pixel.
			Character->in_air = -1;
	}
	if (Character->in_air == -1)
	{
		Character->velocity.y = 10;
	}
	
}

// Draw platforms from platform array.
static void drawPlatform()
{
	int i;
	fill(0, 255, 0, 255);
	for (i = 0; i < PLAT_COUNT; i++)
		rect(platforms[i].position.x , platforms[i].position.y, platforms[i].width , platforms[i].height);
}

void drawprojectile()
{
	int i;
	fill(255,0,0,255);
	for (i = 0; i < PROJ_COUNT; i++)
		circle(projectiles[i].position.x , projectiles[i].position.y , projectiles[i].r);
}

static void updateData()
{
	checkCollision();
	objectsMove();
}

static void checkCollision()
{
	int i, j;
	int flag[PROJ_COUNT][2];
	for (i = 0; i < PROJ_COUNT; i++)
	{
		flag[i][0] = 1;
		flag[i][1] = 1;
	}
	for (i = 0; i < PROJ_COUNT; i++)
	{
		
		for (j = i + 1; j < PROJ_COUNT; j++)
		{

			if (circlesCollision(projectiles[i].position.x + projectiles[i].velocity.x, projectiles[i].position.y + projectiles[i].velocity.y, projectiles[i].r,
				projectiles[j].position.x + projectiles[j].velocity.x, projectiles[j].position.y + projectiles[j].velocity.y, projectiles[j].r))
			{
				int sx = 1, sy = 1;
				if (projectiles[i].velocity.x * projectiles[j].velocity.x < 0)
					sx = -1;
				if (projectiles[i].velocity.y * projectiles[j].velocity.y < 0)
					sy = -1;
				flag[i][0] = sx;
				flag[i][1] = sy;
				flag[j][0] = sx;
				flag[j][1] = sy;
			}
		}
		for (j = 0; j < PLAT_COUNT; j++)
		{
			if (circleRectCollision(projectiles[i].position.x + projectiles[i].velocity.x, projectiles[i].position.y + projectiles[i].velocity.y, projectiles[i].r,
				platforms[j].position.x, platforms[j].position.y, platforms[j].width, platforms[j].height))
			{
				if (projectiles[i].position.x <= platforms[j].position.x || projectiles[i].position.x >= platforms[j].position.x + platforms[j].width)
				{
					flag[i][0] = -1;
				}
				if (projectiles[i].position.y <= platforms[j].position.y || projectiles[i].position.y >= platforms[j].position.y + platforms[j].height)
				{
					flag[i][1] = -1;
				}
			}
		}
	}
	for (i = 0; i < PROJ_COUNT; i++)
	{
		projectiles[i].velocity.x *= flag[i][0];
		projectiles[i].velocity.y *= flag[i][1];
	}

	for (i = 0; i < PLAT_COUNT; i++)
	{
		float x1_min = Character->position.x;
		float x1_max = Character->position.x + Character->width;
		float y1_min = Character->position.y;
		float y1_max = Character->position.y + Character->height;
		if (rectsCollision(Character->position.x + Character->velocity.x , Character->position.y + Character->velocity.y, Character->width, Character->height,
			platforms[i].position.x , platforms[i].position.y , platforms[i].width , platforms[i].height))
		{
			
			float x2_min = platforms[i].position.x;
			float x2_max = platforms[i].position.x + platforms[i].width;
			float y2_min = platforms[i].position.y;
			float y2_max = platforms[i].position.y + platforms[i].height;
			vec2_t tmp1, tmp2;
			vec2_t intersection;
			if (x1_max <= x2_min)
			{
				if (y1_max <= y2_min)
				{
					tmp1.x = x1_max;
					tmp1.y = y1_max;
					tmp2.x = x2_max;
					tmp2.y = y2_min;
					intersection = findIntersect(tmp1, vec2_add(tmp1, Character->velocity), platforms[i].position, tmp2);
					if (intersection.x == -1)
					{
						tmp2.x = x2_min;
						tmp2.y = y2_max;
						intersection = findIntersect(tmp1, tmp1, platforms[i].position, tmp2);
					}
					Character->velocity.x = intersection.x - tmp1.x;
					Character->velocity.y = intersection.y - tmp1.y;
				}
				/*else if (y1_min >= y2_max)
				{

				}
				else
				{

				}*/
			}
			//else if (x1_min >= x2_max)
			//{
			//	if (y1_max <= y2_min)
			//	{

			//	}
			//	else if (y1_min >= y2_max)
			//	{

			//	}
			//	else
			//	{

			//	}
			//}

			if (Character->position.y + Character->height <= platforms[i].position.y)
			{
				Character->in_air = 0;
				Character->velocity.y = 0;
			}
			else if (Character->position.y > platforms[i].position.y + platforms[i].height)
			{
				Character->in_air = -1;
				Character->velocity.y = 10;
			}
		}
		
	}
	for (i = 0; i < PROJ_COUNT; i++)
	{
		if (circleRectCollision(projectiles[i].position.x + projectiles[i].velocity.x , projectiles[i].position.y + projectiles[i].velocity.y, projectiles[i].r,
			Character->position.x + Character->velocity.x, Character->position.y + Character->velocity.y, Character->width, Character->height))
		{
			time_score = clock() - start_t;
			SceneManagerSetNextScene(SCENE_GAMEOVER);
		}
	}
}

static vec2_t findIntersect(vec2_t p1, vec2_t p2, vec2_t q1, vec2_t q2)
{
	vec2_t tmp;
	float a1 = p2.y - p1.y;
	float b1 = p1.x - p2.x;
	float c1 = a1 * p1.x + b1 * p1.y;
	float a2 = q2.y - q1.y;
	float b2 = q1.x - q2.x;
	float c2 = a2 * q1.x + b2 * q1.y;

	float determinant = a1 * b2 - a2 * b1;

	if (determinant == 0)
	{
		tmp.x = -1;
		tmp.y = -1;
	}
	else
	{
		tmp.x = (b2*c1 - b1 * c2) / determinant;
		tmp.y = (a1*c2 - a2 * c1) / determinant;
		if (!(MIN(q1.x, q2.x) <= tmp.x && tmp.x <= MAX(q1.x, q2.x) && MIN(q1.y, q2.y) <= tmp.y && tmp.y <= MAX(q1.y, q2.y)))
		{
			tmp.x = -1;
			tmp.y = -1;
		}
	}
	return tmp;
}

static void objectsMove()
{
	int i;
	Character->position.x += Character->velocity.x;
	Character->position.y += Character->velocity.y;
	for (i = 0; i < PROJ_COUNT; i++)
	{
		projectiles[i].position.x += projectiles[i].velocity.x;
		projectiles[i].position.y += projectiles[i].velocity.y;
	}
}

static bool rectsCollision(float rect1x, float rect1y, float rect1w, float rect1h, float rect2x, float rect2y, float rect2w, float rect2h)
{
	return (rect1x < rect2x + rect2w &&
		rect1x + rect1w > rect2x &&
		rect1y < rect2y + rect2h &&
		rect1h + rect1y > rect2y);
}

static bool circleRectCollision(float cx, float cy, float cr, float rx, float ry, float rw, float rh)
{
	float dx;
	float dy;
	float nearest_x = MAX(rx, MIN(cx, rx + rw));
	float nearest_y = MAX(ry, MIN(cy, ry + rh));
	dx = nearest_x - cx;
	dy = nearest_y - cy;

	return (cr * cr >= dx * dx + dy * dy);
}

static bool circlesCollision(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{
	float dx = c1x - c2x;
	float dy = c1y - c2y;
	float D = c1r + c2r;
	return (D * D >= dx * dx + dy * dy);
}

static int rectsCollideDir()
{

}