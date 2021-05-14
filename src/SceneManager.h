//---------------------------------------------------------
// file:	SceneManager.h
// author:	Garry Chen
// brief:	Basic scene management system
//
// Copyright © 2018 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include "SceneTable.h"

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
// Public Functions:
//---------------------------------------------------------

void SceneManagerInit();
void SceneManagerUpdate();

// Tell the Scene Manager to Change States
void SceneManagerSetNextScene(SCENE nextScene);
