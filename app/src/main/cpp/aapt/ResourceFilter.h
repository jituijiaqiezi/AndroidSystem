//
// Created by 林晨鹏 on 2018/8/23.
//

#ifndef ANDROIDSYSTEM_RESOURCEFILTER_H
#define ANDROIDSYSTEM_RESOURCEFILTER_H

#include <set>
#include <utility>
#include "../util/Errors.h"
#include "../util/String8.h"
#include "../util/StrongPointer.h"
#include "../util/Vector.h"

#include "AaptAssets.h"
#include "ConfigDescription.h"
#include "../util/RefBase.h"

class ResourceFilter : public virtual android::RefBase {
public:
    virtual bool match(const android::ResTable_config &config) const =0;

    class WeakResourceFilter : public ResourceFilter {
    public:
        WeakResourceFilter() : mContainsPseudoAccented(false), mContainsPseudoBidi(false) {}

        android::status_t parse(const android::String8 &str);

        bool match(const android::ResTable_config &config) const;

        inline bool isEmpty() const {
            return mConfigMask == 0;
        }

        inline bool containsPseudo() const {
            return mContainsPseudoAccented;
        }

        inline bool containsPseudoBidi() const {
            return mContainsPseudoBidi;
        }

    private:
        ConfigDescription mDefault;
        uint32_t mConfigMask;
        android::Vector<std::pair<ConfigDescription, uint32_t>> mConfigs;

        bool mContainsPseudoAccented;
        bool mContainsPseudoBidi;
    };

    class StrongResourceFilter : public ResourceFilter {
    public:
        StrongResourceFilter() {}

        explicit StrongResourceFilter(const std::set<ConfigDescription> &configs) : mConfigs(
                configs) {}

        android::status_t parse(const android::String8 &str);

        bool match(const android::ResTable_config &config) const {
            std::set<ConfigDescription>::const_iterator iter = mConfigs.begin();
            for (; iter != mConfigs.end(); iter++) {
                if (iter->compare(config) == 0) {
                    return true;
                }
            }
            return false;
        }

        inline const std::set<ConfigDescription> &getConfigs() const {
            return mConfigs;
        }

    private:
        std::set<ConfigDescription> mConfigs;
    };

    class InverseResourceFilter : public ResourceFilter {
    public:
        explicit InverseResourceFilter(const android::sp<ResourceFilter> &filter)
                : mFilter(filter) {}

        bool match(const android::ResTable_config &config) const {
            return !mFilter->match(config);
        }

    private:
        const android::sp<ResourceFilter> mFilter;
    };

    class AndResourceFilter : public ResourceFilter {
    public:
        void addFilter(const android::sp<ResourceFilter> &filter) {
            mFilters.add(filter);
        }

        bool match(const android::ResTable_config &config) const {
            const size_t N = mFilters.size();
            for (size_t i = 0; i < N; i++) {
                if (!mFilters[i]->match(config)) {
                    return false;
                }
            }
            return true;
        }

    private:
        android::Vector<android::sp<ResourceFilter> > mFilters;
    };

};

#endif //ANDROIDSYSTEM_RESOURCEFILTER_H
