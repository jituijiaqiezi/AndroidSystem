//
// Created by 林晨鹏 on 2018/8/23.
//

#ifndef ANDROIDSYSTEM_LOCALEDATA_H
#define ANDROIDSYSTEM_LOCALEDATA_H

#include <stddef.h>
#include <stdint.h>

namespace android {

    int localeDataCompareRegions(
            const char *left_region, const char *right_region,
            const char *requested_language, const char *requested_script,
            const char *requested_region);

    void localeDataComputeScript(char out[4], const char *language, const char *region);

    bool localeDataIsCloseToUsEnglish(const char *region);

} // namespace android

#endif //ANDROIDSYSTEM_LOCALEDATA_H
