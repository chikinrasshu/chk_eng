//
// Created by chkp on 2024/01/16.
//

#ifndef CHK_ENG_FILE_H
#define CHK_ENG_FILE_H

#include "common.h"

typedef struct file {
    u8* memory;
    u64 size;
} file_t;

bool file_load(file_t* file, const char* path);
bool file_destroy(file_t* file);

file_t* file_load_allocate(const char* path);
bool file_free(file_t* file);

#endif //CHK_ENG_FILE_H
