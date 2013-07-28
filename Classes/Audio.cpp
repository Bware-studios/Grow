//
//  Audio.cpp
//  Grow1
//
//  Created by Mikel on 02/06/13.
//
//

#include "Grow.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

const char *audio_spray_name="spray.wav";


SimpleAudioEngine *audio_engine;

unsigned int audio_psst_handler=0;

void audio_preload_all() {
    audio_engine->preloadEffect(audio_spray_name);
    
}

void audio_play_effect(const char *name) {
    audio_engine->playEffect(name);
}

void audio_start_psst() {
    audio_psst_handler=audio_engine->playEffect(audio_spray_name,true);
}

void audio_stop_psst() {
    audio_engine->stopEffect(audio_psst_handler);
}

