//
//  GameScene.cpp
//  Grow1
//
//  Created by Mikel on 14/05/13.
//
//

#include "Grow.h"


int nbichos=10;


GameScene *theGameScene=NULL;


GameScene::GameScene() {
}

GameScene::~GameScene() {
    printf("gamescene destructor called\n");
    bicho_delete_all();
    hoja_delete_all();
    
}


bool GameScene::init() {
    cocos2d::ccColor4B c1={255,0,0,255};
    cocos2d::ccColor4B c2={0,0,255,255};
    ccColor3B marcador_color={0,0,0};
    
    fondo=cocos2d::CCLayerGradient::create(c1,c2);
//    fondo_sprite=CCSprite::createWithSpriteFrameName("fondo1");
//    fondo_sprite->setAnchorPoint(ccp(0,0));
    plantaLayer=Planta::create(this);
    marcadores=CCLayer::create();
    left=CCLabelTTF::create("XXXXX", "MarkerFelt", 32);
    left->setAnchorPoint(ccp(-0.2,1.2));
    left->setPosition(ccp(0,320));
    left->setColor(marcador_color);
    right=CCLabelTTF::create("YYY", "MarkerFelt", 32);
    right->setAnchorPoint(ccp(1.2,1.2));
    right->setPosition(ccp(480,320));
    right->setColor(marcador_color);
    this->addChild(fondo);
  //  fondo->addChild(fondo_sprite);
    this->addChild(plantaLayer);
    this->addChild(marcadores);
    marcadores->addChild(right);
    marcadores->addChild(left);

    player_ps=CCParticleSmoke::create();
    plantaLayer->addChild(player_ps,30);

    
    this->resetGameState();
    this->scheduleUpdate();
    
    return true;
}

void GameScene::resetGameState() {
    
    new_bugs_rate=1;
    nbugs=0;
    max_nbugs=10;
    generate_bugs=true;
    bicho_arrival();
    
    bug_hunger=0.2;
    grow_reductions=0;
    set_dificultad(0);
    
    load=1.0;
    reloading_rate=0.2;
    unloading_rate=0.5;
    
    player_ps->stopSystem();
    fumigando=false;
    playended=false;
    
}

GameScene *GameScene::create(int n) {
    GameScene *s=new GameScene();
    if (s==NULL) return NULL;
    nbichos=n;
    if ( s->init() == false ) {
        delete s;
        s=NULL;
    } else {
        s->autorelease();
    }
    return s;
}


void GameScene::update(float dt) {
    bicho_update_all(dt,playended);
    hoja_update_all(dt);
    plantaLayer->update(dt);
    if (fumigando) {
        load-=unloading_rate*dt;
        if (fumigando && load<0) unclick();
        load=load<0.0?0.0:load;
    } else {
        load+=reloading_rate*dt;
        load=load>1.0?1.0:load;
    }
    
    char s[200];
    sprintf(s, "%.1f %d",plantaLayer->grow,plantaLayer->fase);
    right->setString(s);
    sprintf(s,"%.0f",100.0*load);
    left->setString(s);
}

void GameScene::click(float x, float y) {
    if (load>0) {
        audio_start_psst();
        player_ps->setPosition(ccp(x,320-y));
        player_ps->resetSystem();
        fumigando=true;
    }
}

void GameScene::move(float x, float y) {
    player_ps->setPosition(ccp(x,320-y));
}

void GameScene::unclick() {
    player_ps->stopSystem();
    fumigando=false;
    audio_stop_psst();
}



void GameScene::bicho_arrival() {
    float tinter=rand_exp_limited(new_bugs_rate, 1);
    this->runAction(CCSequence::create(CCDelayTime::create(tinter),CCCallFunc::create(this, callfunc_selector(GameScene::bicho_arrival)),NULL));
    if (!generate_bugs || nbugs>=max_nbugs) return;
    Bicho::create(plantaLayer,true);
    nbugs+=1;
}

void GameScene::set_dificultad(int i) {
    // i=0 inicial
    // i=1
    new_bugs_rate=1+.25*(i+1);
    max_nbugs=5+5*(i+1);
    bug_hunger=0.25*(i+1);
    grow_rate=(.05/4);
    //*(5-grow_reductions)/5;
    
    printf("nivel %d grow_rate %f \n",i,grow_rate);
//    grow_rate/=1;
}

void GameScene::grow_reduce_1hoja() {
    grow_reductions+=1;
    grow_rate=(.05/4);
    //*(6-grow_reductions)/6;
    printf("grow_rate %f \n",grow_rate);
    if (grow_reductions==6) {
        grow_rate=0;
        this->game_lost();
    }
}

void GameScene::game_lost() {
    grow_rate=0;
    // perder
    playended=true;
    CCLabelTTF *text;
    text= CCLabelTTF::create("You lost", "Marker Felt", 40);
    CCSize fsize=CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
    text->setPosition(ccp(fsize.width/2,fsize.height/2));
    text->setColor((ccColor3B){0,0,0});
    this->addChild(text);
    this->schedule_game_exit(5);    
}

void GameScene::flor_grown() {
    // ganar
    playended=true;
    CCLabelTTF *text;
    text= CCLabelTTF::create("You won !!+!", "Marker Felt", 40);
    CCSize fsize=CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
    text->setPosition(ccp(fsize.width/2,fsize.height/2));
    text->setColor((ccColor3B){255,255,0});
    this->addChild(text);
    text->runAction(CCRepeatForever::create(CCRotateBy::create(1, -90)));
    this->schedule_game_exit(5);
}


void GameScene::schedule_game_exit(float dt) {
    this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(dt), CCCallFunc::create(this,callfunc_selector(GameScene::game_exit))));
}


void GameScene::game_exit() {
    printf("finished\n");
    //CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(0.3,theMenuScene));
    CCDirector::sharedDirector()->replaceScene(theMenuScene);
    theMenuScene->mainEnterActions();
}

