//
//  MenuScene.cpp
//  Grow1
//
//  Created by Mikel on 08/05/13.
//
//

#include "Grow.h"

bool debugOption=false;
bool dontdieOption=false;


CCMenuItemLabel *MakeMenuItem(const char *texto, float x, float y,ccColor3B color, CCObject *target, SEL_MenuHandler selector) {
    CCMenuItemLabel *l1;
    l1=CCMenuItemLabel::create(CCLabelTTF::create(texto, "MarkerFelt", 40),target,selector);
    l1->setColor(color);
    l1->setPosition(ccp(x,y));
    return l1;
}



MenuScene *theMenuScene=NULL;

MenuScene::MenuScene() {
}

MenuScene::~MenuScene() {
}


bool MenuScene::init() {
    ccColor4B c1={255,255,255,180};
    ccColor4B c2={255,255,255,220};
    
    menu=NULL;
    options=NULL;
    visible_menu=NULL;

    
    
    CCLayerGradient *fondol;
    
    fondol=CCLayerGradient::create(c1,c2);
    fondol->changeWidthAndHeight(400,250);
    fondol->setAnchorPoint(ccp(0.5,0.5));
    fondol->ignoreAnchorPointForPosition(false);
    fondol->setPosition(240,160);
    //fondol->setRotation(30);
    fondo=fondol;

    fondo_sprite= CCSprite::createWithSpriteFrameName("fondo1");
    fondo_sprite->setAnchorPoint(ccp(0,0));
    
    this->addChild(fondo_sprite,0);
    this->addChild(fondo,10);
    

    
    changeToMain();
    changeToMain();
    changeToMain();
    
    return true;
}


MenuScene *MenuScene::create() {
    MenuScene *s=new MenuScene();
    if (s==NULL) return NULL;
    if ( s->init() == false ) {
        delete s;
        s=NULL;
    } else {
        s->autorelease();
    }
    return s;
}


void MenuScene::action_enter1(CCObject *sender) {
    CCDirector* pDirector = CCDirector::sharedDirector();
    
    if (theGameScene) theGameScene->release();
    theGameScene = GameScene::create(10);
    theGameScene->retain();
    
    pDirector->replaceScene(CCTransitionMoveInL::create(0.3,theGameScene));
}

void MenuScene::action_enter2(CCObject *sender) {
    CCDirector* pDirector = CCDirector::sharedDirector();
    
    theGameScene = GameScene::create(100);
    theGameScene->retain();
    
    pDirector->replaceScene(CCTransitionMoveInL::create(0.3,theGameScene));
}

void MenuScene::action_toggleDebug(CCObject *sender) {
    debugOption=!debugOption;
    debugOptionMenuItem->setString(debugOption?"Debug: ON":"Debug: OFF");
    CCDirector::sharedDirector()->setDisplayStats(debugOption);

}

void MenuScene::action_toggleDontdie(CCObject *sender) {
    dontdieOption=!dontdieOption;
    dontdieOptionMenuItem->setString(dontdieOption?"Don't die: ON":"Don't die: OFF");    
}

void MenuScene::action_options(CCObject *sender) {
    changeToOptions();
}

void MenuScene::action_back(CCObject *sender) {
    changeToMain();
}


void MenuScene::changeToOptions() {
    if (visible_menu) visible_menu->removeFromParent();
    if (options==NULL) {
        ccColor3B negro={0,0,0};
        CCMenuItemLabel *l1,*l2;
        debugOptionMenuItem=
        MakeMenuItem("Debug: OFF", 0, 50, negro, this, menu_selector(MenuScene::action_toggleDebug));
        dontdieOptionMenuItem=MakeMenuItem("Don't die: OFF", 0, 0, negro, this, menu_selector(MenuScene::action_toggleDontdie));
        l2=MakeMenuItem("Back", 0, -50, negro, this, menu_selector(MenuScene::action_back));
        options=CCMenu::create(debugOptionMenuItem,dontdieOptionMenuItem,l2,NULL);
        options->retain();
    }
    visible_menu=options;
    this->addChild(visible_menu,20);
}

void MenuScene::changeToMain() {
    if (visible_menu) visible_menu->removeFromParent();
    
    if (menu==NULL) {
        ccColor3B negro={0,0,0};
        CCMenuItemLabel *l1, *l2;
        
        l1=MakeMenuItem("Play", 0, 40, negro, this, menu_selector(MenuScene::action_enter1));
        l2=MakeMenuItem("Options", 0, -40, negro, this, menu_selector(MenuScene::action_options));

        menu=CCMenu::create(l1,l2,NULL);
        menu->retain();
    }
    
    visible_menu=menu;
    this->addChild(visible_menu,20);
}
