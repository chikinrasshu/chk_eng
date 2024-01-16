#include "common.h"
#include "file.h"
#include "log.h"
#include "window.h"

CHK_WINDOW_FN(on_start) {
    // chk_log("Start!");
}

CHK_WINDOW_FN(on_close) {
    // chk_log("Close!");
}

CHK_WINDOW_FN(on_frame) {
    // chk_log("Frame!");
}

int main() {
    window_t window = {0};
    if (!window_create(&window, 800, 600, "chk_engine")) { return EXIT_FAILURE; }

    // Read the dummy file
    file_t dummy = {0};
    if (!file_load(&dummy, "data/sounds/test.wav")) { return EXIT_FAILURE; }

    window.on_start_fn = on_start;
    window.on_close_fn = on_close;
    window.on_frame_fn = on_frame;

    s32 result = window_run(&window);
    window_destroy(&window);
    return result;
}
