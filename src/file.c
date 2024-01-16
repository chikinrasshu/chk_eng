//
// Created by chkp on 2024/01/16.
//

#include "file.h"
#include "log.h"

#include <stdio.h>

bool file_load(file_t* file, const char* path) {
    if (!file) { chk_log("file was NULL"); return false; }
    assert(path != NULL);

    FILE* fptr = fopen(path, "rb");
    if (!fptr) { chk_log("Failed to open '%s' for reading!", path); return false; }

    fseek(fptr, 0, SEEK_END);
    file->size = (u64)ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    file->memory = malloc(file->size);
    if (!fread(file->memory, file->size, 1, fptr)) {
        chk_log("Failed to read '%zu' bytes from file '%s'", file->size, path);
        free(file->memory);
        file->memory = NULL;
        file->size = 0;
    }

    fclose(fptr);
    return file->memory != NULL && file->size > 0;
}

bool file_destroy(file_t* file) {
    if(!file) { chk_log("file was NULL"); return false; }
    assert(file->memory != NULL);

    free(file->memory);
    file->memory = NULL;
    file->size = 0;

    return true;
}


file_t* file_load_allocate(const char* path) {
    file_t* file = malloc(sizeof(*file));
    if (!file) { chk_log("Failed to allocate %zu bytes for the file!", sizeof(*file)); return NULL; }
    if (!file_load(file, path)) { free(file); return NULL; }
    return file;
}

bool file_free(file_t* file) {
    bool result = file_destroy(file);
    free(file);
    return result;
}
