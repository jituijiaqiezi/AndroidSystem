//
//Created by android.
//

#ifndef ANDROIDSYSTEM_CONDITION_H
#define ANDROIDSYSTEM_CONDITION_H

#include <stdint.h>
#include <sys/types.h>
#include <time.h>

#if defined(HAVE_PTHREADS)
#include <pthread.h>
#endif

#include "Errors.h"
#include "Mutex.h"
#include "Timers.h"

namespace android {
    class Condition {
    public:
        enum {
            PRIVATE = 0,
            SHARED = 1
        };

        Condition();

        Condition(int type);

        ~Condition();

        status_t wait(Mutex &mutex);

        status_t waitRelative(Mutex &mutex, nsecs_t reltime);

        void signal();

        void broadcast();

    private:

#if defined(HAVE_PTHREADS)
        pthread_cond_t mCond;
#else
        void *mState;
#endif
    };

#if defined(HAVE_PTHREADS)

    inline Condition::Condition() {
        pthread_cond_init(&mCond, NULL);
    }

    inline Condition::Condition(int type) {
        if (type == SHARED) {
            pthread_condattr_t attr;
            pthread_condattr_init(&attr);
            pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
            pthread_cond_init(&mCond, &attr);
            pthread_condattr_destroy(&attr);
        } else {
            pthread_cond_init(&mCond, NULL);
        }
    }

    inline Condition::~Condition() {
        pthread_cond_destroy(&mCond);
    }

    inline status_t Condition::wait(Mutex &mutex) {
        return -pthread_cond_wait(&mCond, &mutex.mMutex);
    }

    inline status_t Condition::waitRelative(Mutex &mutex, nsecs_t reltime) {
#if defined(HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE)
        struct timespec ts;
        ts.tv_sec=reltime/1000000000;
        ts.tv_nsec=reltime%1000000000;
        return -pthread_cond_timedwait_releative_np(&mCond,&mutex.mMutex,&ts);
#else
        struct timespec ts;

#if defined(HAVE_POSIX_CLOCKS)
        clock_gettime(CLOCK_REALTIME,&ts);

#else
        struct timeval t;
        gettimeofday(&t, NULL);
        ts.tv_sec = t.tv_sec;
        ts.tv_nsec = t.tv_usec * 1000;
#endif
        ts.tv_sec += reltime / 1000000000;
        ts.tv_nsec += reltime % 1000000000;
        if (ts.tv_nsec >= 1000000000) {
            ts.tv_nsec -= 1000000000;
            ts.tv_sec += 1;
        }
        return -pthread_cond_timedwait(&mCond, &mutex.mMutex, &ts);
#endif
    }

    inline void Condition::signal() {
        pthread_cond_signal(&mCond);
    }

    inline void Condition::broadcast() {
        pthread_cond_broadcast(&mCond);
    }

#endif
}
#endif //ANDROIDSYSTEM_CONDITION_H
