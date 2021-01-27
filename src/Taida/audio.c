#include "Taida/audio.h"
#include "Taida/utils/log.h"

#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

#include <AL/alc.h>
#include <AL/alext.h>

#include <sndfile.h>

ALuint taida_get_audio_buffer(const char*);
ALuint taida_gen_audio_source(ALuint);

int taida_init_audio(const ALchar *devicename)
{
    const ALCchar *name;
    ALCdevice *device;
    ALCcontext *ctx;

    device = alcOpenDevice(devicename);

    if (!device)
    {
        taida_log_error("Could not open a device!");
        return 1;
    }

    ctx = alcCreateContext(device, NULL);
    if (ctx == NULL || alcMakeContextCurrent(ctx) == ALC_FALSE)
    {
        if (ctx != NULL)
        {
            alcDestroyContext(ctx);
        }
        alcCloseDevice(device);
        taida_log_error("Could not set a context!");
        return 1;
    }

    name = NULL;
    if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
    {
        name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    }
    if (!name || alcGetError(device) != AL_NO_ERROR)
    {
        name = alcGetString(device, ALC_DEVICE_SPECIFIER);
    }

    char info[250];
    snprintf(info, 250, "Opened \"%s\"\n", name);
    taida_log_info(info);

    return 0;
}

void taida_close_audio(void)
{
    ALCdevice *device;
    ALCcontext *ctx;

    ctx = alcGetCurrentContext();
    if (ctx == NULL)
        return;

    device = alcGetContextsDevice(ctx);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(device);
}

taida_audio_t *taida_load_audio(const char *filename)
{
    taida_audio_t *taida_audio = malloc(sizeof(taida_audio_t));
    taida_audio->buffer = taida_get_audio_buffer(filename);

    if (!taida_audio->buffer)
    {
        taida_destroy_audio(taida_audio);
        return 0;
    }

    taida_audio->source = taida_gen_audio_source(taida_audio->buffer);
    return taida_audio;
}

void taida_destroy_audio(taida_audio_t *taida_audio)
{
    if (taida_audio->source)
    {
        alDeleteSources(1, &taida_audio->source);
    }
    if (taida_audio->buffer)
    {
        alDeleteBuffers(1, &taida_audio->buffer);
    }

    free(taida_audio);
}

ALuint taida_get_audio_buffer(const char *filename)
{
    ALenum err, format;
    ALuint buffer;
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    short *membuf;
    sf_count_t num_frames;
    ALsizei num_bytes;

    char msg[500];

    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile)
    {
        snprintf(msg, 500, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
        taida_log_error(msg);
        return 0;
    }

    if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
    {
        snprintf(msg, 500, "Bad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
        taida_log_error(msg);
        sf_close(sndfile);
        return 0;
    }

    /* Get the sound format, and figure out the OpenAL format */
    format = AL_NONE;
    if (sfinfo.channels == 1)
        format = AL_FORMAT_MONO16;
    else if (sfinfo.channels == 2)
        format = AL_FORMAT_STEREO16;
    else if (sfinfo.channels == 3)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT2D_16;
    }
    else if (sfinfo.channels == 4)
    {
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT3D_16;
    }
    if (!format)
    {
        snprintf(msg, 500, "Unsupported channel count: %d\n", sfinfo.channels);
        taida_log_error(msg);
        sf_close(sndfile);
        return 0;
    }

    /* Decode the whole audio file to a buffer. */
    membuf = malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short));

    num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
    if (num_frames < 1)
    {
        free(membuf);
        sf_close(sndfile);
        snprintf(msg, 500, "Failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
        taida_log_error(msg);
        return 0;
    }
    num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

    /* Buffer the audio data into a new buffer object, then free the data and
     * close the file.
     */
    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

    free(membuf);
    sf_close(sndfile);

    /* Check if an error occured, and clean up if so. */
    err = alGetError();
    if (err != AL_NO_ERROR)
    {
        snprintf(msg, 500, "OpenAL Error: %s\n", alGetString(err));
        taida_log_error(msg);
        if (buffer && alIsBuffer(buffer))
            alDeleteBuffers(1, &buffer);
        return 0;
    }

    return buffer;
}

ALuint taida_gen_audio_source(ALuint buffer)
{
    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, (ALint)buffer);

    if (alGetError() != AL_NO_ERROR)
    {
        taida_log_error("Failed to setup sound source");
    }

    return source;
}

void taida_play_audio(taida_audio_t *taida_audio)
{
    alSourcePlay(taida_audio->source);
}

int taida_is_playing_audio(taida_audio_t *taida_audio)
{
    ALenum state;
    alGetSourcei(taida_audio->source, AL_SOURCE_STATE, &state);
    return alGetError() == AL_NO_ERROR && state == AL_PLAYING;
}

ALfloat taida_playing_audio_offset(taida_audio_t *taida_audio)
{
    ALfloat offset;
    alGetSourcef(taida_audio->source, AL_SEC_OFFSET, &offset);
    return offset;
}