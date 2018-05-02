#include "BFSceneGame.h"

#define DIFF_REPLACE 180
#define DIFF_CHANGE 30
#define DIFF_CHANGE_LIST 60
#define MAX_LINES 7

CCScene* BFSceneGame::scene()
{

    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
	scene->setTag(1);
    
    // 'layer' is an autorelease object
    BFSceneGame *layer = BFSceneGame::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->setTag(0);

    // return the scene
    return scene;
}


BFSceneGame::~BFSceneGame() {
	CCLog("~BFSceneGame()");
	this->setKeypadEnabled(false);
}


// on "init" you need to initialize your instance
bool BFSceneGame::init()
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
										menu_selector(BFSceneGame::menuCloseCallback));
	   
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
	CCNode * pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("scene/game/Game.json"); //cocos2dx 2.2
	this->addChild(pNode, 0, 0);
	// установка маштаба
	pNode->setScaleY(winSize.height / TOP_EDGE_DESCTOP);
	pNode->setScaleX(winSize.width / RIGHT_EDGE_DESCTOP);

	BFGameAction *gameAction = BFGameAction::create();
	this->addChild(gameAction, 10, TAG_GAME_ACTION);
	gameAction->setGameScale(ccp(pNode->getScaleX(), pNode->getScaleY()));

	CCSequence* seq = CCSequence::create(CCDelayTime::create(0.1f), CCCallFuncN::create(this, callfuncN_selector(BFSceneGame::_callbackStartAnimation)), nullptr);
	this->runAction(seq);

	return true;
}


void BFSceneGame::_callbackStartAnimation(CCNode * Node) {

	if (CCDirector::sharedDirector()->getRunningScene()->getTag() != 1) {
		CCSequence* seq = CCSequence::create(CCDelayTime::create(0.1f), CCCallFuncN::create(this, callfuncN_selector(BFSceneGame::_callbackStartAnimation)), NULL);
		this->runAction(seq);
		return;
	}

	this->_addPlayerFish();
	this->schedule(schedule_selector(BFSceneGame::_updateGame));
	this->schedule(schedule_selector(BFSceneGame::_addEnemyFish), 3.0f);
}


void BFSceneGame::_addPlayerFish() {

	CCArmature *playerFishArmature = CCArmature::create("PlayerFish");
	playerFishArmature->setPosition(CCPointZero);
	playerFishArmature->getAnimation()->playWithIndex(0);
	BFPlayerFish *playerFishObject = BFPlayerFish::create(playerFishArmature);
	playerFishArmature->setUserObject(playerFishObject);
	CCSprite *background = (CCSprite *)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0)->getChildByTag(0)->getChildByTag(10003);
	background->addChild(playerFishArmature, 1, TAG_PLAYER);

	playerFishArmature->setScale(0.5f);
}


void BFSceneGame::_addEnemyFish(float dt) {

	int grid = 7;
	int shift = ((grid - 1) / 2);

	int x = rand() % grid - shift;
	int y = rand() % grid - shift;

	if (x < shift && x > -shift) {
		y = rand() % 2 - 1;
		if (!y)
			y = -shift;
		else
			y = shift;
	}

	CCPoint pos;
	pos.x = RIGHT_EDGE_DESCTOP / 2 / shift * x;
	pos.y = TOP_EDGE_DESCTOP / 2 / shift * y;

	float duration = 9.0f;
	CCSprite *enemyFishSpite = CCSprite::createWithSpriteFrameName("image/badFish.png");
	enemyFishSpite->setPosition(pos);
	BFEnemyFish *enemyFishObject = BFEnemyFish::create(enemyFishSpite);
	enemyFishSpite->setUserObject(enemyFishObject);
	CCSprite *background = (CCSprite *)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0)->getChildByTag(0)->getChildByTag(10003);
	background->addChild(enemyFishSpite, 1, TAG_ENEMY);

	enemyFishSpite->setScale(0.5f);

	enemyFishSpite->runAction(CCMoveTo::create(duration, CCPointZero));
}



void BFSceneGame::_updateGame(float dt) {
	
	BFGameAction *gameAction = static_cast<BFGameAction *>(this->getChildByTag(TAG_GAME_ACTION));
	CCPoint posFinger = gameAction->getPositionFinger();

	CCSprite *background = (CCSprite *)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0)->getChildByTag(0)->getChildByTag(10003);
	CCArmature *playerFishArmature = static_cast<CCArmature *>(background->getChildByTag(TAG_PLAYER));
	BFPlayerFish *playerFishObject = static_cast<BFPlayerFish *>(playerFishArmature->getUserObject());
	playerFishObject->updatePlayer(posFinger);

	CCArray *children = background->getChildren();
	for (size_t i = 0; i < children->count(); i++) {

		CCSprite *spriteObject = dynamic_cast<CCSprite *>(children->objectAtIndex(i));
		if (spriteObject && spriteObject->getTag() == TAG_ENEMY) {
			BFEnemyFish *enemyFishObject = static_cast<BFEnemyFish *>(spriteObject->getUserObject());
			//enemyFishObject->updateEnemy(posFinger);
			if (enemyFishObject->isTouchEnemy(posFinger))
				playerFishObject->createFire(spriteObject->getPosition());
			
			if (this->_isPlayerCaught(playerFishArmature, spriteObject))
				this->_returnScene();
		}

		if (spriteObject && spriteObject->getTag() == TAG_BUBBLE) {
			BFMoveBubble *enemyFishObject = static_cast<BFMoveBubble *>(spriteObject->getUserObject());
			enemyFishObject->updateBubble();
		}
	}
}


bool BFSceneGame::_isPlayerCaught(CCArmature *player, CCSprite *enemy) {

	float scalePlayer = player->getScale();
	float scaleEnemy = enemy->getScale();

	CCPoint posPlayer = player->getPosition();
	CCPoint posEnemy = enemy->getPosition();

	CCSize sizePlayer = player->getContentSize();
	CCSize sizeEnemy = enemy->getContentSize();

	return (posPlayer.x - sizePlayer.width * 0.4f * scalePlayer) < (posEnemy.x + sizeEnemy.width * 0.4f * scaleEnemy)
		&& (posPlayer.x + sizePlayer.width * 0.4f * scalePlayer) > (posEnemy.x - sizeEnemy.width * 0.4f * scaleEnemy)
		&& (posPlayer.y - sizePlayer.height * 0.4f * scalePlayer) < (posEnemy.y + sizeEnemy.height * 0.4f * scaleEnemy)
		&& (posPlayer.y + sizePlayer.height * 0.4f * scalePlayer) > (posEnemy.y - sizeEnemy.height * 0.4f * scaleEnemy);
}


void BFSceneGame::_returnScene() {
	CCDirector::sharedDirector()->popScene();
}


void BFSceneGame::menuCloseCallback(CCObject* pSender)
{
	this->_returnScene();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif
}


void BFSceneGame::keyBackClicked(void) {
	this->menuCloseCallback(this);
}
