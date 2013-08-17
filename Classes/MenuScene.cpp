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


// origen 0,0 en la esquina inferior izuquierda son hijos de scene
const CCPoint titulo_position = ccp(240,270);
const CCPoint titulo_position_out = ccp(240,400);

const CCPoint options_position = ccp(240,160);
const CCPoint options_position_out = ccp(240,-200);


// origen 0,0 en el centro son hijos del menu
const CCPoint boton_play_position = ccp(-150,-20);
const CCPoint boton_play_position_out = ccp(-400,-20);
const CCPoint boton_info_position = ccp(150,-50);
const CCPoint boton_info_position_out = ccp(400,-50);

const int z_fondo=0;
const int z_options_menu=10;
const int z_buttons=20;


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
    fondol->setRotation(30);
    fondo=fondol;

    fondo_sprite= CCSprite::createWithSpriteFrameName("fondo1");
    fondo_sprite->setAnchorPoint(ccp(0,0));
    
    this->addChild(fondo_sprite,z_fondo);
    //this->addChild(fondo,10);
    

    titulo_sprite=CCSprite::create("titulo.png");
    this->addChild(titulo_sprite,z_buttons);
    
    
    
    changeToMain();
    //changeToMain();
    //changeToMain();
    
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
    this->mainCleanActions();
    
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
    //if (visible_menu) visible_menu->removeFromParent();
    bool menu_created=false;
    if (options==NULL) {
        menu_created=true;
        ccColor3B negro={0,0,0};
        
        
        fondo_optionsMenu=CCLayerGradient::create((ccColor4B){255,255,255,180},(ccColor4B){255,255,255,180});
        fondo_optionsMenu->changeWidthAndHeight(400,250);
        fondo_optionsMenu->setAnchorPoint(ccp(0.5,0.5));
        fondo_optionsMenu->ignoreAnchorPointForPosition(false);
        //fondo_optionsMenu->setPosition(240,160);
        //fondo_optionsMenu->setRotation(30);
        this->addChild(fondo_optionsMenu,z_options_menu);

        
        
        CCMenuItemLabel *l2;
        debugOptionMenuItem=
        MakeMenuItem("Debug: OFF", 0, 50, negro, this, menu_selector(MenuScene::action_toggleDebug));
        dontdieOptionMenuItem=MakeMenuItem("Don't die: OFF", 0, 0, negro, this, menu_selector(MenuScene::action_toggleDontdie));
        l2=MakeMenuItem("Back", 0, -50, negro, this, menu_selector(MenuScene::action_back));
        options=CCMenu::create(debugOptionMenuItem,dontdieOptionMenuItem,l2,NULL);
        options->setPosition(ccp(200,125));
        options->retain();
        fondo_optionsMenu->addChild(options);
    }
    visible_menu=options;
    //if (menu_created) this->addChild(visible_menu,20);


    this->mainCleanActions();
    this->optionsEnterActions();


}

void MenuScene::changeToMain() {
    //if (visible_menu) visible_menu->removeFromParent();
    bool menu_created=false;
    if (menu==NULL) {
        menu_created=true;
        //ccColor3B negro={0,0,0};
        //CCMenuItemLabel *l1, *l2;
        
        boton_play=CCMenuItemImage::create("boton_play.png", "boton_play_selected.png", this, menu_selector(MenuScene::action_enter1));

        boton_info=CCMenuItemImage::create("boton_info.png", "boton_info_selected.png", this, menu_selector(MenuScene::action_options));

        //l1=MakeMenuItem("Play", 0, 40, negro, this, menu_selector(MenuScene::action_enter1));
        //l2=MakeMenuItem("Options", 0, -40, negro, this, menu_selector(MenuScene::action_options));

        menu=CCMenu::create(boton_play,boton_info,NULL);
        menu->retain();
    }

    this->mainEnterActions();
    if (options) this->optionsCleanActions();
    
    visible_menu=menu;
    if (menu_created) this->addChild(visible_menu,20);
}


void MenuScene::mainEnterActions() {
    titulo_sprite->setPosition(titulo_position_out);
    titulo_sprite->stopAllActions();
    titulo_sprite->runAction(CCMoveTo::create(0.25, titulo_position));
    
    boton_play->setPosition(boton_play_position_out);
    boton_play->stopAllActions();
    boton_play->runAction(CCMoveTo::create(0.25, boton_play_position));
    boton_info->setPosition(boton_info_position_out);
    boton_info->stopAllActions();
    boton_info->runAction(CCMoveTo::create(0.25, boton_info_position));
    
}

void MenuScene::mainCleanActions() {
    titulo_sprite->setPosition(titulo_position);
    titulo_sprite->stopAllActions();
    titulo_sprite->runAction(CCMoveTo::create(0.25, titulo_position_out));
    
    boton_play->setPosition(boton_play_position);
    boton_play->stopAllActions();
    boton_play->runAction(CCMoveTo::create(0.25, boton_play_position_out));
    boton_info->setPosition(boton_info_position);
    boton_info->stopAllActions();
    boton_info->runAction(CCMoveTo::create(0.25, boton_info_position_out));

}

void MenuScene::optionsEnterActions() {
    fondo_optionsMenu->setPosition(options_position_out);
    fondo_optionsMenu->stopAllActions();
    fondo_optionsMenu->runAction(CCMoveTo::create(0.25, options_position));
}

void MenuScene::optionsCleanActions() {
    fondo_optionsMenu->setPosition(options_position);
    fondo_optionsMenu->stopAllActions();
    fondo_optionsMenu->runAction(CCMoveTo::create(0.25, options_position_out));
}


