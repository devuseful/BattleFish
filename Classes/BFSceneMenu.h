#ifndef __BFSceneMenu_H__
#define __BFSceneMenu_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BFConstant.h"
#include "BFSceneGame.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;


class BFSceneMenu : public cocos2d::CCLayer
{

	enum enumBFSceneMenu {
	TAG_INPUTTEXT_LAYER = 1,
	}; 


public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void keyBackClicked(void);

    // implement the "static node()" method manually
    CREATE_FUNC(BFSceneMenu);

	virtual ~BFSceneMenu();

protected:

	void _callbackStartAnimation(CCNode * Node);
	void _onTouchButton(CCObject* pSender, TouchEventType type);

};

#endif // __BFSceneMenu_H__
