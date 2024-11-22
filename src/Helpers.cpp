#include "Helpers.hpp"

// GlobalNamespace
#include "GlobalNamespace/BeatmapLevelPack.hpp"

// Usings
using namespace GlobalNamespace;

bool Helpers::dlcComparer(BeatmapLevelPack* a, BeatmapLevelPack* b) {
    return std::string(a->___packName) > std::string(b->___packName);
}
