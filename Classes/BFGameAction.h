 /*
 * BFGameAction.cpp
 *
 *  Created on: 01.05.2018
 *      Author: User
 */


#ifndef __BFGameAction_H__
#define __BFGameAction_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BFConstant.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;


class BFGameAction: public cocos2d::CCLayer {
public:
	BFGameAction();

	virtual bool init();	

	virtual void onEnter();
	virtual void onExit();

	virtual ~BFGameAction();

	void setGameScale(CCPoint scale);

	CCPoint getPositionFinger();

	// implement the "static node()" method manually
    CREATE_FUNC(BFGameAction);

protected:

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	CCPoint position_;
	bool isTouch_;
	CCPoint scale_;

};

#endif // __BFGameAction_H__
