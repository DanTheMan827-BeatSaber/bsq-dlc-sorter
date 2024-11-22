#pragma once

// GlobalNamespace
#include "GlobalNamespace/BeatmapLevelPack.hpp"

// Usings
using namespace GlobalNamespace;

/// @brief A helper class with utility functions.
class Helpers {
public:
    /// @brief Sorts packs by name Z-A.
    /// @param a The first pack to compare.
    /// @param b The second pack to compare.
    /// @return True if pack `a`'s name is lexicographically greater than pack `b`'s name.
    static bool dlcComparer(BeatmapLevelPack* a, BeatmapLevelPack* b);
};
