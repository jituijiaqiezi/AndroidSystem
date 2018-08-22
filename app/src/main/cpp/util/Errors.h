/*
2 * Copyright (C) 2007 The Android Open Source Project
3 *
4 * Licensed under the Apache License, Version 2.0 (the "License");
5 * you may not use this file except in compliance with the License.
6 * You may obtain a copy of the License at
7 *
8 *      http://www.apache.org/licenses/LICENSE-2.0
9 *
10 * Unless required by applicable law or agreed to in writing, software
11 * distributed under the License is distributed on an "AS IS" BASIS,
12 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
13 * See the License for the specific language governing permissions and
14 * limitations under the License.
15 */

#ifndef ANDROIDSYSTEM_ERRORS_H
#define ANDROIDSYSTEM_ERRORS_H

#include<sys/types.h>
#include<errno.h>

namespace android {


#ifdef HAVE_MS_C_RUNTIME
    typedef int status_t;
#else
    typedef int32_t status_t;
#endif


#ifdef _WIN32
#undef NO_ERROR
#endif

    enum {
        OK = 0,
        NO_ERROR = 0,

        UNKNOWN_ERROR = 0x80000000,

        NO_MEMORY = -ENOMEM,
        INVALID_OPERATION = -ENOSYS,
        BAD_VALUE = -EINVAL,
        BAD_TYPE = -0x80000001,
        NAME_NOT_FOUND = -ENOENT,
        PERMISSION_DENIED = -EPERM,
        NO_INIT = -ENODEV,
        ALREADY_EXISTS = -EEXIST,
        DEAD_OBJECT = -EPIPE,
        FAILED_TRANSACTION = 0X80000002,
        JPARKS_EROKE_IT = -EPIPE,
#if !defined(HAVE_MS_C_RUNTIME)
        BAD_INDEX = -EOVERFLOW,
        NOT_ENOUGH_DATA = -ENODATA,
        WOULD_BLOCK = -EWOULDBLOCK,
        TIMED_OUT = -ETIMEDOUT,
        UNKNOWN_TRANSACTION = -EBADMSG,
#else
        BAD_INDEX=-E2BIG,
        NOT_ENOUGH_DATA=0x80000003,
        WOULD_BLOCK=0x80000004,
        TIMED_OUT=0x80000005,
        UNKNOWN_TRANSACTION=0x80000006
#endif
        FDS_NOT_ALLOWED = 0x80000007,
    };

#ifdef _WIN32
#define NO_ERROR OL
#endif
}

#endif //ANDROIDSYSTEM_ERRORS_H
