//
//  Planta.h
//  Grow1
//
//  Created by Mikel on 25/05/13.
//
//

#ifndef __Grow1__Planta__
#define __Grow1__Planta__

class GameScene;

class Planta : public CCLayer {
    
public:
    Planta();
    ~Planta();
    bool init(GameScene *parent);
    static Planta *create(GameScene *parent);
    
    void update(float dt);
    void draw(void);
    
    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    void ccTouchMoved(CCTouch *touch, CCEvent *event);
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
    void ccTouchCancelled(CCTouch *touch, CCEvent *event);

    
    GameScene *parent;
    float grow;
    CCPoint vs[16];
    CCPoint draw_vs[16];
    float altura[4];
    
    float x[5];
    float y[5];
    float alfa[4];
    float progreso;
    
   // CCSprite *hoja_sprite[3];
    CCSprite *flor_sprite;
    CCSprite *tallo_sprite[4];
    int fase;
    
    bool touching;
    
};






#endif /* defined(__Grow1__Planta__) */
