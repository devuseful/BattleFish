/*
 * BFPlayerFish.h
 *
 *  Created on: 01.05.2018
 *      Author: User
 */


#ifndef __BFPlayerFish_H__
#define __BFPlayerFish_H__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "BFMoveBubble.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


class BFPlayerFish : public CCObject
{
public:
	
	BFPlayerFish(CCArmature *playerArmature);
	static BFPlayerFish* create(CCArmature *playerArmature);

	void updatePlayer(CCPoint posfinger);
	void createFire(CCPoint pos);

	virtual ~BFPlayerFish();

protected:

	void _addMoveBuble(CCPoint pos);
	void _onAnimationEvent(CCArmature *pArmature, MovementEventType eventType, const char *animationID);

	float angle_;
	bool isFire_;
	bool isReady_;

	CCArmature *playerArmature_;

};



#endif // __BFPlayerFish_H__
