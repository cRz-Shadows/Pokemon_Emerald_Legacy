# Pull Request: Fix Acro Bike Reverse Ledge Jump

## Problem

In the postgame, when the player has the upgraded acro bike with bunny-hop ledge jumping enabled (`FLAG_UNLOCKED_BIKE_SWITCHING`), performing a reverse bunny-hop over a ledge could land the player inside walls or on top of NPCs. This happened because the original code used a single combined condition that only checked whether the tile was a ledge, without verifying that the destination tile (one past the ledge) was actually passable.

The bug is reproducible in areas like Jagged Pass where ledges are adjacent to walls or NPCs.

## Fix

Split the `GetLedgeJumpDirection()` ledge jump condition into two separate checks:

1. **Normal ledge jumps** (player facing the same direction as the ledge orientation) continue to work exactly as before with no changes.
2. **Reverse bunny-hop jumps** (postgame feature) now call `GetCollisionAtCoords()` on the landing tile before allowing the jump. This function checks for:
   - Impassable wall tiles
   - NPCs occupying the tile
   - Elevation mismatches
   - Map border collisions

   The reverse jump is only allowed if the destination returns `COLLISION_NONE`.

Normal postgame ledge jumping still works in all valid directions — only jumps that would land the player in an invalid position are blocked.

## File Changed

- `src/event_object_movement.c` — `GetLedgeJumpDirection()` function (around line 7672)
