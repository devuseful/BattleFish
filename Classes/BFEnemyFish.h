/*
 * BFEnemyFish.h
 *
 *  Created on: 01.05.2018
 *      Author: User
 */


#ifndef __BFEnemyFish_H__
#define __BFEnemyFish_H__


#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


class BFEnemyFish : public CCObject
{
public:

	BFEnemyFish(CCSprite *enemySprite);
	static BFEnemyFish* create(CCSprite *enemySprite);

	bool isTouchEnemy(CCPoint posfinger);
	void setDeadEnemy();
	bool isDeadEnemy();

	virtual ~BFEnemyFish();

protected:

	float angle_;
	bool isDead_;
	CCSprite *enemySprite_;

};



#endif // __BFEnemyFish_H__
