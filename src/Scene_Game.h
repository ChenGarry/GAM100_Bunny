//---------------------------------------------------------
// file:	Scene_GameOver.h
// author:	Garry Chen
// brief:	Game scene functions
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
static struct character {
	int face_left;			// True if character facing left, false if facing right.
	int in_air;			    // Store three value: jump up, fall down, on the ground.
	vec2_t position;		// Store position x and y;
	float width, height;	// Whole character's hitbox width and height.
	vec2_t velocity;			// Character's delta movement.
	float jump_y;			// Store character's jump starting point.(Use for jumping, before i finishing collision.)
} *Character;

typedef struct {
	vec2_t position;
	float width, height;
} PLATFORM;

typedef struct {
	vec2_t position;
	float r;
	vec2_t velocity;
} PROJECTILE;

//---------------------------------------------------------
// Public Variables:
//---------------------------------------------------------

//---------------------------------------------------------
// Public Functions:
//---------------------------------------------------------

void SceneGameInit();
void SceneGameUpdate();
