ProfBirch_EventScript_UpdateLocation::
	@ If the Johto-starter quest needs Birch in the lab (state >= 4 = "all
	@ Hoenn mons caught, choose a Johto starter"), force him to the lab
	@ regardless of whether the Mossdeep Jirachi sidequest has been done.
	@ Mossdeep Birch is a separate object event with its own hide flag, so
	@ this does not affect the Jirachi quest.
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, ProfBirch_EventScript_MoveToLab
	goto_if_unset FLAG_HIDE_MOSSDEEP_CITY_BIRCH, Common_EventScript_NopReturn
	goto_if_eq VAR_PETALBURG_GYM_STATE, 0, Common_EventScript_NopReturn
	goto_if_set FLAG_SYS_GAME_CLEAR, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 0, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 1, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 2, ProfBirch_EventScript_MoveToRoute101
	call_if_eq VAR_BIRCH_STATE, 3, ProfBirch_EventScript_MoveToRoute101
	call_if_eq VAR_BIRCH_STATE, 4, ProfBirch_EventScript_MoveToRoute103
	call_if_eq VAR_BIRCH_STATE, 5, ProfBirch_EventScript_MoveToRoute103
	call_if_eq VAR_BIRCH_STATE, 6, ProfBirch_EventScript_MoveToLab
	call_if_eq VAR_BIRCH_STATE, 7, ProfBirch_EventScript_MoveToLab
	return

ProfBirch_EventScript_MoveToLab::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

ProfBirch_EventScript_MoveToRoute101::
	clearflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

ProfBirch_EventScript_MoveToRoute103::
	clearflag FLAG_HIDE_ROUTE_103_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	return

ProfBirch_EventScript_RatePokedexOrRegister::
	lock
	faceplayer
	goto_if_unset FLAG_HAS_MATCH_CALL, ProfBirch_EventScript_AskRatePokedex
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch

ProfBirch_EventScript_AskRatePokedex::
	msgbox gBirchDexRatingText_AreYouCurious, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ProfBirch_EventScript_DeclineRating
	call ProfBirch_EventScript_RatePokedex
	release
	end

ProfBirch_EventScript_DeclineRating::
	msgbox gBirchDexRatingText_Cancel, MSGBOX_DEFAULT
	release
	end

ProfBirch_EventScript_ShowRatingMessage::
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

ProfBirch_EventScript_RatePokedex::
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num Hoenn seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num Hoenn caught
	msgbox gBirchDexRatingText_SoYouveSeenAndCaught, MSGBOX_DEFAULT
	call ProfBirch_EventScript_ShowRatingMessage
	goto_if_eq VAR_0x800A, 0, Common_EventScript_NopReturn  @ National dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008  @ Num National seen
	buffernumberstring STR_VAR_2, VAR_0x8009  @ Num National caught
	msgbox gBirchDexRatingText_OnANationwideBasis, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasAllMons
	goto_if_eq VAR_RESULT, TRUE, ProfBirch_EventScript_CompletedNationalDex
	return

ProfBirch_EventScript_CompletedNationalDex::
	goto_if_set FLAG_RECEIVED_OLD_SEA_MAP, Common_EventScript_NopReturn
	msgbox gBirchDexRatingText_DexCompletedNationwide, MSGBOX_DEFAULT
	checkitemspace ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, FALSE, ProfBirch_EventScript_OldSeaMapBagFull
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	msgbox gBirchDexRatingText_JourneyNotOverYet, MSGBOX_DEFAULT
	releaseall
	return

ProfBirch_EventScript_OldSeaMapBagFull:
	vmessage ProfBirch_Text_OldSeaMapBagFull
	waitmessage
	waitbuttonpress
	releaseall
	return

gBirchDexRatingText_DexCompletedNationwide::
	.string "Well now, {PLAYER}{KUN},\n"
	.string "this is truly remarkable!\p"
	.string "You've completed the POKéDEX on a\n"
	.string "nationwide basis…\p"
	.string "I never thought I'd see this day!\n"
	.string "Your dedication is inspiring.\p"
	.string "Ah, that reminds me... There's something\n"
	.string "I've been holding onto.\l"
	.string "It's an OLD SEA MAP.\p"
	.string "I came across it years ago during one\n"
	.string "of my field expeditions, but I\l"
	.string "never quite knew what to make of it.\p"
	.string "It’s a curious thing, really. I was never\n"
	.string "quite sure of its origin.\p"
	.string "The map seems to point to a mysterious\n"
	.string "island...\p"
	.string "But when I tried to follow it, there was\n"
	.string "nothing there, just endless sea.\p"
	.string "I started to think it was just an old\n"
	.string "sailor's tall tale, and perhaps that's\l"
	.string "why I never pursued it further.\p"
	.string "But seeing your dedication and skill, I\n"
	.string "believe you might be the one to solve\l"
	.string "this mystery.\p"
	.string "Who knows, there could be something\n"
	.string "incredible hidden there.\p"
	.string "Take this OLD SEA MAP, {PLAYER}{KUN}.$"

ProfBirch_Text_OldSeaMapBagFull:
	.string "Oh, I'm sorry, {PLAYER}.\n"
	.string "Your BAG's KEY ITEMS POCKET is full.\p"
	.string "Please store something on your PC,\n"
	.string "then come back for this.$"

gBirchDexRatingText_JourneyNotOverYet:
	.string "Perhaps your journey isn't quite over\n"
	.string "just yet.$"
