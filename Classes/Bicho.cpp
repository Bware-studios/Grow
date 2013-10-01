//
//  Bicho.cpp
//  Grow1
//
//  Created by Mikel on 21/05/13.
//
//

#include "Grow.h"

int bicho_array_capacity=100;

CCArray * bichos = NULL;


CCAnimation *bicho_alas_anim= NULL;
CCAnimation *bicho_muriendo_anim= NULL;
CCAnimation *bicho_comiendo_anim= NULL;



Bicho::Bicho() {
}

Bicho::~Bicho() {
    alas->removeFromParent();
//    cuerpo->removeFromParent();
}


bool Bicho::init(CCNode *parent, bool outofscreen) {
    
    if (!bichos) {
        bichos = CCArray::createWithCapacity(bicho_array_capacity);
        bichos->retain();
    }
    
    if (!bicho_alas_anim)
        bicho_alas_anim= CCAnimationCache::sharedAnimationCache()->animationByName("alas");
    if (!bicho_muriendo_anim)
        bicho_muriendo_anim= CCAnimationCache::sharedAnimationCache()->animationByName("bicho_muriendo");
    if (!bicho_comiendo_anim)
        bicho_comiendo_anim= CCAnimationCache::sharedAnimationCache()->animationByName("bicho_comiendo");

    
    
    alas=CCSprite::createWithSpriteFrameName("ala1");
    alas->retain();
//    cuerpo=CCSprite::createWithSpriteFrameName("bicho1");
//    cuerpo->retain();

    float gen_x,gen_y;
    gen_y=rand_range(0,320);
    if (outofscreen) {
        gen_x=rand_range(480,520);
        gen_x=gen_x>500?gen_x-520:gen_x;
    } else {
        gen_x=rand_range(0, 320);
    }
    //printf("generado en ( %f , %f ) \n",gen_x,gen_y);
    alas->setPosition(ccp(gen_x,gen_y));
//    cuerpo->setPosition(ccp(100,100));
    
    
    parent->addChild(alas,21);
//    parent->addChild(cuerpo,3);
    
    alas_action=alas->runAction(CCRepeatForever::create(CCAnimate::create(bicho_alas_anim)));
//    cuerpo_action=cuerpo->runAction(CCRepeatForever::create(CCAnimate::create(bicho_cuerpo_anim)));
    
    vx=rand_range(-50, 50);
    //100*(rand()*1.0/RAND_MAX-0.5);
    vy=rand_range(-30,30);
    //60*(rand()*1.0/RAND_MAX-0.5);

    if (vx>0) {
        alas->setFlipX(true);
 //       cuerpo->setFlipX(true);
    }
        
    muerto=false;
    finalmoving=false;
    decideTarget();
    
    bichos->addObject(this);
    return true;
}


Bicho *Bicho::create(CCNode *parent, bool outofscreen) {
    Bicho *s=new Bicho();
    if (s==NULL) return NULL;
    if ( s->init(parent,outofscreen) == false ) {
        delete s;
        s=NULL;
    } else {
        s->autorelease();
    }
    return s;
}

void Bicho::checkdamagefrom(float x, float y) {
    CCPoint pos=alas->getPosition();
    float d2 = (pos.x-x)*(pos.x-x)+(pos.y-y)*(pos.y-y);
    if (d2<32*32) {
//        alas->stopAllActions();
//        cuerpo->stopAllActions();
        alas->stopAction(alas_action);
        alas_action=alas->runAction(CCAnimate::create(bicho_muriendo_anim));
        alas->setRotation(0);
        muerto=true;
        theGameScene->score_update_1kill();
    }
}

void Bicho::checkAndDestroy() {
    if (muerto) {
        CCPoint pos=alas->getPosition();
        if (pos.y<-30) {
            //delete this;
            bichos->removeObject(this);
            theGameScene->nbugs-=1;
        }
    }
}

void Bicho::update(float dt) {
    CCPoint pos;
    pos=alas->getPosition();
    pos.x+=vx*dt;
    pos.y+=vy*dt;
    alas->setPosition(pos);
 //   cuerpo->setPosition(pos);
    if (!muerto) {
        float d_totarget=(pos.x-target.x)*(pos.x-target.x)+(pos.y-target.y)*(pos.y-target.y);
        if (target_is_hoja) {
            if(d_totarget<10) {
                float angle=target_hoja->hoja_sprite->getRotation();
                alas->setRotation(angle);
 //               cuerpo->setRotation(angle);
            }
            if (d_totarget<3 && ( vx!=0 || vy!=0 ) ) {
                vx=0;
                vy=0;
                alas->setZOrder(20);
                alas->stopAction(alas_action);
                alas_action=alas->runAction(CCRepeatForever::create(CCAnimate::create(bicho_comiendo_anim)));
//                cuerpo->stopAction(cuerpo_action);
//                cuerpo_action=cuerpo->runAction(CCRepeatForever::create(CCAnimate::create(bicho_comiendo_anim)));
//                cuerpo->resumeSchedulerAndActions();
            }
            if (vx==0 && vy==0) {
                if (!target_hoja->drain(0.2*dt) || finalmoving) {
                    decideTarget();
                    alas->setZOrder(21);
//                    cuerpo->stopAllActions();
                    alas->stopAllActions();
                    alas_action=alas->runAction(CCRepeatForever::create(CCAnimate::create(bicho_alas_anim)));
//                    cuerpo_action=cuerpo->runAction(CCRepeatForever::create(CCAnimate::create(bicho_cuerpo_anim)));
                    alas->setRotation(0);
//                    cuerpo->setRotation(0);
                }
            }
            
        } else {
            if(d_totarget<10) {
                decideTarget();
            }
        }
//        if (pos.x>480 || pos.x<0) {
//            vx=-vx;
//            alas->setFlipX(vx>0);
////            cuerpo->setFlipX(vx>0);
//        }
//        if (pos.y>320 || pos.y<0) vy=-vy;
    } else {
        vx-=0.5*dt*vx;
        vy-=50*dt;
        float a=alas->getRotation();
        //alas->setRotation(a+30*dt);
//        cuerpo->setRotation(a+10*dt);
    }
}


void Bicho::decideTarget() {
    target.x=rand_range(0, 480);
    //480*(rand()*1.0/RAND_MAX);
    target.y=rand_range(0, 320);
    //320*(rand()*1.0/RAND_MAX);
    CCPoint pos=alas->getPosition();

    target_is_hoja=false;
    if (theGameScene) { // si no es que estamos decidiendo los primeros targets
        if (!finalmoving) {
            if (rand_u() < theGameScene->bug_hunger) {
                // en este caso cambialo por una hoja
                Hoja *hoja_target=hoja_get_random_hoja();
                if (hoja_target) {
                    if (! hoja_target->falling) {
                        float alfa=rand_u();
//            target.x=pa.x*alfa+pb.x*(1-alfa);
//            target.y=pa.y*alfa+pb.y*(1-alfa);
                        target=hoja_target->getBichoPosition(alfa);
                        target_is_hoja=true;
                        target_hoja=hoja_target;
                    }
                }
            }
        } else {
            if (pos.x<240) {
                target.x=530;
            } else {
                target.x=-50;
            }
            target.y=pos.y;
        }
    }
    float decided_v=rand_range(50, 200);
    //100*(0.5*((rand()*1.0/RAND_MAX)+1));
    vx=target.x-pos.x;
    vy=target.y-pos.y;
    float vm=sqrt(vx*vx+vy*vy);
    vx=vx*decided_v/vm;
    vy=vy*decided_v/vm;
    alas->setFlipX(vx>0);
//    cuerpo->setFlipX(vx>0);
}


void bicho_update_all(float dt,bool playended) {
    Bicho *bichoaux;
    int i;
    CCPoint fumigando_p;
    bool fumigando=theGameScene->fumigando;
    if (fumigando) fumigando_p=theGameScene->player_ps->getPosition();
    if (bichos==NULL) return;
    int n=bichos->count();
    for (i=0;i<n;i++) {
        bichoaux=(Bicho *)(bichos->objectAtIndex(i));
        bichoaux->finalmoving=playended;
        if ( fumigando && ! bichoaux->muerto ) {
            bichoaux->checkdamagefrom(fumigando_p.x, fumigando_p.y);
        }
        bichoaux->update(dt);
    }
    for (i=n-1;i>=0;i--) {
        ((Bicho *)(bichos->objectAtIndex(i)))->checkAndDestroy();
    }
}

void bicho_delete_all() {
    if (bichos) {
        bichos->removeAllObjects();
        bichos->release();
        bichos=NULL;
    }
}

void bicho_forget_hoja_target(Hoja *hoja) {
    CCObject *bo;
    Bicho *b;
    CCARRAY_FOREACH(bichos, bo) {
        b=(Bicho *)bo;
        if (b->target_is_hoja && b->target_hoja==hoja) {
            b->target_is_hoja=false;
            if (b->vx==0 && b->vy==0) {
                b->alas->stopAllActions();
                b->alas_action=b->alas->runAction(CCRepeatForever::create(CCAnimate::create(bicho_alas_anim)));
                //                    cuerpo_action=cuerpo->runAction(CCRepeatForever::create(CCAnimate::create(bicho_cuerpo_anim)));
                b->alas->setRotation(0);
            }
        }
    }
}


void create_n_bichos_in(int n,Planta *parent) {
    int i;
    for (i=0;i<n;i++) {
        Bicho::create(parent,false);
    }
}

