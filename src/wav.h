//
// Created by chkp on 2024/01/16.
//

#ifndef CHK_ENG_WAV_H
#define CHK_ENG_WAV_H

#include "common.h"

typedef PACK(struct wav_header{
    u32 riff_id;
    u32 size;
    u32 wave_id;
}) wav_header_t;

typedef PACK(struct wav_fmt{
    u16 format_tag;
    u16 num_channels;
    u32 samples_per_second;
    u32 avg_bytes_per_second;
    u16 block_align;
    u16 bits_per_sample;
    u16 size;
    u16 valid_bits_per_sample;
    u32 channel_mask;
    u8 sub_format[16];
}) wav_fmt_t;

typedef PACK(struct wav_chunk{
     u32 id;
     u32 size;
 }) wav_chunk_t;

#define CHK_RIFF_CODE(a,b,c,d) (((u32)(a) << 0) | ((u32)(b) << 8) | ((u32)(c) << 16) | ((u32)(d) << 24))
typedef enum wav_chunk_id : u32 {
    WAV_CHUNK_ID_fmt = CHK_RIFF_CODE('f', 'm', 't', ' '),
    WAV_CHUNK_ID_RIFF = CHK_RIFF_CODE('R', 'I', 'F', 'F'),
    WAV_CHUNK_ID_WAVE = CHK_RIFF_CODE('W', 'A', 'V', 'E'),
} wav_chunk_id_t;

typedef struct sound {
    u16* samples;
    size_t sample_count;
} sound_t;

bool wav_load(sound_t* sound, const char* path);
bool wav_destroy(sound_t* sound);

sound_t* wav_load_allocate(const char* path);
bool wav_free(sound_t* sound);

#endif //CHK_ENG_WAV_H
