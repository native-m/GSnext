#include <gsnext/Renderer/GnAdapterInfo.h>
#include <spdlog/fmt/fmt.h>

GnAdapterId::GnAdapterId() :
    u64{0, 0}
{
}

GnAdapterId::GnAdapterId(const GnAdapterId& other) :
    u64 { other.u64[0], other.u64[1] }
{
}

void GnAdapterId::FromString(const std::string& str)
{
    if (str == "0") {
        // reset to default adapter
        u64[0] = 0;
        u64[1] = 0;
        return;
    }

    if (str.length() < 32) {
        // skip invalid ID
        return;
    }

    for (uint32_t i = 0; i < 16; i++) {
        c[i] = static_cast<char>(std::stoi(str.substr(i * 2, 2), nullptr, 16));
    }
}

std::string GnAdapterId::ToString()
{
    if (u64[0] == 0 && u64[1] == 0) {
        return "0";
    }

    return fmt::format("{:016x}{:016x}", u64[0], u64[1]);
}
