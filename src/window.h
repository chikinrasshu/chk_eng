//
// Created by chkp on 2024/01/16.
//

#ifndef CHK_ENG_WINDOW_H
#define CHK_ENG_WINDOW_H

#include "common.h"

typedef struct window window_t;
#define CHK_WINDOW_FN(fn_name) void fn_name(void* user_ptr)
typedef CHK_WINDOW_FN(window_fn_t);

typedef struct window {
    s32 x, y;
    s32 w, h;
    r32 scale_x, scale_y;

    void* user_ptr;
    window_fn_t* on_start_fn;
    window_fn_t* on_close_fn;
    window_fn_t* on_frame_fn;

    void* internal_handle;
} window_t;

bool window_create(window_t* window, s32 w, s32 h, const char* caption);
bool window_destroy(window_t* window);

window_t* window_create_allocate(s32 w, s32 h, const char* caption);
bool window_free(window_t* window);

s32 window_run(window_t* window);
bool window_close(window_t* window);

#endif //CHK_ENG_WINDOW_H
