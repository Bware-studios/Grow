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
    void game_lost();
    void flor_grown();

    void score_update_1kill();
    void score_update_grow();
    void score_update();
    
    void schedule_game_exit(float dt);
    void game_exit();
    
    void action_pause_button();
    void action_unpause_button();
    
    void end_game_results();

    
    CCLayer *fondo;
    CCSprite *fondo_sprite;
    Planta *plantaLayer;
    CCLayer *marcadores;
    CCLabelTTF *left;
    CCLabelTTF *right;
    
    
    CCParticleSmoke *player_ps;
    bool fumigando;
    
    
    CCLayer *ingame_controls_layer;
    CCLayerGradient *ingame_results;
    CCLayerGradient *ingame_pause_layer;
    
    bool playended;
    bool gamepaused;

    bool gamewon;
    
    bool call_bicho_arrival_after_pause;

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
    
    
    
    // score
    // por crecer la flor 1.0 es completamente todo
    float score_grow;
    // por matar bichos
    float score_kill;
    int score_num_kills;
    
    // acumulado en multiples rondas
    float score_total;
    
};

extern GameScene *theGameScene;



#endif /* defined(__Grow1__GameScene__) */
