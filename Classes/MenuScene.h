//
//  MenuScene.h
//  Grow1
//
//  Created by Mikel on 08/05/13.
//
//

#ifndef __Grow1__MenuScene__
#define __Grow1__MenuScene__


extern bool debugOption;
extern bool dontdieOption;


CCMenuItemLabel *MakeMenuItem(const char *texto, float x, float y,ccColor3B color, CCObject *target, SEL_MenuHandler selector);

class MenuScene : public cocos2d::CCScene {
    
public:
    MenuScene();
    ~MenuScene();
    bool init();
    static MenuScene *create();
    void action_enter1(CCObject *sender);
    void action_enter2(CCObject *sender);
    void action_toggleDebug(CCObject *sender);
    void action_toggleDontdie(CCObject *sender);
    void action_options(CCObject *sender);
    void action_back(CCObject *sender);

    void changeToOptions();
    void changeToMain();
    
    void mainEnterActions();
    void mainCleanActions();
    void optionsEnterActions();
    void optionsCleanActions();
    
    
    CCLayer *fondo;
    CCSprite *fondo_sprite;

    CCMenu *menu;
    CCMenu *options;
    CCMenu *visible_menu;
    
    CCLayerGradient *fondo_optionsMenu;
    CCMenuItemLabel *debugOptionMenuItem;
    CCMenuItemLabel *dontdieOptionMenuItem;

    
    CCSprite *titulo_sprite;
    CCMenuItemImage *boton_play;
    CCMenuItemImage *boton_info;
    
    
};





extern MenuScene *theMenuScene;



#endif /* defined(__Grow1__MenuScene__) */
