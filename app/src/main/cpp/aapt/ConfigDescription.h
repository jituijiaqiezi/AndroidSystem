//
// Created by 林晨鹏 on 2018/8/23.
//

#ifndef ANDROIDSYSTEM_CONFIGDESCRIPTION_H
#define ANDROIDSYSTEM_CONFIGDESCRIPTION_H

#include "../androidfw/ResourceTypes.h"

struct ConfigDescription : public android::ResTable_config {
    ConfigDescription() {
        memset(this, 0, sizeof(*this));
        size = sizeof(android::ResTable_config);
    }

    ConfigDescription(const android::ResTable_config&o) {  // NOLINT(implicit)
        *static_cast<android::ResTable_config*>(this) = o;
        size = sizeof(android::ResTable_config);
    }

    ConfigDescription(const ConfigDescription&o) {
        *static_cast<android::ResTable_config*>(this) = o;
    }

    ConfigDescription& operator=(const android::ResTable_config& o) {
        *static_cast<android::ResTable_config*>(this) = o;
        size = sizeof(android::ResTable_config);
        return *this;
    }

    ConfigDescription& operator=(const ConfigDescription& o) {
        *static_cast<android::ResTable_config*>(this) = o;
        return *this;
    }

    inline bool operator<(const ConfigDescription& o) const { return compare(o) < 0; }
    inline bool operator<=(const ConfigDescription& o) const { return compare(o) <= 0; }
    inline bool operator==(const ConfigDescription& o) const { return compare(o) == 0; }
    inline bool operator!=(const ConfigDescription& o) const { return compare(o) != 0; }
    inline bool operator>=(const ConfigDescription& o) const { return compare(o) >= 0; }
    inline bool operator>(const ConfigDescription& o) const { return compare(o) > 0; }
};


#endif //ANDROIDSYSTEM_CONFIGDESCRIPTION_H
