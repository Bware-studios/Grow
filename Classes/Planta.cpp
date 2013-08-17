//
//  Planta.cpp
//  Grow1
//
//  Created by Mikel on 25/05/13.
//
//

#include "Grow.h"
#include <math.h>

// pixels per second
//float planta_grow_rate=0.05;

float planta_desviacion_amplitud=60;

const int npartes=4;

CCAnimation *planta_hoja_anim= NULL;
CCAnimation *planta_flor_anim= NULL;



Planta::Planta() {
}

Planta::~Planta() {
    printf("planta destructor called\n");
}


bool Planta::init(GameScene *parent) {
    grow=0;
    fase=0;
    
    
    if (!planta_flor_anim)
        planta_flor_anim= CCAnimationCache::sharedAnimationCache()->animationByName("flor");

    
    this->parent=parent;

    x[0]=240;
    x[1]=240+((rand()*1.0/RAND_MAX)-0.5)*planta_desviacion_amplitud;
    x[2]=240+((rand()*1.0/RAND_MAX)-0.5)*planta_desviacion_amplitud;
    x[3]=240+((rand()*1.0/RAND_MAX)-0.5)*planta_desviacion_amplitud;
    x[4]=240+((rand()*1.0/RAND_MAX)-0.5)*planta_desviacion_amplitud;
    y[0]=0;
    y[1]=60;
    y[2]=120;
    y[3]=170;
    y[4]=200;
    
    
//    altura[0]=70;
//    altura[1]=130;
//    altura[2]=180;
//    altura[3]=240;

    int i;
    for (i=0;i<npartes;i++) {
        alfa[i]=atanf((x[i+1]-x[i])/(y[i+1]-y[i]))*180/M_PI;
        printf("a[%d]=%f\n",i,alfa[i]);
    }
    
    tallo_sprite[0]=CCSprite::createWithSpriteFrameName("tallo1");
    tallo_sprite[0]->setPosition(ccp(x[0],y[0]));
    tallo_sprite[0]->setRotation(alfa[0]);
    tallo_sprite[0]->setAnchorPoint(ccp(0.5,0.75));
    tallo_sprite[1]=NULL;
    tallo_sprite[2]=NULL;
    tallo_sprite[3]=NULL;

    this->addChild(tallo_sprite[0],10);
    
    
    CCSpriteFrame *sframe;
    CCSpriteFrameCache *sf_cache=CCSpriteFrameCache::sharedSpriteFrameCache();
    sframe=CCSpriteFrame::create("Grow1_fondo.png", CCRectMake(0, 320-y[1], 480,y[1]));
    sf_cache->addSpriteFrame(sframe, "fondo1a");
    sframe=CCSpriteFrame::create("Grow1_fondo.png", CCRectMake(0, 320-y[2], 480,y[2]-y[1]));
    sf_cache->addSpriteFrame(sframe, "fondo1b");
    sframe=CCSpriteFrame::create("Grow1_fondo.png", CCRectMake(0, 320-y[3], 480,y[3]-y[2]));
    sf_cache->addSpriteFrame(sframe, "fondo1c");
    sframe=CCSpriteFrame::create("Grow1_fondo.png", CCRectMake(0, 0, 480,320-y[3]));
    sf_cache->addSpriteFrame(sframe, "fondo1d");

    CCSprite *fondo;
    fondo=CCSprite::createWithSpriteFrameName("fondo1a");
    fondo->setAnchorPoint(ccp(0,0));
    fondo->setPosition(ccp(0,0));
    this->addChild(fondo,9);
    fondo=CCSprite::createWithSpriteFrameName("fondo1b");
    fondo->setAnchorPoint(ccp(0,0));
    fondo->setPosition(ccp(0,y[1]));
    this->addChild(fondo,7);
    fondo=CCSprite::createWithSpriteFrameName("fondo1c");
    fondo->setAnchorPoint(ccp(0,0));
    fondo->setPosition(ccp(0,y[2]));
    this->addChild(fondo,5);
    fondo=CCSprite::createWithSpriteFrameName("fondo1d");
    fondo->setAnchorPoint(ccp(0,0));
    fondo->setPosition(ccp(0,y[3]));
    this->addChild(fondo,1);
    
    
//    float desviacion;
//    float delta;
//    
//    desviacion=((rand()*1.0/RAND_MAX)-0.5)*planta_desviacion_amplitud;    
//    vs[0]=ccp(230,0);
//    vs[1]=ccp(250,0);
//    vs[2]=ccp(250+desviacion,altura[0]);
//    vs[3]=ccp(230+desviacion,altura[0]);
//
//    alfa[0]=atanf(desviacion/altura[0])*180/M_PI;
//    printf("%f / %f -> %f\n",desviacion,altura[0],alfa[0]);
//    
//    delta=-desviacion;
//
//    vs[5]=ccp(250+desviacion,altura[0]);
//    vs[4]=ccp(230+desviacion,altura[0]);
//    desviacion=((rand()*1.0/RAND_MAX)-0.5)*planta_desviacion_amplitud;
//    vs[6]=ccp(250+desviacion,altura[1]);
//    vs[7]=ccp(230+desviacion,altura[1]);
//
//    delta+=desviacion;
//    alfa[1]=atanf(delta/(altura[1]-altura[0]))*180/M_PI;
//    delta=-desviacion;
//    printf("%f / %f -> %f\n",desviacion,altura[1],alfa[1]);
//    
//    vs[9]=ccp(250+desviacion,altura[1]);
//    vs[8]=ccp(230+desviacion,altura[1]);
//    desviacion=((rand()*1.0/RAND_MAX)-0.5)*planta_desviacion_amplitud;
//    vs[10]=ccp(250+desviacion,altura[2]);
//    vs[11]=ccp(230+desviacion,altura[2]);
//
//    delta+=desviacion;
//    alfa[2]=atanf(delta/(altura[2]-altura[1]))*180/M_PI;
//    delta=-desviacion;
//    printf("%f / %f -> %f\n",desviacion,altura[2],alfa[2]);
//    
//    vs[13]=ccp(250+desviacion,altura[2]);
//    vs[12]=ccp(230+desviacion,altura[2]);
//    desviacion=((rand()*1.0/RAND_MAX)-0.5)*planta_desviacion_amplitud;
//    vs[14]=ccp(250+desviacion,altura[3]);
//    vs[15]=ccp(230+desviacion,altura[3]);
//
//    delta+=desviacion;
//    alfa[3]=atanf(delta/(altura[3]-altura[2]))*180/M_PI;
//    delta=-desviacion;
//    printf("%f / %f -> %f\n",desviacion,altura[2],alfa[2]);
//    
//    for (i=0;i<16;i++) {
//        draw_vs[i]=vs[i];
//    }
    
//    flor_sprite = CCSprite::createWithSpriteFrameName("flor1");
//    flor_sprite->retain();
//    flor_sprite->setAnchorPoint(ccp(0.5,.2));
//    this->addChild(flor_sprite, 1);
//    flor_sprite->setPosition(ccp());
    
    
    first_hoja_grown=false;
    alive_hojas=0;
    
    touching=false;
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    //printf("touch enabled %d   %d %d\n",this->isTouchEnabled(),this->getTouchMode(),kCCTouchesOneByOne);
    return true;
}


Planta *Planta::create(GameScene *parent) {
    Planta *s=new Planta();
    if (s==NULL) return NULL;
    if ( s->init(parent) == false ) {
        delete s;
        s=NULL;
    } else {
        s->autorelease();
    }
    return s;
}

void Planta::update(float dt) {
    if (fase<4) grow+=dt*theGameScene->grow_rate;
    int faseant=fase;
    fase=(int)(grow*npartes);
    if (fase>faseant) {
        theGameScene->set_dificultad(fase);
        if (fase<4) {
            tallo_sprite[fase]=CCSprite::createWithSpriteFrameName(fase==1?"tallo2":(fase==2?"tallo3":"tallo3"));
            tallo_sprite[fase]->setRotation(alfa[fase]);
            tallo_sprite[fase]->setAnchorPoint(ccp(0.5,0.75));
            this->addChild(tallo_sprite[fase],10-2*fase);
            Hoja::create(this, ccp(x[fase]-5,y[fase]),true,this);
            Hoja::create(this, ccp(x[fase]+5,y[fase]),false,this);
            first_hoja_grown=true;
            alive_hojas+=2;
        } else {
            theGameScene->flor_grown();
            flor_sprite = CCSprite::createWithSpriteFrameName("flor1");
            flor_sprite->setAnchorPoint(ccp(0.5,0));
            flor_sprite->setPosition(ccp(x[fase],y[fase]));
            this->addChild(flor_sprite, 11);
            flor_sprite->runAction(CCAnimate::create(planta_flor_anim));
            flor_sprite->setRotation(alfa[3]);
        }
    }
    if (fase<4) {
        float a=(grow*npartes-fase);
        //CCPoint pos=tallo_sprite[fase-1]->getPosition();
        tallo_sprite[fase]->setPosition(ccp(x[fase+1]*a+x[fase]*(1-a),y[fase+1]*a+y[fase]*(1-a)));
    }
    
    //printf("a= %f  g= %f %d\n",a,grow,fase);
    
//    float h=grow>10?grow:10;
//    if (h>altura[fase] && fase<4) {
////        hoja_sprite[fase]=CCSprite::createWithSpriteFrameName("hoja1");
////        hoja_sprite[fase]->setAnchorPoint(ccp(1,.5));
////        hoja_sprite[fase]->setPosition(ccp(0.5*(vs[(fase)*4+3].x+vs[fase*4+2].x),vs[fase*4+2].y));
////        hoja_sprite[fase]->runAction(CCAnimate::create(planta_hoja_anim));
////        hoja_sprite[fase]->setRotation(-30);
////        this->addChild(hoja_sprite[fase],1);
//        if (fase<3) {
//            Hoja::create(this, ccp(vs[(fase)*4+3].x,vs[fase*4+2].y),true);
//            Hoja::create(this, ccp(vs[(fase)*4+2].x,vs[fase*4+2].y),false);
//        } else {
//            flor_sprite->runAction(CCAnimate::create(planta_flor_anim));
//        }
//        fase+=1;
//    }
//    if (fase<4) {
//        float ant_altura=0;
//        if (fase>0) ant_altura=altura[fase-1];
//        float alfa=(h-ant_altura)/(altura[fase]-ant_altura);
//    
//        draw_vs[2+fase*4].x=alfa*vs[2+fase*4].x+(1-alfa)*vs[1+fase*4].x;
//        draw_vs[2+fase*4].y=alfa*vs[2+fase*4].y+(1-alfa)*vs[1+fase*4].y;
//
//        draw_vs[3+fase*4].x=alfa*vs[3+fase*4].x+(1-alfa)*vs[0+fase*4].x;
//        draw_vs[3+fase*4].y=alfa*vs[3+fase*4].y+(1-alfa)*vs[0+fase*4].y;
//
//        flor_sprite->setPosition(ccp(0.5*(draw_vs[2+fase*4].x+draw_vs[3+fase*4].x),draw_vs[3+fase*4].y));
//        flor_sprite->setRotation(this->alfa[fase]);
//        //printf("%f\n",this->alfa[fase]);
//    }
}

void Planta::draw(void) {
//    ccDrawPoly(vs, 4+fase*2, true);
    int i;
    int fasestodraw=((fase>3)?3:fase);
    for (i=0;i<=fasestodraw;i++) {
        ccDrawSolidPoly(&(draw_vs[4*i]), 4, ccc4f(0, 0.7+0.1*i, 0, 1));
    }
}



void Planta::hoja_falling() {
    alive_hojas-=1;
    if (first_hoja_grown && alive_hojas==0) {
        theGameScene->game_lost();
    }
}




bool Planta::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    if ( ! touching ) {
        touching=true;
        CCPoint pos=touch->getLocationInView();
        parent->click(pos.x,pos.y);
    }
    return true;
}

void Planta::ccTouchMoved(CCTouch *touch, CCEvent *event) {
    //printf("moved\n");
    CCPoint pos=touch->getLocationInView();
    parent->move(pos.x,pos.y);
    
}

void Planta::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    parent->unclick();
    touching=false;
}

void Planta::ccTouchCancelled(CCTouch *touch, CCEvent *event) {
    parent->unclick();
    touching=false;
}




