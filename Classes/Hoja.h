//
//  Hoja.h
//  Grow1
//
//  Created by Mikel on 28/05/13.
//
//

#ifndef __Grow1__Hoja__
#define __Grow1__Hoja__


class Hoja : public CCObject {
    
public:
    Hoja();
    ~Hoja();
    bool init(CCNode *parent, CCPoint pos, bool fliped);
    static Hoja *create(CCNode *parent, CCPoint pos, bool fliped);
    
    void update(float dt);
    
    void checkAndDestroy();
    
    bool drain(float dlife);

    
    // punto inicial y final donde parar un bicho
    CCPoint getBichoPosition(float alfa);
    
    CCSprite *hoja_sprite;
    
    int damage;
    float vida;
    float maxvida;
    bool falling;
};

void hoja_update_all(float dt);
void hoja_delete_all();
Hoja *hoja_get_random_hoja();

#endif /* defined(__Grow1__Hoja__) */
