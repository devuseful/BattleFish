/*
 * BFPlayerFish.cpp
 *
 *  Created on: 01.05.2018
 *      Author: User
 */

#include "BFPlayerFish.h"


BFPlayerFish::BFPlayerFish(CCArmature *playerArmature) {
	CCLog("BFPlayerFish()");
	playerArmature_ = playerArmature;
	angle_ = playerArmature_->getRotation();
	isFire_ = false;
	isReady_ = false;
	playerArmature_->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(BFPlayerFish::_onAnimationEvent));
}


BFPlayerFish* BFPlayerFish::create(CCArmature *playerArmature) {
	
	BFPlayerFish* rocket = new BFPlayerFish(playerArmature);
	if (rocket)
	{
		rocket->autorelease();
		return rocket;
	}
	CC_SAFE_DELETE(rocket);
	return NULL;
}


BFPlayerFish::~BFPlayerFish() {
	CCLog("~BFPlayerFish()");
	playerArmature_ = nullptr;
}


void BFPlayerFish::updatePlayer(CCPoint posfinger) {

	if (posfinger.x == 0 && posfinger.y == 0)
		return;

	float angle = -CC_RADIANS_TO_DEGREES(posfinger.getAngle()) - 90;

	float diff = angle_ - angle;
	if (diff > 180)
		diff -= 360;

	if (fabs(diff) < 5) {
		isReady_ = true;
		return;
	}

	isReady_ = false;

	int sign = (diff > 0) - (diff < 0);

	angle_ -= sign * 2;
	if (fabs(angle_) > 360)
		angle_ += 360 * sign;

	playerArmature_->setRotation(angle_);
}


void BFPlayerFish::createFire(CCPoint pos) {
	if (isFire_ || !isReady_)
		return;
	
	isFire_ = true;
	playerArmature_->getAnimation()->playWithIndex(1);
	this->_addMoveBuble(pos);
}


void BFPlayerFish::_addMoveBuble(CCPoint pos) {
	
	float delay = 0.05f;
	float duration = 0.5f;
	CCSprite *background = (CCSprite *)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0)->getChildByTag(0)->getChildByTag(10003);
	CCSprite *bubbleSpite = CCSprite::createWithSpriteFrameName("image/bubble.png");
	bubbleSpite->setPosition(CCPointZero);
	BFMoveBubble *bubbleObject = BFMoveBubble::create(bubbleSpite);
	bubbleSpite->setUserObject(bubbleObject);
	background->addChild(bubbleSpite, 10, TAG_BUBBLE);
	bubbleSpite->setOpacity(0);
	bubbleSpite->setScale(0.5f);

	CCSpawn *spawn = CCSpawn::create(CCMoveTo::create(duration, pos), CCFadeIn::create(duration/4), nullptr);
	CCSequence *seq = CCSequence::create(CCDelayTime::create(delay), spawn, CCRemoveSelf::create(), nullptr);
	bubbleSpite->runAction(seq);
}


void BFPlayerFish::_onAnimationEvent(CCArmature *pArmature, MovementEventType eventType, const char *animationID) {

	if (eventType == COMPLETE) {
		if (strcmp(animationID, "Fire") == 0) {
			isFire_ = false;
			playerArmature_->getAnimation()->playWithIndex(0);
		}
	}

	if (eventType == LOOP_COMPLETE) {

	}
}


