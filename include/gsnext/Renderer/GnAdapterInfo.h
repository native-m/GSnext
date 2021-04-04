#pragma once

#include <gsnext/GnCommon.h>

union GnAdapterId
{
    char c[GN_ID_LENGTH];
    uint64_t u64[GN_ID_LENGTH / sizeof(uint64_t)];

    GnAdapterId();

    void FromString(const std::string& str);
    std::string ToString();
};

struct GnAdapterInfo
{
    GnAdapterId id;
    uint32_t deviceId;
    uint32_t vendorId;
    char name[GN_MAX_CHAR];
};
