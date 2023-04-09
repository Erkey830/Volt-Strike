#ifndef GUARD_BATTLE_AI_SWITCH_ITEMS_H
#define GUARD_BATTLE_AI_SWITCH_ITEMS_H

enum
{
    AI_ITEM_FULL_RESTORE = 1,
    AI_ITEM_HEAL_HP,
    AI_ITEM_CURE_CONDITION,
    AI_ITEM_X_STAT,
    AI_ITEM_GUARD_SPEC,
    AI_ITEM_NOT_RECOGNIZABLE
};

enum {
    AI_HEAL_CONFUSION,
    AI_HEAL_PARALYSIS,
    AI_HEAL_FREEZE,
    AI_HEAL_BURN,
    AI_HEAL_POISON,
    AI_HEAL_SLEEP,
};

enum {
    AI_X_ATTACK,
    AI_X_DEFEND,
    AI_X_SPEED,
    AI_X_SPATK,
    AI_X_SPDEF, // Unused
    AI_X_ACCURACY,
    AI_X_EVASION, // Unused
    AI_DIRE_HIT,
};

void GetAIPartyIndexes(u32 battlerId, s32 *firstId, s32 *lastId);
void AI_TrySwitchOrUseItem(void);
u8 GetMostSuitableMonToSwitchInto(void);
bool32 ShouldSwitch(void);

#endif // GUARD_BATTLE_AI_SWITCH_ITEMS_H