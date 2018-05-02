#include "BFSceneMenu.h"

#define DIFF_REPLACE 180
#define DIFF_CHANGE 30
#define DIFF_CHANGE_LIST 60
#define MAX_LINES 7

CCScene* BFSceneMenu::scene()
{

    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
	scene->setTag(2);
    
    // 'layer' is an autorelease object
    BFSceneMenu *layer = BFSceneMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->setTag(0);

    // return the scene
    return scene;
}


BFSceneMenu::~BFSceneMenu() {
	CCLog("~BFSceneMenu()");
	this->setKeypadEnabled(false);
}


// on "init" you need to initialize your instance
bool BFSceneMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	this->setKeypadEnabled(true);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
										"image/CloseNormal.png",
										"image/CloseSelected.png",
										this,
										menu_selector(BFSceneMenu::menuCloseCallback));
	   
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
								origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	// загрузить сцену из файла
	CCNode * pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scene/menu/Menu.json"); //cocos2dx 2.2
	this->addChild(pNode, 0, 0);
	// установка маштаба
	pNode->setScaleY(winSize.height / TOP_EDGE_DESCTOP);
	pNode->setScaleX(winSize.width / RIGHT_EDGE_DESCTOP);

	CCNode *menuNode = pNode->getChildByTag(10003);
	UILayer * menuLayer = (UILayer*)menuNode->getChildren()->objectAtIndex(0);
	UIButton *buttonStart = static_cast<UIButton *>(menuLayer->getWidgetByName("ButtonStart"));
	buttonStart->addTouchEventListener(this, toucheventselector(BFSceneMenu::_onTouchButton));

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("graphics/Objects0.plist");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/PlayerFish.ExportJson");

	CCSequence* seq = CCSequence::create(CCDelayTime::create(0.1f), CCCallFuncN::create(this, callfuncN_selector(BFSceneMenu::_callbackStartAnimation)), nullptr);
	this->runAction(seq);

	return true;
}



void BFSceneMenu::_callbackStartAnimation(CCNode * Node) {

	if (CCDirector::sharedDirector()->getRunningScene()->getTag() != 2) {
		CCSequence* seq = CCSequence::create(CCDelayTime::create(0.1f), CCCallFuncN::create(this, callfuncN_selector(BFSceneMenu::_callbackStartAnimation)), NULL);
		this->runAction(seq);
		return;
	}

}


void BFSceneMenu::_onTouchButton(CCObject* pSender, TouchEventType type) {

	//UIButton *button = static_cast<UIButton *>(pSender);
	if (type == TOUCH_EVENT_BEGAN) {

	}

	if (type == TOUCH_EVENT_ENDED) {
		
		CCScene *scene = BFSceneGame::scene();
		CCScene* pScene = CCTransitionFade::create(0.1f, scene);
		if (pScene) {
			CCDirector::sharedDirector()->pushScene(pScene);
		}
	}

	if (type == TOUCH_EVENT_CANCELED) {

	}
}




void BFSceneMenu::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void BFSceneMenu::keyBackClicked(void) {
	this->menuCloseCallback(this);
}