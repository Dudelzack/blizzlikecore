/*
 * BlizzLikeCore Copyright (C) 2012-2013  BlizzLikeGroup
 * Integrated Files: CREDITS.md and LICENSE.md
 */

#ifndef _ITEM_ENCHANTMENT_MGR_H
#define _ITEM_ENCHANTMENT_MGR_H

#include "Common.h"

void LoadRandomEnchantmentsTable();
uint32 GetItemEnchantMod(uint32 entry);
uint32 GenerateEnchSuffixFactor(uint32 item_id);
#endif

