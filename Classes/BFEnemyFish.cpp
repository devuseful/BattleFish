/*
 * BFEnemyFish.cpp
 *
 *  Created on: 01.05.2018
 *      Author: User
 */

#include "BFEnemyFish.h"


BFEnemyFish::BFEnemyFish(CCSprite *enemySprite) {
	CCLog("BFEnemyFish()");
	enemySprite_ = enemySprite;
	angle_ = enemySprite_->getRotation();
	isDead_ = false;
}


BFEnemyFish* BFEnemyFish::create(CCSprite *enemySprite) {
	
	BFEnemyFish* enemy = new BFEnemyFish(enemySprite);
	if (enemy)
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}


BFEnemyFish::~BFEnemyFish() {
	CCLog("~BFEnemyFish()");
}


bool BFEnemyFish::isTouchEnemy(CCPoint posfinger) {
	if (this->isDeadEnemy())
		return false;

	float scale = enemySprite_->getScale();
	CCPoint curPos = enemySprite_->getPosition();
	CCSize size = enemySprite_->getContentSize();
	return (curPos.x - size.width / 2 * scale) < posfinger.x 
		&& (curPos.x + size.width / 2 * scale) > posfinger.x 
		&& (curPos.y - size.height / 2 * scale) < posfinger.y 
		&& (curPos.y + size.height / 2 * scale) > posfinger.y;
}

void BFEnemyFish::setDeadEnemy() {
	isDead_ = true;
	float duration = 0.1f;
	CCSequence *seq = CCSequence::create(CCFadeIn::create(duration), CCRemoveSelf::create(), nullptr);
	enemySprite_->runAction(seq);
}

bool BFEnemyFish::isDeadEnemy() {
	return isDead_;
}