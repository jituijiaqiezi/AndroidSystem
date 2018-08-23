//
// Created by 林晨鹏 on 2018/8/23.
//

#ifndef ANDROIDSYSTEM_APKBUILDER_H
#define ANDROIDSYSTEM_APKBUILDER_H

#include <set>
#include "../util/Errors.h"
#include "../util/String8.h"
#include "../util/StrongPointer.h"
#include "../util/Vector.h"
#include "ConfigDescription.h"
#include "OutputSet.h"
#include "ResourceFilter.h"


using ResourceFilter::WeakResourceFilter;
using namespace android;
class ApkSplit;
class AaptFile;

class ApkBuilder : public android::RefBase {
public:
    explicit ApkBuilder(const sp<WeakResourceFilter>& configFilter);

    /**
     * Tells the builder to generate a separate APK for resources that
     * match the configurations specified. Split APKs can not have
     * overlapping resources.
     *
     * NOTE: All splits should be set up before any files are added.
     */
    android::status_t createSplitForConfigs(const std::set<ConfigDescription>& configs);

    /**
     * Adds a file to be written to the final APK. It's name must not collide
     * with that of any files previously added. When a Split APK is being
     * generated, duplicates can exist as long as they are in different splits
     * (resources.arsc, AndroidManifest.xml).
     */
    android::status_t addEntry(const android::String8& path, const android::sp<AaptFile>& file);

    android::Vector<sp<ApkSplit> >& getSplits() {
        return mSplits;
    }

    android::sp<ApkSplit> getBaseSplit() {
        return mSplits[0];
    }

    void print() const;

private:
    android::sp<ResourceFilter> mConfigFilter;
    android::sp<ResourceFilter::AndResourceFilter> mDefaultFilter;
    android::Vector<sp<ApkSplit> > mSplits;
};

class ApkSplit : public OutputSet {
public:
    android::status_t addEntry(const android::String8& path, const android::sp<AaptFile>& file);

    const std::set<OutputEntry>& getEntries() const {
        return mFiles;
    }

    const std::set<ConfigDescription>& getConfigs() const {
        return mConfigs;
    }

    bool matches(const sp<AaptFile>& file) const {
        return mFilter->match(file->getGroupEntry().toParams());
    }

    sp<ResourceFilter> getResourceFilter() const {
        return mFilter;
    }

    const android::String8& getPrintableName() const {
        return mName;
    }

    const android::String8& getDirectorySafeName() const {
        return mDirName;
    }

    const android::String8& getPackageSafeName() const {
        return mPackageSafeName;
    }

    bool isBase() const {
        return mIsBase;
    }

    void print() const;

private:
    friend class ApkBuilder;

    ApkSplit(const std::set<ConfigDescription>& configs, const android::sp<ResourceFilter>& filter, bool isBase=false);

    std::set<ConfigDescription> mConfigs;
    const sp<ResourceFilter> mFilter;
    const bool mIsBase;
    String8 mName;
    String8 mDirName;
    String8 mPackageSafeName;
    std::set<OutputEntry> mFiles;
};
#endif //ANDROIDSYSTEM_APKBUILDER_H
