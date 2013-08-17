//
//  Hoja.cpp
//  Grow1
//
//  Created by Mikel on 28/05/13.
//
//

#include "Grow.h"

int hoja_array_capacity=100;

float hoja_angulo_hoja=0;

CCArray * hojas = NULL;

CCAnimation *left_hoja_anim= NULL;
CCAnimation *right_hoja_anim= NULL;


Hoja::Hoja() {
}

Hoja::~Hoja() {
    hoja_sprite->removeFromParent();
}


bool Hoja::init(CCNode *parent,CCPoint pos, bool fliped, Planta *planta) {
    
    if (!hojas) {
        hojas = CCArray::createWithCapacity(hoja_array_capacity);
        hojas->retain();
    }
    
    if (!left_hoja_anim)
        left_hoja_anim= CCAnimationCache::sharedAnimationCache()->animationByName("left_hoja");
    if (!right_hoja_anim)
        right_hoja_anim= CCAnimationCache::sharedAnimationCache()->animationByName("right_hoja");

    
    planta_parent=planta;
    
    hoja_sprite=CCSprite::createWithSpriteFrameName(fliped?"right_hoja1":"left_hoja1");
    hoja_sprite->retain();
    
    hoja_sprite->setAnchorPoint(fliped?ccp(1,.5):ccp(0,.5));
    hoja_sprite->setPosition(pos);
    hoja_sprite->setFlipX(fliped);
    hoja_sprite->runAction(CCAnimate::create(fliped?left_hoja_anim:right_hoja_anim));
    hoja_sprite->setRotation(fliped?-hoja_angulo_hoja:hoja_angulo_hoja);
    parent->addChild(hoja_sprite,11);

    
    damage=0;
    maxvida=1.0;
    vida=maxvida;
    falling=false;
    
    hojas->addObject(this);
    return true;
}


Hoja *Hoja::create(CCNode *parent, CCPoint pos, bool fliped, Planta *planta) {
    Hoja *s=new Hoja();
    if (s==NULL) return NULL;
    if ( s->init(parent,pos,fliped,planta) == false ) {
        delete s;
        s=NULL;
    } else {
        s->autorelease();
    }
    return s;
}

void Hoja::update(float dt) {
    if (vida>0) {
    
    } else {
        CCPoint pos=hoja_sprite->getPosition();
        float alfa=hoja_sprite->getRotation();
        pos.y-=70*dt;
        alfa+=(hoja_sprite->isFlipX()?-10:10)*dt;
        hoja_sprite->setPosition(pos);
        hoja_sprite->setRotation(alfa);
    }
}

void Hoja::checkAndDestroy() {
    if (vida<=0) {
        CCPoint pos=hoja_sprite->getPosition();
        if (pos.y<-30) {
            //delete this;
            hojas->removeObject(this);
        }
    }
}


bool Hoja::drain(float dlife) {
    if (!dontdieOption)  vida-=dlife;
    if (vida<0) {
        vida=0;
        if (!falling) {
            planta_parent->hoja_falling();
            falling=true;
            bicho_forget_hoja_target(this);
            theGameScene->grow_reduce_1hoja();
        }
        return false;
    } else if (damage<2 && vida < 0.3*maxvida) {
        damage+=1;
        hoja_sprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(hoja_sprite->isFlipX()?"left_hoja_comida2":"right_hoja_comida2"));
    } else if (damage<1 && vida < 0.6*maxvida) {
        damage+=1;
        hoja_sprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(hoja_sprite->isFlipX()?"left_hoja_comida1":"right_hoja_comida1"));
    }
    return true;
}


CCPoint Hoja::getBichoPosition(float alfa) {
    bool fliped=hoja_sprite->isFlipX();
    CCPoint a=hoja_sprite->convertToWorldSpaceAR(ccp(fliped?-40:40,20));
    CCPoint b=hoja_sprite->convertToWorldSpaceAR(ccp(fliped?-100:100,20));
    
    return ccp(a.x*alfa+b.x*(1-alfa),a.y*alfa+b.y*(1-alfa));
}


void hoja_update_all(float dt) {
    if (!hojas) return;
    Hoja *hojaaux;
    int i;
    int n=hojas->count();
    for (i=0;i<n;i++) {
        hojaaux=(Hoja *)(hojas->objectAtIndex(i));
        hojaaux->update(dt);
    }
    for (i=n-1;i>=0;i--) {
        ((Hoja *)(hojas->objectAtIndex(i)))->checkAndDestroy();
    }
}

void hoja_delete_all() {
    hojas->removeAllObjects();
}

Hoja *hoja_get_random_hoja() {
    if (!hojas) return NULL;
    int n=hojas->count();
    if (n==0) return NULL;
    int i=rand()%n;
    return (Hoja*)hojas->objectAtIndex(i);
}


