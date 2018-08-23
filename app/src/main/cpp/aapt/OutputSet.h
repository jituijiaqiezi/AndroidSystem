//
// Created by 林晨鹏 on 2018/8/23.
//

#ifndef ANDROIDSYSTEM_OUTPUTSET_H
#define ANDROIDSYSTEM_OUTPUTSET_H

#include <set>
#include "../util/Errors.h"
#include "../util/String8.h"
#include "../util/StrongPointer.h"
#include "../util/RefBase.h"


class AaptFile;

class OutputEntry {
public:
    OutputEntry() {}
    OutputEntry(const android::String8& path, const android::sp<const AaptFile>& file)
            : mPath(path), mFile(file) {}

    inline const android::sp<const AaptFile>& getFile() const {
        return mFile;
    }

    inline const android::String8& getPath() const {
        return mPath;
    }

    bool operator<(const OutputEntry& o) const { return getPath() < o.mPath; }
    bool operator==(const OutputEntry& o) const { return getPath() == o.mPath; }

private:
    android::String8 mPath;
    android::sp<const AaptFile> mFile;
};

class OutputSet : public virtual android::RefBase {
public:
    virtual const std::set<OutputEntry>& getEntries() const = 0;

    virtual ~OutputSet() {}
};
#endif //ANDROIDSYSTEM_OUTPUTSET_H
