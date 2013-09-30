//
//  GameScene.cpp
//  Grow1
//
//  Created by Mikel on 14/05/13.
//
//

#include "Grow.h"


const float score_per_growunit = 1000;
const float score_per_kill = 20;

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
    left=CCLabelTTF::create("XXXXX", "Marker Felt", 32);
    left->setAnchorPoint(ccp(-0.2,1.2));
    left->setPosition(ccp(0,320));
    left->setColor(marcador_color);
    right=CCLabelTTF::create("YYY", "Marker Felt", 32);
    right->setAnchorPoint(ccp(1.2,1.2));
    right->setPosition(ccp(460,320));
    right->setColor(marcador_color);
    this->addChild(fondo);
  //  fondo->addChild(fondo_sprite);
    this->addChild(plantaLayer);
    this->addChild(marcadores);
    marcadores->addChild(right);
    marcadores->addChild(left);

    player_ps=CCParticleSmoke::create();
    plantaLayer->addChild(player_ps,30);

    
    
    ingame_controls_layer=CCLayer::create();
    ingame_pause_layer=NULL;
    ingame_results=NULL;
    
    this->addChild(ingame_controls_layer, 100);
    CCMenuItemImage *pause_button=CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(GameScene::action_pause_button));
    pause_button->setPosition(ccp(230,150));
    CCMenu *menu=CCMenu::create(pause_button,NULL);
    ingame_controls_layer->addChild(menu);
    
    this->resetGameState();
    this->scheduleUpdate();
    
    return true;
}

void GameScene::resetGameState() {
    fumigando=false;
    playended=false;
    gamepaused=false;
    call_bicho_arrival_after_pause=false;
    gamewon=false;
    
    new_bugs_rate=1;
    nbugs=0;
    max_nbugs=10;
    generate_bugs=true;
    
    bug_hunger=0.2;
    grow_reductions=0;
    
    load=1.0;
    reloading_rate=0.2;
    unloading_rate=0.5;
    
    player_ps->stopSystem();
    
    score_total=0;
    score_kill=0;
    score_grow=0;
    score_num_kills=0;
    set_dificultad(0);
    bicho_arrival();
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
    if (gamepaused) return;
    
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
    //sprintf(s, "%.1f %d",plantaLayer->grow,plantaLayer->fase);
    //right->setString(s);
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
    if (gamepaused) {
        call_bicho_arrival_after_pause=true;
        return;
    }
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
    gamewon=true;
    CCLabelTTF *text;
    text= CCLabelTTF::create("You won !!+!", "Marker Felt", 40);
    CCSize fsize=CCEGLView::sharedOpenGLView()->getDesignResolutionSize();
    text->setPosition(ccp(fsize.width/2,fsize.height/2));
    text->setColor((ccColor3B){255,255,0});
    this->addChild(text);
    text->runAction(CCRepeatForever::create(CCRotateBy::create(1, -90)));
    this->schedule_game_exit(5);
}


void GameScene::score_update_1kill() {
    score_num_kills+=1;
    score_kill=score_num_kills*score_per_kill;
    score_update();
}

void GameScene::score_update_grow() {
    float thegrow=plantaLayer->grow;
    
    if (playended) return;
    if (thegrow>1.0) thegrow=1.0;
    
    score_grow=(plantaLayer->grow)*score_per_growunit;
    score_update();
}

void GameScene::score_update() {
    char s[200];

    score_total=score_kill+score_grow;
    sprintf(s, "%u",(int)score_total);
    right->setString(s);

}

void GameScene::schedule_game_exit(float dt) {
    this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(dt), CCCallFunc::create(this,callfunc_selector(GameScene::end_game_results))));
}


void GameScene::game_exit() {
    printf("finished\n");
    //CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(0.3,theMenuScene));
    CCDirector::sharedDirector()->replaceScene(theMenuScene);
    theMenuScene->mainEnterActions();
}


void GameScene::action_pause_button() {
    if (gamepaused) return;
    gamepaused=true;
    
    CCMenuItemLabel *l1,*l2;
    l1=CCMenuItemLabel::create(CCLabelTTF::create("Continue", "Marker Felt", 40),this,menu_selector(GameScene::action_unpause_button));
    l1->setColor((ccColor3B){0,100,0});
    l1->setPosition(ccp(0,40));
    l2=CCMenuItemLabel::create(CCLabelTTF::create("Quit", "Marker Felt", 40),this,menu_selector(GameScene::game_exit));
    l2->setColor((ccColor3B){100,0,0});
    l2->setPosition(ccp(0,-40));

    
    ingame_pause_layer=CCLayerGradient::create((ccColor4B){255,255,255,180},(ccColor4B){255,255,255,180});
    ingame_pause_layer->changeWidthAndHeight(400,250);
    ingame_pause_layer->setAnchorPoint(ccp(0.5,0.5));
    ingame_pause_layer->ignoreAnchorPointForPosition(false);
    ingame_pause_layer->setPosition(ccp(240,160));
    this->addChild(ingame_pause_layer, 100);
    CCMenu *menu=CCMenu::create(l1,l2,NULL);
    menu->setPosition(ccp(200,125));
    ingame_pause_layer->addChild(menu);

    
}


void GameScene::action_unpause_button() {
    this->removeChild(ingame_pause_layer);
    ingame_pause_layer=NULL;
    gamepaused=false;
    if (call_bicho_arrival_after_pause) {
        call_bicho_arrival_after_pause=false;
        bicho_arrival();
    }
}


void GameScene::end_game_results() {
    gamepaused=true;
    playended=true;
    
    CCMenuItemLabel *l1;
    l1=CCMenuItemLabel::create(CCLabelTTF::create("back to menu", "Marker Felt", 40),this,menu_selector(GameScene::game_exit));
    l1->setColor((ccColor3B){0,100,0});
    l1->setPosition(ccp(0,-80));
    
    CCLabelTTF *t1;
    
    
    ingame_results=CCLayerGradient::create((ccColor4B){255,255,255,180},(ccColor4B){255,255,255,180});
    ingame_results->changeWidthAndHeight(400,250);
    ingame_results->setAnchorPoint(ccp(0.5,0.5));
    ingame_results->ignoreAnchorPointForPosition(false);
    ingame_results->setPosition(ccp(240,160));
    this->addChild(ingame_results, 100);
    CCMenu *menu=CCMenu::create(l1,NULL);
    menu->setPosition(ccp(200,125));
    ingame_results->addChild(menu);
    
    
    t1=CCLabelTTF::create((gamewon?"Congratulations":"Sorry :-("),"Marker Felt", 40);
    t1->setPosition(ccp(200,220));
    t1->setColor((ccColor3B){0,0,0});
    ingame_results->addChild(t1);
    
    if ( !dontdieOption ) {
        char s[500];
        sprintf(s,"Growth: %d\nKills: %d x %d\nTotal score: %d",(int)score_grow,score_num_kills,(int)score_per_kill,(int)score_total);
        t1=CCLabelTTF::create(s,"Marker Felt", 26);
        t1->setPosition(ccp(200,130));
        t1->setColor((ccColor3B){0,0,0});
        ingame_results->addChild(t1);
    }
    
}



