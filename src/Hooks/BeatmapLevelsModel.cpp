#include "main.hpp"
#include "autohooks.hpp"
#include "Helpers.hpp"

// GlobalNamespace
#include "GlobalNamespace/BeatmapLevelPack.hpp"
#include "GlobalNamespace/BeatmapLevelsModel.hpp"

// C++
#include <algorithm>

// Usings
using namespace GlobalNamespace;
using namespace System::Collections::Generic;

// Sorts the level packs by name descending (the game loads them in reverse order)
MAKE_AUTO_HOOK_MATCH(BeatmapLevelsModel_LoadAllBeatmapLevelPacks, &BeatmapLevelsModel::LoadAllBeatmapLevelPacks, void, BeatmapLevelsModel* self) {
    Logger.debug("BeatmapLevelsModel_LoadAllBeatmapLevelPacks");

    // Call the original to set up dlcBeatmapLevelsRepository
    BeatmapLevelsModel_LoadAllBeatmapLevelPacks(self);

    // Store the level packs in a variable to make the code cleaner.
    auto packs = self->___dlcBeatmapLevelsRepository->____beatmapLevelPacks;

    // Sort the packs
    std::stable_sort(packs.begin(), packs.end(), Helpers::dlcComparer);

    // Log the new order.
    for (auto pack : packs) {
        Logger.debug("{}", pack->___packName);
    }
}
