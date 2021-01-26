#include <stdio.h>

#include <Taida/audio.h>

int main()
{
    taida_init_audio(NULL);

    taida_audio_t *taida_audio1 = taida_load_audio("assets/spell1_0.wav");
    // taida_audio_t *taida_audio2 = taida_load_audio("assets/spell1_0.wav");
    taida_audio_t *taida_audio2 = taida_load_audio("assets/dark fallout.ogg");

    if (!taida_audio1 || !taida_audio2)
    {
        return 1;
    }

    taida_play_audio(taida_audio1);
    taida_play_audio(taida_audio2);
    do
    {
    } while (taida_is_playing_audio(taida_audio2));

    taida_destroy_audio(taida_audio1);
    taida_destroy_audio(taida_audio2);

    taida_close_audio();
}
