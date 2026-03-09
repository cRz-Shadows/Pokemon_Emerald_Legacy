.set LOCALID_NURSE, 1
.set LOCALID_GUARD_1, 3
.set LOCALID_GUARD_2, 4

EverGrandeCity_PokemonLeague_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_PokemonLeague_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

EverGrandeCity_PokemonLeague_1F_OnTransition:
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	call_if_unset FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_GUARD_1, 9, 2
	setobjectxyperm LOCALID_GUARD_2, 10, 2
	return

EverGrandeCity_PokemonLeague_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Clerk::
	call_if_unset FLAG_SYS_GAME_CLEAR, EverGrandeCity_PokemonLeague_1F_EventScript_Clerk_MainGame
	call_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_PokemonLeague_1F_EventScript_Clerk_PostGame
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Clerk_MainGame::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart EverGrandeCity_PokemonLeague_1F_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Clerk_PostGame::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart EverGrandeCity_PokemonLeague_1F_Pokemart_PostGame
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
EverGrandeCity_PokemonLeague_1F_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_TM_SHADOW_BALL
	.2byte ITEM_TM_IRON_TAIL
	.2byte ITEM_TM_SLUDGE_BOMB
	.2byte ITEM_TM_SANDSTORM
	.2byte ITEM_TM_RAIN_DANCE
	.2byte ITEM_TM_SUNNY_DAY
	.2byte ITEM_TM_HAIL
	.2byte ITEM_TM_FRUSTRATION
	.2byte ITEM_TM_RETURN
	.2byte ITEM_NONE
	release
	end

	.align 2
EverGrandeCity_PokemonLeague_1F_Pokemart_PostGame:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_TM_SHADOW_BALL
	.2byte ITEM_TM_IRON_TAIL
	.2byte ITEM_TM_SLUDGE_BOMB
	.2byte ITEM_TM_SANDSTORM
	.2byte ITEM_TM_RAIN_DANCE
	.2byte ITEM_TM_SUNNY_DAY
	.2byte ITEM_TM_HAIL
	.2byte ITEM_TM_FRUSTRATION
	.2byte ITEM_TM_RETURN
	.2byte ITEM_BLACK_GLASSES
	.2byte ITEM_SPELL_TAG
	.2byte ITEM_NONE
	release
	end

@ The door guards only check for FLAG_BADGE06_GET because Winonas badge is the only one that can be skipped
@ Its assumed the player has the remaining badges
EverGrandeCity_PokemonLeague_1F_EventScript_DoorGuard::
	lockall
	goto_if_set FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 11, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 8, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft
	message EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges
	waitmessage
	delay 120
	goto_if_unset FLAG_BADGE06_GET, EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges
	closemessage
	applymovement LOCALID_GUARD_1, EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay
	applymovement LOCALID_GUARD_2, EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	playfanfare MUS_OBTAIN_BADGE
	message EverGrandeCity_PokemonLeague_1F_Text_GoForth
	waitmessage
	waitfanfare
	closemessage
	copyobjectxytoperm LOCALID_GUARD_1
	copyobjectxytoperm LOCALID_GUARD_2
	setflag FLAG_ENTERED_ELITE_FOUR
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft::
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaL::
	goto_if_set FLAG_IS_CHAMPION, EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaEnd
	goto_if_unset FLAG_HARD, EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaEnd
	call EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquaza
	applymovement LOCALID_GUARD_1, Common_Movement_FacePlayer
	waitmovement 0
	goto EverGrandeCity_PokemonLeague_1F_EventScript_CantBringRayquaza

EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaR::
	goto_if_set FLAG_IS_CHAMPION, EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaEnd
	goto_if_unset FLAG_HARD, EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaEnd
	call EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquaza
	applymovement LOCALID_GUARD_2, Common_Movement_FacePlayer
	waitmovement 0
	goto EverGrandeCity_PokemonLeague_1F_EventScript_CantBringRayquaza

EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquaza::
	goto_if_set FLAG_IS_CHAMPION, EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaEnd
	setvar 0x8005, SPECIES_RAYQUAZA
	special CheckSpecies
	goto_if_eq VAR_RESULT, FALSE, EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaEnd
	return

EverGrandeCity_PokemonLeague_1F_EventScript_CantBringRayquaza::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_CantBringLegendaries, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MovePlayerBack
	waitmovement 0
EverGrandeCity_PokemonLeague_1F_EventScript_CheckRayquazaEnd::
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MovePlayerBack:
	walk_down
	step_end

EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges:
	.string "Beyond this point, only those TRAINERS\n"
	.string "who have collected all the GYM BADGES\l"
	.string "are permitted to enter.\p"
	.string "TRAINER, let us confirm that you have\n"
	.string "all the GYM BADGES.$"

EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges:
	.string "You haven't obtained all the BADGES.\p"
	.string "If you're bound for the POKéMON\n"
	.string "LEAGUE, you must return with them.$"

EverGrandeCity_PokemonLeague_1F_Text_CantBringLegendaries:
	.string "Only POKéMON of extraordinary spirit\n"
	.string "may enter the LEAGUE's ranks.\p"
	.string "LEGENDARY POKéMON are not allowed.\n"
	.string "Please return with a different team.$"

EverGrandeCity_PokemonLeague_1F_Text_GoForth:
	.string "TRAINER! Believe in yourself and your\n"
	.string "POKéMON, and go forth!$"
