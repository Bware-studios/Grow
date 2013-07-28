//
//  GameScene.h
//  Grow1
//
//  Created by Mikel on 14/05/13.
//
//

#ifndef __Grow1__GameScene__
#define __Grow1__GameScene__



class GameScene : public cocos2d::CCScene {
    
public:
    GameScene();
    ~GameScene();
    bool init();
    void resetGameState();
    static GameScene *create(int n);
    
    void update(float dt);


    void click(float x, float y);
    void move(float x, float y);
    void unclick();

    
    void bicho_arrival();

    void set_dificultad(int i);
    void grow_reduce_1hoja();
    void flor_grown();

    void schedule_game_exit(float dt);
    void game_exit();
    
    CCLayer *fondo;
    CCSprite *fondo_sprite;
    Planta *plantaLayer;
    CCLayer *marcadores;
    CCLabelTTF *left;
    CCLabelTTF *right;
    
    
    CCParticleSmoke *player_ps;
    bool fumigando;
    
    bool playended;
    
    // new bugs per second
    float new_bugs_rate;
    bool generate_bugs;
    int nbugs;
    int max_nbugs;
    // probabilidad de elegir de target una hoja
    float bug_hunger;
    // insecticida
    float load;
    // load per second
    float reloading_rate;
    float unloading_rate;
    // plant
    float grow_rate;
    float grow_reductions;
    // hojas
    int live_hojas;
    int max_hojas;
    
};

extern GameScene *theGameScene;



#endif /* defined(__Grow1__GameScene__) */
