#pragma region Includes
#include "main.hpp"

// GlobalNamespace
#include "GlobalNamespace/BeatmapLevelPack.hpp"
#include "GlobalNamespace/BeatmapLevelsModel.hpp"

// System
#include "System/Collections/Generic/IEnumerable_1.hpp"
#include "System/Collections/Generic/IReadOnlyList_1.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "System/Linq/Enumerable.hpp"

// C++
#include <algorithm>
#pragma endregion

#pragma region Usings
using namespace GlobalNamespace;
using namespace System::Collections::Generic;
#pragma endregion

/// @brief Sorts packs by name Z-A.
/// @param a The first pack to compare.
/// @param b The second pack to compare.
/// @return
bool dlc_comparer(BeatmapLevelPack* a, BeatmapLevelPack* b) {
    return std::string(a->___packName) > std::string(b->___packName);
}

#pragma region Hook definitions
MAKE_HOOK_MATCH(BeatmapLevelsModel_LoadAllBeatmapLevelPacks, &BeatmapLevelsModel::LoadAllBeatmapLevelPacks, void, BeatmapLevelsModel* self) {
    Logger.debug("BeatmapLevelsModel_LoadAllBeatmapLevelPacks");

    // Call the original to set up dlcBeatmapLevelsRepository
    BeatmapLevelsModel_LoadAllBeatmapLevelPacks(self);

    // Store the level packs in a variable to make the code cleaner.
    auto packs = self->___dlcBeatmapLevelsRepository->____beatmapLevelPacks;

    // Sort the packs
    std::stable_sort(packs.begin(), packs.end(), dlc_comparer);

    // Log the new order.
    for (auto pack : packs) {
        Logger.debug("{}", pack->___packName);
    }
}
#pragma endregion

#pragma region Mod setup
/// @brief Called at the early stages of game loading
/// @param info
/// @return
MOD_EXPORT_FUNC void setup(CModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;

    Logger.info("Completed setup!");
}

/// @brief Called later on in the game loading - a good time to install function hooks
/// @return
MOD_EXPORT_FUNC void late_load() {
    il2cpp_functions::Init();

    Logger.info("Installing hooks...");

    INSTALL_HOOK(Logger, BeatmapLevelsModel_LoadAllBeatmapLevelPacks);

    Logger.info("Installed all hooks!");
}
#pragma endregion
