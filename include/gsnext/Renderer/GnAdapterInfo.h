#pragma once

#include <gsnext/GnCommon.h>

typedef uint64_t GnAdapterId;

struct GnAdapterInfo
{
    GnAdapterId id;
    uint32_t deviceId;
    uint32_t vendorId;
    char name[GN_MAX_CHAR];
};
