# Pull Request: Fix Sky Attack failing on last PP

## Problem

Sky Attack fails when used on its last PP. With 5 PP (no PP Ups), the first 4 uses work correctly, but the 5th use consumes the final PP and then displays "There's no PP left for this move!" without actually executing. With PP Ups bringing it to 8 PP, the 8th use fails in the same way.

## Root Cause

Sky Attack was changed from a two-turn charging move to a one-turn move (the charge turn logic in `BattleScript_EffectSkyAttack` was commented out). However, the script was not updated to use the standard one-turn hit path. Instead it still routes through `BattleScript_TwoTurnMovesSecondTurn`, causing a conflict:

1. `ppreduce` runs first, deducting PP (e.g. 1 → 0 on last use)
2. The script jumps to `BattleScript_TwoTurnMovesSecondTurn`
3. `attackcanceler` runs and checks: if PP == 0 AND `STATUS2_MULTIPLETURNS` is not set, reject the move
4. Since Sky Attack is no longer a proper two-turn sequence, `STATUS2_MULTIPLETURNS` is never set from a prior charge turn
5. With PP at 0, the check fails and the move is rejected — even though PP was already consumed

The PP == 0 check in `attackcanceler` is designed to allow two-turn moves to complete their second turn even at 0 PP (via the `STATUS2_MULTIPLETURNS` exemption). But since Sky Attack no longer has a first charge turn to set that status, the exemption never applies.

## Fix

Replaced the broken script routing with the standard one-turn hit path. Since Sky Attack already has `secondaryEffectChance: 30` in its move data, setting `MOVE_EFFECT_FLINCH` and going through `BattleScript_EffectHit` gives the correct behavior: a normal one-turn attack with a 30% flinch chance, with PP handled correctly (deducted after the canceler check, not before).

**Before:**
```asm
BattleScript_EffectSkyAttack::
    ppreduce
    goto BattleScript_TwoTurnMovesSecondTurn
```

**After:**
```asm
BattleScript_EffectSkyAttack::
    setmoveeffect MOVE_EFFECT_FLINCH
    goto BattleScript_EffectHit
```

## File Changed

- `data/battle_scripts_1.s` — `BattleScript_EffectSkyAttack` (around line 1110)
