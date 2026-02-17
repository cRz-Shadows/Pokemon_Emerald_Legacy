# Pull Request: Fix Pomeg Berry not working on Shedinja

## Problem

Using a Pomeg Berry on Shedinja says "It won't have any effect" even when Shedinja has HP EVs (which it can have because it copies Ninjask's EVs upon creation). The berry should allow reducing HP EVs like it does for any other Pokemon.

## Root Cause

In `ItemEffectToMonEv()` (`src/party_menu.c`), there is an explicit check that returns 0 instead of the actual HP EV value when the Pokemon is Shedinja:

```c
case ITEM_EFFECT_HP_EV:
    if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_SHEDINJA)
        return GetMonData(mon, MON_DATA_HP_EV);
    break; // Falls through to return 0 for Shedinja
```

This function is called both before and after the berry is applied to compare EV values. Since it returns 0 for Shedinja in both cases, the comparison is always `0 == 0`, which triggers the "It won't have any effect" message.

This check was likely added because Shedinja's HP is always 1 regardless of EVs, so the developer assumed HP EVs were irrelevant. However, the Pomeg Berry's purpose is to reduce EVs (not HP directly), and players may want to reduce HP EVs to reallocate them to other stats via other EV berries or vitamins.

## Fix

Removed the Shedinja exclusion so `ItemEffectToMonEv()` returns the actual HP EV value for all species. Shedinja's HP will still always be 1 after stat recalculation (this is already handled by `CalculateMonStats()` in `pokemon.c`), but the EV itself is properly reduced.

## File Changed

- `src/party_menu.c` — `ItemEffectToMonEv()` (around line 4541)
