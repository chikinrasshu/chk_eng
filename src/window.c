//
// Created by chkp on 2024/01/16.
//

#include "window.h"
#include "log.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// Fwd callbacks
void window_cb_pos(GLFWwindow* handle, int x, int y);
void window_cb_size(GLFWwindow* handle, int w, int h);
void window_cb_frame(GLFWwindow* handle);
void window_cb_scale(GLFWwindow* handle, float sx, float sy);

bool window_create(window_t* window, s32 w, s32 h, const char* caption) {
    if (!window) { chk_log("window '%s' was NULL", caption); return false; }

    if (!glfwInit()) { free(window); chk_log("Failed to initialize GLFW!"); return false; }

    GLFWwindow* handle = glfwCreateWindow(w, h, caption, NULL, NULL);
    if (!handle) { free(window); chk_log("Failed to create the main window!"); return false; }

    glfwSetWindowUserPointer(handle, window);
    glfwSetWindowPosCallback(handle, window_cb_pos);
    glfwSetWindowSizeCallback(handle, window_cb_size);
    glfwSetWindowRefreshCallback(handle, window_cb_frame);
    glfwSetWindowContentScaleCallback(handle, window_cb_scale);

    window->internal_handle = handle;
    return true;
}

bool window_destroy(window_t* window) {
    if(!window) { chk_log("window was NULL"); return false; }
    assert(window->internal_handle != NULL);

    bool result = window_close(window);
    window->internal_handle = NULL;

    return result;
}


window_t* window_create_allocate(s32 w, s32 h, const char* caption) {
    window_t* window = malloc(sizeof(*window));
    if (!window) { chk_log("Failed to allocate %zu bytes for the window!", sizeof(*window)); return NULL; }
    if (!window_create(window, w, h, caption)) { free(window); return NULL; }
    return window;
}

bool window_free(window_t* window) {
    if (!window) { chk_log("window was NULL"); return false; }
    bool result = window_destroy(window);
    free(window);

    return result;
}


s32 window_run(window_t* window) {
    if(!window) { chk_log("window was NULL"); return EXIT_FAILURE; }
    assert(window->internal_handle != NULL);

    if (window->on_start_fn) { window->on_start_fn(window->user_ptr); }
    while(!glfwWindowShouldClose(window->internal_handle)) {
        if (window->on_frame_fn) { window->on_frame_fn(window->user_ptr); }
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

bool window_close(window_t* window) {
    if (!window) { return false; }
    assert(window->internal_handle != NULL);

    if (window->on_close_fn) { window->on_close_fn(window->user_ptr); }
    glfwDestroyWindow(window->internal_handle);

    return true;
}

// Setters
void window_set_user_ptr(window_t* window, void* user_ptr) { window->user_ptr = user_ptr; }
void window_set_on_start(window_t* window, window_fn_t* start_fn) { window->on_start_fn = start_fn; }
void window_set_on_close(window_t* window, window_fn_t* close_fn) { window->on_close_fn = close_fn; }
void window_set_on_frame(window_t* window, window_fn_t* frame_fn) { window->on_frame_fn = frame_fn; }

// Callbacks
#define CHK_WPTR window_t* window = glfwGetWindowUserPointer(handle)
void window_cb_pos(GLFWwindow* handle, int x, int y) { CHK_WPTR; window->x = x; window->y = y; }
void window_cb_size(GLFWwindow* handle, int w, int h) { CHK_WPTR; window->w = w; window->h = h; }
void window_cb_frame(GLFWwindow* handle) { CHK_WPTR; if (window->on_frame_fn) { window->on_frame_fn(window->user_ptr); } }
void window_cb_scale(GLFWwindow* handle, float sx, float sy) { CHK_WPTR; window->scale_x = sx; window->scale_y = sy; }
#undef CHK_WPTR
