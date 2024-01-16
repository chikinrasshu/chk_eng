//
// Created by chkp on 2024/01/16.
//

#include "log.h"
#include <stdarg.h>
#include <stdio.h>

s32 internal_log(const char* msg, const char* file, s32 line, const char* func, ...) {
    va_list args;
    va_start(args, func);

    s32 written = printf("%s : %s(%u) => ", file, func, line);
    written += vprintf(msg, args);
    written += printf("\n");

    va_end(args);
    return written;
}
