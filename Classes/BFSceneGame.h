#ifndef __BFSceneGame_H__
#define __BFSceneGame_H__

#include "cocos2d.h"
#include "cocos-ext.h"
//#include "spine/Json.h"
#include "BFGameAction.h"
#include "BFPlayerFish.h"
#include "BFEnemyFish.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
//using namespace CocosDenshion;


class BFSceneGame : public cocos2d::CCLayer
{

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void keyBackClicked(void); // обработка кнопки назад

    // implement the "static node()" method manually
    CREATE_FUNC(BFSceneGame);

	virtual ~BFSceneGame();

protected:

	void _callbackStartAnimation(CCNode * Node);
	void _addPlayerFish();
	void _addEnemyFish(float dt);
	void _updateGame(float dt);
	bool _isPlayerCaught(CCArmature *player, CCSprite *enemy);
	void _returnScene();

};

#endif // __BFSceneGame_H__
