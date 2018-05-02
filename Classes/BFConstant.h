/*
 * BFConstant.h
 *
 *  Created on: 01.05.2018
 *      Author: User
 */

#ifndef __BFConstant_H__
#define __BFConstant_H__

enum enumBFSceneGame {
	TAG_PLAYER = 1,
	TAG_ENEMY,
	TAG_BUBBLE,
	TAG_GAME_ACTION = 1000,
};

#define LEFT_EDGE_DESCTOP 0
#define RIGHT_EDGE_DESCTOP 960.0f
#define LOW_EDGE_DESCTOP 0
#define TOP_EDGE_DESCTOP 640.0f

#define CCCA(x)   (x->copy()->autorelease())

#endif __BFConstant_H__