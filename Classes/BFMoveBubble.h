/*
 * BFMoveBubble.h
 *
 *  Created on: 01.05.2018
 *      Author: User
 */


#ifndef __BFMoveBubble_H__
#define __BFMoveBubble_H__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "BFConstant.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


class BFMoveBubble : public CCObject
{
public:

	BFMoveBubble(CCSprite *bubbleSprite);
	static BFMoveBubble* create(CCSprite *bubbleSprite);

	void updateBubble();

	virtual ~BFMoveBubble();

protected:

	CCSprite *bubbleSprite_;

};



#endif // __BFMoveBubble_H__
