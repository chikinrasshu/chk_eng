//
// Created by chkp on 2024/01/16.
//

#ifndef CHK_ENG_LOG_H
#define CHK_ENG_LOG_H

#include "common.h"

s32 internal_log(const char* msg, const char* file, s32 line, const char* func, ...);

#define chk_log(msg, ...) internal_log(msg, __FILE__, __LINE__, __func__,##__VA_ARGS__)

#endif //CHK_ENG_LOG_H
