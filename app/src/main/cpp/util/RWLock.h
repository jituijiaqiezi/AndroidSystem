//
//Created by android.
//

#ifndef ANDROIDSYSTEM_RWLOCK_H
#define ANDROIDSYSTEM_RWLOCK_H

#include <stdint.h>
#include <sys/types.h>

#if defined(HAVE_PTHREADS)
# include <pthread.h>
#endif

#include "Errors.h"
#include "ThreadDefs.h"

// ---------------------------------------------------------------------------
namespace android {
// ---------------------------------------------------------------------------

#if defined(HAVE_PTHREADS)

    /*
 * Simple mutex class.  The implementation is system-dependent.
 *
 * The mutex must be unlocked by the thread that locked it.  They are not
 * recursive, i.e. the same thread can't lock it multiple times.
 */
class RWLock {
public:
    enum {
        PRIVATE = 0,
        SHARED = 1
    };

                RWLock();
                RWLock(const char* name);
                RWLock(int type, const char* name = NULL);
                ~RWLock();

    status_t    readLock();
    status_t    tryReadLock();
    status_t    writeLock();
    status_t    tryWriteLock();
    void        unlock();

    class AutoRLock {
    public:
        inline AutoRLock(RWLock& rwlock) : mLock(rwlock)  { mLock.readLock(); }
        inline ~AutoRLock() { mLock.unlock(); }
    private:
        RWLock& mLock;
    };

    class AutoWLock {
    public:
        inline AutoWLock(RWLock& rwlock) : mLock(rwlock)  { mLock.writeLock(); }
        inline ~AutoWLock() { mLock.unlock(); }
    private:
        RWLock& mLock;
    };

private:
    // A RWLock cannot be copied
                RWLock(const RWLock&);
   RWLock&      operator = (const RWLock&);

   pthread_rwlock_t mRWLock;
};

inline RWLock::RWLock() {
    pthread_rwlock_init(&mRWLock, NULL);
}
inline RWLock::RWLock(const char* name) {
    pthread_rwlock_init(&mRWLock, NULL);
}
inline RWLock::RWLock(int type, const char* name) {
    if (type == SHARED) {
        pthread_rwlockattr_t attr;
        pthread_rwlockattr_init(&attr);
        pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        pthread_rwlock_init(&mRWLock, &attr);
        pthread_rwlockattr_destroy(&attr);
    } else {
        pthread_rwlock_init(&mRWLock, NULL);
    }
}
inline RWLock::~RWLock() {
    pthread_rwlock_destroy(&mRWLock);
}
inline status_t RWLock::readLock() {
    return -pthread_rwlock_rdlock(&mRWLock);
}
inline status_t RWLock::tryReadLock() {
    return -pthread_rwlock_tryrdlock(&mRWLock);
}
inline status_t RWLock::writeLock() {
    return -pthread_rwlock_wrlock(&mRWLock);
}
inline status_t RWLock::tryWriteLock() {
    return -pthread_rwlock_trywrlock(&mRWLock);
}
inline void RWLock::unlock() {
    pthread_rwlock_unlock(&mRWLock);
}

#endif // HAVE_PTHREADS

// ---------------------------------------------------------------------------
}; // namespace android
// ---------------------------------------------------------------------------

#endif // _LIBS_UTILS_RWLOCK_H
