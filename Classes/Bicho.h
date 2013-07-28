//
//  Bicho.h
//  Grow1
//
//  Created by Mikel on 21/05/13.
//
//

#ifndef __Grow1__Bicho__
#define __Grow1__Bicho__

class Hoja;
class Planta;

class Bicho : public CCObject {
    
public:
    Bicho();
    ~Bicho();
    bool init(CCNode *parent, bool outofscreen);
    static Bicho *create(CCNode *parent, bool outofscreen);
    void checkdamagefrom(float x, float y);
    void checkAndDestroy();

    void update(float dt);
    
    
    void decideTarget();
    
    CCSprite *alas;
//    CCSprite *cuerpo;
    CCAction *alas_action;
//    CCAction *cuerpo_action;
    
    float vx;
    float vy;

    
    CCPoint target;
    bool target_is_hoja;
    Hoja *target_hoja;
    
    bool muerto;
    bool finalmoving;
};

void bicho_update_all(float dt,bool playended);
void bicho_delete_all();
void bicho_forget_hoja_target(Hoja *hoja);
void create_n_bichos_in(int n,Planta *parent);

#endif 