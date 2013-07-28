//
//  Audio.h
//  Grow1
//
//  Created by Mikel on 02/06/13.
//
//

#ifndef __Grow1__Audio__
#define __Grow1__Audio__

extern const char *audio_spray_name;


void audio_preload_all();
void audio_play_effect(const char *name);

void audio_start_psst();
void audio_stop_psst();

#endif /* defined(__Grow1__Audio__) */
