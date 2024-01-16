//
// Created by chkp on 2024/01/16.
//

#include "wav.h"
#include "file.h"
#include "log.h"

bool wav_parse(sound_t* sound, file_t* file) {
    u8* file_ptr = file->memory;
    {
        // wav_header_t* header = (wav_header_t*)file_ptr;
        // if (header->riff_id != WAV_CHUNK_ID_RIFF) { chk_log("Invalid magic, expected RIFF"); return false; }
        // if (header->wave_id != WAV_CHUNK_ID_WAVE) { chk_log("Invalid magic, expected WAVE"); return false; }

    }
    return true;
}

bool wav_load(sound_t* sound, const char* path) {
    if (!sound) { chk_log("sound was NULL"); return false; }
    assert(path != NULL);

    file_t file;
    if (!file_load(&file, path)) { return false; }

    bool loaded = wav_parse(sound, &file);
    file_destroy(&file);
    return loaded;
}

bool wav_destroy(sound_t* sound) {
    if (!sound) { chk_log("sound was NULL"); return false; }
    free(sound->samples);
    sound->samples = NULL;
    sound->sample_count = 0;
    return true;
}


sound_t* wav_load_allocate(const char* path) {
    sound_t* sound = malloc(sizeof(*sound));
    if (!wav_load(sound, path)) { free(sound); return false; }

    return sound;
}

bool wav_free(sound_t* sound) {
    if (!sound) { chk_log("sound was NULL"); return false; }

    bool result = wav_destroy(sound);
    return result;
}
