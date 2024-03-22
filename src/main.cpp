#pragma region Includes
#include "main.hpp"

// GlobalNamespace
#include "GlobalNamespace/BeatmapLevelsModel.hpp"
#include "GlobalNamespace/BeatmapLevelPack.hpp"
#include "GlobalNamespace/BeatmapLevelsEntitlementModel.hpp"
#include "GlobalNamespace/IBeatmapLevelLoader.hpp"
#include "GlobalNamespace/PackDefinitionSO.hpp"
#include "System/Collections/Generic/IEnumerable_1.hpp"
#include "System/Collections/Generic/IReadOnlyList_1.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "System/Linq/Enumerable.hpp"
#include <algorithm>

// UnitEngine
#include "UnityEngine/GameObject.hpp"
#pragma endregion

#pragma region Usings
using namespace GlobalNamespace;
using namespace System::Collections::Generic;
#pragma endregion

/// @brief Sorts packs with the OST packs first in their original order, followed by DLC sorted by name.
/// @param a The first pack to compare.
/// @param b The second pack to compare.
/// @return
bool dlc_comparer(BeatmapLevelPack* a, BeatmapLevelPack* b) {
    return std::string(a->___packName) < std::string(b->___packName);
}

#pragma region Hook definitions
// Hooks the MainMenuViewController to hide the musicPackPromoBanner object.
MAKE_HOOK_MATCH(BeatmapLevelsModel_CreateAllLoadedBeatmapLevelPacks, &BeatmapLevelsModel::CreateAllLoadedBeatmapLevelPacks, BeatmapLevelsRepository*, BeatmapLevelsModel* self) {
    Logger.debug("BeatmapLevelsModel_CreateAllLoadedBeatmapLevelPacks");

    // Create a list from the beatmapLevelPacks
    auto list = ListW<BeatmapLevelPack*>::New();
    list->AddRange(self->___dlcBeatmapLevelsRepository->____beatmapLevelPacks->i___System__Collections__Generic__IEnumerable_1_T_());

    // Convert the list to an array so we can sort it
    auto packs = list->ToArray();

    // Sort the packs
    std::stable_sort(packs->begin(), packs->end(), dlc_comparer);

    // Clear the list
    list->Clear();

    // Log the new order and add the items back into the list.
    for (auto pack : packs) {
        Logger.debug("{}", pack->___packName);
        list->Add(pack);
    }

    // Reverse the list because the game loads them in reverse order.
    list->Reverse();

    // Put our list back
    self->___dlcBeatmapLevelsRepository->____beatmapLevelPacks = static_cast<System::Collections::Generic::IReadOnlyList_1<BeatmapLevelPack*>*>(list.convert());

    // Call the original method
    return BeatmapLevelsModel_CreateAllLoadedBeatmapLevelPacks(self);
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

    INSTALL_HOOK(Logger, BeatmapLevelsModel_CreateAllLoadedBeatmapLevelPacks);

    Logger.info("Installed all hooks!");
}
#pragma endregion
