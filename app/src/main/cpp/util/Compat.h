//
// Created by 林晨鹏 on 2018/8/23.
//

#ifndef ANDROIDSYSTEM_COMPAT_H
#define ANDROIDSYSTEM_COMPAT_H

#include <unistd.h>

/* Compatibility definitions for non-Linux (i.e., BSD-based) hosts. */
#ifndef HAVE_OFF64_T
#if _FILE_OFFSET_BITS < 64
#error "_FILE_OFFSET_BITS < 64; large files are not supported on this platform"
#endif /* _FILE_OFFSET_BITS < 64 */

typedef off_t off64_t;

static inline off64_t lseek64(int fd, off64_t offset, int whence) {
    return lseek(fd, offset, whence);
}

#ifdef HAVE_PREAD
static inline ssize_t pread64(int fd, void* buf, size_t nbytes, off64_t offset) {
    return pread(fd, buf, nbytes, offset);
}
#endif

#endif /* !HAVE_OFF64_T */

#endif /* __LIB_UTILS_COMPAT_H */


#endif //ANDROIDSYSTEM_COMPAT_H
