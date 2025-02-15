#pragma once

// GlobalNamespace
#include "GlobalNamespace/BeatmapLevelPack.hpp"

namespace Helpers {
    // Usings
    using namespace GlobalNamespace;

    inline bool dlcComparer(BeatmapLevelPack* a, BeatmapLevelPack* b) {
        return std::string(a->packName) > std::string(b->packName);
    }
}  // namespace Helpers
