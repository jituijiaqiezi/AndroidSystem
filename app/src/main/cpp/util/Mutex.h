//
//Created by android.
//

#ifndef ANDROIDSYSTEM_MUTEX_H
#define ANDROIDSYSTEM_MUTEX_H

#include <stdint.h>
#include <sys/types.h>
#include <time.h>

#if defined(HAVE_PTHREADS)
#include <pthread.h>
#endif

#include "Errors.h"

namespace android {
    class Condition;

    class Mutex {
    public:
        enum {
            PRIVATE = 0,
            SHARED = 1
        };

        Mutex();

        Mutex(const char *name);

        Mutex(int type, const char *name = NULL);

        ~Mutex();

        status_t lock();

        void unlock();

        status_t tryLock();

        class AutoLock {
        public:
            inline AutoLock(Mutex &mutex) : mLock(mutex) { mLock.lock(); }

            inline AutoLock(Mutex *mutex) : mLock(*mutex) {
                mLock.lock();
            }

            inline ~AutoLock() {
                mLock.unlock();
            }

        private:
            Mutex &mLock;
        };

    private:
        friend class Condition;

        Mutex(const Mutex &);

        Mutex &operator=(const Mutex &);

#if defined(HAVE_PTHREADS)
        pthread_mutex_t mMutex;
#else

        void _init();

        void *mState;
#endif
    };

#if defined(HAVE_PTHREADS)
    inline Mutex::Mutex(){
        pthread_mutex_init(&mMutex,NULL);
    }

    inline Mutex::Mutex(const char* name) {
            pthread_mutex_init(&mMutex, NULL);
        }
    inline Mutex::Mutex(int type, const char* name) {
            if (type == SHARED) {
                    pthread_mutexattr_t attr;
                    pthread_mutexattr_init(&attr);
                    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
                    pthread_mutex_init(&mMutex, &attr);
                    pthread_mutexattr_destroy(&attr);
                } else {
                    pthread_mutex_init(&mMutex, NULL);
                }
        }
    inline Mutex::~Mutex() {
            pthread_mutex_destroy(&mMutex);
        }
    inline status_t Mutex::lock() {
            return -pthread_mutex_lock(&mMutex);
        }
    inline void Mutex::unlock() {
            pthread_mutex_unlock(&mMutex);
        }
    inline status_t Mutex::tryLock() {
            return -pthread_mutex_trylock(&mMutex);
        }

#endif // HAVE_PTHREADS

    typedef Mutex::AutoLock AutoMutex;

}
#endif //ANDROIDSYSTEM_MUTEX_H
