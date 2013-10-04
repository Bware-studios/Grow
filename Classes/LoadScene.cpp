//
//  LoadScene.cpp
//  Grow1
//
//  Created by Mikel on 19/05/13.
//
//

#include "Grow.h"


LoadScene *theLoadScene=NULL;

LoadScene::LoadScene() {
}

LoadScene::~LoadScene() {
}


bool LoadScene::init() {
    //ccColor4B c1={0,50,0,255};
    //ccColor4B c2={0,150,0,255};
    //fondo=CCLayerGradient::create(c1,c2);
    //this->addChild(fondo);
    
    CCSprite *fondoimg= CCSprite::create("fondo_loading.png");
    fondoimg->setPosition(ccp(240,160));
    this->addChild(fondoimg,1);
    
    texto=CCLabelTTF::create("xxx", "Marker Felt", 18);
    texto->setPosition(ccp(240,20));

    ccColor3B textcolor={100,100,100};
    texto->setColor(textcolor);
    this->addChild(texto,10);
    
    return true;
}


LoadScene *LoadScene::create() {
    LoadScene *s=new LoadScene();
    if (s==NULL) return NULL;
    if ( s->init() == false ) {
        delete s;
        s=NULL;
    } else {
        s->autorelease();
    }
    return s;
}

void LoadScene::loadGameContent() {
    texto->setString("Loading: Preparing graphics");
    
    CCSpriteFrameCache *sf_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCSpriteFrame *sframe;
    
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(0, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala1");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(64, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala2");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(128, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala3");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(192, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala4");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(256, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala5");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(320, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala6");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(384, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala7");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(448, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala8");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(512, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala9");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(576, 0, 64,64));
    sf_cache->addSpriteFrame(sframe, "ala10");

    
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(0, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo1");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(64, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo2");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(128, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo3");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(192, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo4");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(256, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo5");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(320, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo6");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(384, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo7");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(448, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo8");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(512, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo9");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(576, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_comiendo10");

    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(640, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_muriendo1");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(704, 128, 64,64));
    sf_cache->addSpriteFrame(sframe, "bicho_muriendo2");

    
    
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(768, 64, 192,64));
    sf_cache->addSpriteFrame(sframe, "right_hoja1");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(576, 64, 192,64));
    sf_cache->addSpriteFrame(sframe, "right_hoja2");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(0, 64, 192,64));
    sf_cache->addSpriteFrame(sframe, "right_hoja3");

    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(192, 64, 192,64));
    sf_cache->addSpriteFrame(sframe, "right_hoja_comida1");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(384, 64, 192,64));
    sf_cache->addSpriteFrame(sframe, "right_hoja_comida2");

    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(768, 384, 192,64));
    sf_cache->addSpriteFrame(sframe, "left_hoja1");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(576, 384, 192,64));
    sf_cache->addSpriteFrame(sframe, "left_hoja2");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(0, 384, 192,64));
    sf_cache->addSpriteFrame(sframe, "left_hoja3");
    
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(192, 384, 192,64));
    sf_cache->addSpriteFrame(sframe, "left_hoja_comida1");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(384, 384, 192,64));
    sf_cache->addSpriteFrame(sframe, "left_hoja_comida2");
    

    
    
//    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(0, 192, 192,96));
//    sf_cache->addSpriteFrame(sframe, "flor1");
//    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(192, 192, 192,96));
//    sf_cache->addSpriteFrame(sframe, "flor2");
//    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(384, 192, 192,96));
//    sf_cache->addSpriteFrame(sframe, "flor3");
//    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(576, 192, 192,96));
//    sf_cache->addSpriteFrame(sframe, "flor4");

    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(0, 192, 256, 192));
    sf_cache->addSpriteFrame(sframe, "flor1");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(256, 192, 256, 192));
    sf_cache->addSpriteFrame(sframe, "flor2");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(512, 192, 256, 192));
    sf_cache->addSpriteFrame(sframe, "flor3");
    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(768, 192, 256, 192));
    sf_cache->addSpriteFrame(sframe, "flor4");


    // textura de pruebas
//    sframe=CCSpriteFrame::create("Grow1_textura_p.png", CCRectMake(0, 128, 64,128));
//    sf_cache->addSpriteFrame(sframe, "tallo1");
//    sframe=CCSpriteFrame::create("Grow1_textura_p.png", CCRectMake(64, 128, 64,128));
//    sf_cache->addSpriteFrame(sframe, "tallo2");
//    sframe=CCSpriteFrame::create("Grow1_textura_p.png", CCRectMake(128, 128, 64,128));
//    sf_cache->addSpriteFrame(sframe, "tallo3");

    sframe=CCSpriteFrame::create("Grow1_textura1.png", CCRectMake(960, 0, 64,128));
    sf_cache->addSpriteFrame(sframe, "tallo1");
    sf_cache->addSpriteFrame(sframe, "tallo2");
    sf_cache->addSpriteFrame(sframe, "tallo3");
    
    
    sframe=CCSpriteFrame::create("Grow1_fondo.png", CCRectMake(0, 0, 480,320));
    sf_cache->addSpriteFrame(sframe, "fondo1");

    
    CCAnimationCache *an_cache = CCAnimationCache::sharedAnimationCache();
    CCAnimation *anim;
    CCArray *frames;
    //= CCArray::createWithCapacity(10);
//    CCAnimationFrame *aframe;
    frames=CCArray::create(sf_cache->spriteFrameByName("ala1"),sf_cache->spriteFrameByName("ala2"),sf_cache->spriteFrameByName("ala3"),sf_cache->spriteFrameByName("ala4"),sf_cache->spriteFrameByName("ala5"),sf_cache->spriteFrameByName("ala6"),sf_cache->spriteFrameByName("ala7"),sf_cache->spriteFrameByName("ala8"),sf_cache->spriteFrameByName("ala9"),sf_cache->spriteFrameByName("ala10"),NULL);
    anim=CCAnimation::createWithSpriteFrames(frames,0.02);
    an_cache->addAnimation(anim, "alas");

    frames=CCArray::create(sf_cache->spriteFrameByName("bicho_muriendo1"),sf_cache->spriteFrameByName("bicho_muriendo2"),NULL);
    anim=CCAnimation::createWithSpriteFrames(frames,0.2);
    an_cache->addAnimation(anim, "bicho_muriendo");

    frames=CCArray::create(sf_cache->spriteFrameByName("bicho_comiendo1"),sf_cache->spriteFrameByName("bicho_comiendo2"),sf_cache->spriteFrameByName("bicho_comiendo3"),sf_cache->spriteFrameByName("bicho_comiendo4"),sf_cache->spriteFrameByName("bicho_comiendo5"),sf_cache->spriteFrameByName("bicho_comiendo6"),sf_cache->spriteFrameByName("bicho_comiendo7"),sf_cache->spriteFrameByName("bicho_comiendo8"),sf_cache->spriteFrameByName("bicho_comiendo9"),sf_cache->spriteFrameByName("bicho_comiendo10"),NULL);
    anim=CCAnimation::createWithSpriteFrames(frames,0.03);
    an_cache->addAnimation(anim, "bicho_comiendo");

    frames=CCArray::create(sf_cache->spriteFrameByName("left_hoja1"),sf_cache->spriteFrameByName("left_hoja2"),sf_cache->spriteFrameByName("left_hoja3"),NULL);
    anim=CCAnimation::createWithSpriteFrames(frames,0.4);
    an_cache->addAnimation(anim, "left_hoja");

    frames=CCArray::create(sf_cache->spriteFrameByName("right_hoja1"),sf_cache->spriteFrameByName("right_hoja2"),sf_cache->spriteFrameByName("right_hoja3"),NULL);
    anim=CCAnimation::createWithSpriteFrames(frames,0.4);
    an_cache->addAnimation(anim, "right_hoja");
    
    frames=CCArray::create(sf_cache->spriteFrameByName("flor1"),sf_cache->spriteFrameByName("flor2"),sf_cache->spriteFrameByName("flor3"),sf_cache->spriteFrameByName("flor4"),NULL);
    anim=CCAnimation::createWithSpriteFrames(frames,0.5);
    an_cache->addAnimation(anim, "flor");
    
    
    texto->setString("Loading: Preparing menu");
    theMenuScene = MenuScene::create();
    theMenuScene->retain();
  //  texto->setString("Preparing scene");
  //  theGameScene = GameScene::create();
  //  theGameScene->retain();

    texto->setString("Loading: Preparing audio");
    audio_preload_all();
    
    //texto->setString("Done");

    texto->setString("Loading: DONE");
    
    this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(2.0), CCCallFunc::create(this,callfunc_selector(LoadScene::exitLoadScene))));

}

void LoadScene::exitLoadScene() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->pushScene(theMenuScene);
}


void setLoadSceneAndStart(CCDirector *director) {
    theLoadScene = LoadScene::create();
    theLoadScene->retain();
    director->runWithScene(theLoadScene);
    theLoadScene->loadGameContent();
}



