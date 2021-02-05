#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <AL/al.h>

typedef struct taida_audio
{
    ALuint source, buffer;
} taida_audio_t;

int taida_init_audio(const ALchar*);
void taida_close_audio(void);
taida_audio_t *taida_load_audio(const char*);
void taida_destroy_audio(taida_audio_t*);

void taida_play_audio(taida_audio_t*);
int taida_is_playing_audio(taida_audio_t*);
ALfloat taida_playing_audio_offset(taida_audio_t*);

#endif /* _AUDIO_H_ */
