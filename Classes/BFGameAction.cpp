/*
 * BFGameAction.cpp
 *
 *  Created on: 01.05.2018
 *      Author: User
 */


#include "BFGameAction.h"


BFGameAction::BFGameAction() {
	// TODO Auto-generated constructor stub
	position_ = CCPointZero;
	scale_ = ccp(1, 1);
	isTouch_ = false;
	CCLog("BFGameAction()");

}

BFGameAction::~BFGameAction() {
	// TODO Auto-generated destructor stub
	CCLog("~BFGameAction()");
}

bool BFGameAction::init() {

	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	return true;
}

void BFGameAction::setGameScale(CCPoint scale) {
	scale_ = scale;
}


bool BFGameAction::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	position_ = pTouch->getLocation();
	isTouch_ = true;
	return true;
}


void BFGameAction::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
	position_ = pTouch->getLocation();
	isTouch_ = true;
}


void BFGameAction::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
	isTouch_ = false;
}


void BFGameAction::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
	isTouch_ = false;
}


void BFGameAction::onEnter() {
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
		this, 0, true);
}

void BFGameAction::onExit() {
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCPoint BFGameAction::getPositionFinger() {

	if (!isTouch_)
		return CCPointZero;

	float x = position_.x / scale_.x - RIGHT_EDGE_DESCTOP / 2;
	float y = position_.y / scale_.y - TOP_EDGE_DESCTOP / 2;
	//CCLog("ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) = x = %f, y = %f", x, y);
	return ccp(x, y);
}