/*
 * BFMoveBubble.cpp
 *
 *  Created on: 01.05.2018
 *      Author: User
 */

#include "BFMoveBubble.h"
#include "BFEnemyFish.h"


BFMoveBubble::BFMoveBubble(CCSprite *bubbleSprite) {
	CCLog("BFMoveBubble()");
	bubbleSprite_ = bubbleSprite;
}


BFMoveBubble* BFMoveBubble::create(CCSprite *bubbleSprite) {
	
	BFMoveBubble* bubble = new BFMoveBubble(bubbleSprite);
	if (bubble)
	{
		bubble->autorelease();
		return bubble;
	}
	CC_SAFE_DELETE(bubble);
	return NULL;
}


BFMoveBubble::~BFMoveBubble() {
	CCLog("~BFMoveBubble()");
}


void BFMoveBubble::updateBubble() {

	bool isRemove = false;
	CCSprite *background = (CCSprite *)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0)->getChildByTag(0)->getChildByTag(10003);

	CCArray *children = background->getChildren();
	for (size_t i = 0; i < children->count(); i++) {

		CCSprite *spriteObject = dynamic_cast<CCSprite *>(children->objectAtIndex(i));
		if (spriteObject && spriteObject->getTag() == TAG_ENEMY) {
			BFEnemyFish *enemyFishObject = static_cast<BFEnemyFish *>(spriteObject->getUserObject());
			if (enemyFishObject->isTouchEnemy(bubbleSprite_->getPosition())) {
				enemyFishObject->setDeadEnemy();
				isRemove = true;
			}
		}
	}

	if (isRemove)
		bubbleSprite_->removeFromParent();
}