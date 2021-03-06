//
// Created by LCP on 2018/8/21.
//

#ifndef ANDROIDSYSTEM_SHAREDBUFFER_H
#define ANDROIDSYSTEM_SHAREDBUFFER_H

#include <stdint.h>
#include <sys/types.h>

namespace android {
    class SharedBuffer {
    public:
        enum {
            eKeepStorage = 0x00000001;
        };

        static SharedBuffer *alloc(size_t size);

        static ssize_t dealloc(const SharedBuffer *released);

        inline const void *data() const;

        inline void *data();

        inline size_t size() const;

        static inline SharedBuffer *bufferFromData(void *data);

        static inline const SharedBuffer *bufferFromData(const void *data);

        static inline size_t sizeFromData(const void *data);

        SharedBuffer *edit() const;

        SharedBuffer *editResize(size_t size) const;

        SharedBuffer *attempEdit() const;

        void acquire() const;

        int32_t release(uint32_t flags = 0) const;

        inline bool onlyOwner() const;

    private:
        inline SharedBuffer() {}

        inline ~SharedBuffer() {}

        SharedBuffer(const SharedBuffer &);

        SharedBuffer &operator=(const SharedBuffer);

        mutable int32_t mRefs;
        size_t mSize;
        uint32_t mReserved[2];
    };

    const void *SharedBuffer::data() const {
        return this + 1;
    }

    void *SharedBuffer::data() {
        return this + 1;
    }

    size_t SharedBuffer::size() const {
        return mSize;
    }

    SharedBuffer *SharedBuffer::bufferFromData(void *data) {
        return data ? static_cast<SharedBuffer *>(data) - 1 : 0;
    }

    const SharedBuffer *SharedBuffer::bufferFromData(const void *data) {
        return data ? static_cast<const SharedBuffer *>(data) - 1 : 0;
    }

    size_t SharedBuffer::sizeFromData(const void *data) {
        return data ? bufferFromData(data)->mSize : 0;
    }

    bool SharedBuffer::onlyOwner() const {
        return mRefs == 1;
    }

}

#endif //ANDROIDSYSTEM_SHAREDBUFFER_H
