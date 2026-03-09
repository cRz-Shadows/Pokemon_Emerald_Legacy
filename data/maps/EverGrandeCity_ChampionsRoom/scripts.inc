.set LOCALID_WALLACE, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3
.set LOCALID_STEVEN, 4

EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call_if_unset FLAG_IS_CHAMPION, EverGrandeCity_ChampionsRoom_EventScript_SetStevenLayout
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_SetStevenLayout::	
	setmaplayoutindex LAYOUT_EVER_GRANDE_CITY_CHAMPIONS_ROOM_STEVEN
	return	

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto_if_unset FLAG_IS_CHAMPION, EverGrandeCity_ChampionsRoom_EventScript_Steven
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Steven::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenIntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN_1, EverGrandeCity_ChampionsRoom_Text_StevenDefeat
	goto EverGrandeCity_ChampionsRoom_EventScript_StevenDefeated
	end

EverGrandeCity_ChampionsRoom_EventScript_StevenDefeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenPostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	goto_if_unset FLAG_IS_CHAMPION, EverGrandeCity_ChampionsRoom_EventScript_StevenGoToHOF
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceGoToHOF
	
EverGrandeCity_ChampionsRoom_EventScript_StevenGoToHOF::
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_STEVEN, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_STEVEN, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE_2, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceDefeated
	end

EverGrandeCity_ChampionsRoom_EventScript_WallaceDefeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_RematchMayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_RematchBrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_RematchMayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchMayAdvice, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_RematchBirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_RematchBrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchBrendanAdvice, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_RematchBirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_RematchBirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchBirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchBirchCongratulations, MSGBOX_DEFAULT
	closemessage
	goto_if_unset FLAG_IS_CHAMPION, EverGrandeCity_ChampionsRoom_EventScript_StevenGoToHOF
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceGoToHOF

EverGrandeCity_ChampionsRoom_EventScript_WallaceGoToHOF::
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchWallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_RematchMayCantGoIn
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_RematchBrendanCantGoIn
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchWallaceChampion, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_RematchMayCantGoIn::
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchMayCantGoIn, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RematchBrendanCantGoIn::
	msgbox EverGrandeCity_ChampionsRoom_Text_RematchBrendanCantGoIn, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_StevenIntroSpeech:
	.string "STEVEN: Welcome, {PLAYER}{KUN}.\p"
	.string "I was looking forward to seeing you\n"
	.string "here one day.\p"
	.string "You… What did you see on your\n"
	.string "journey with POKéMON?\p"
	.string "What did you feel, meeting so many\n"
	.string "other TRAINERS like you?\p"
	.string "What has awoken in you?\n"
	.string "I want you to hit me with it all!\p"
	.string "Now, bring it!$"

EverGrandeCity_ChampionsRoom_Text_StevenDefeat:
	.string "I, the CHAMPION, fall in defeat…\p"
	.string "Kudos to you, {PLAYER}{KUN}!\p"
	.string "You are a truly noble POKéMON\n"
	.string "TRAINER!$"

EverGrandeCity_ChampionsRoom_Text_StevenPostBattleSpeech:
	.string "STEVEN: Congratulations!\p"
	.string "The feelings you have for your\n"
	.string "POKéMON…\p"
	.string "And the POKéMON that responded to\n"
	.string "those feelings with all their might…\p"
	.string "They came together as one, and created\n"
	.string "an even greater power.\p"
	.string "And thus, you were able to grasp\n"
	.string "victory today!\p"
	.string "You are rightfully the HOENN region's\n"
	.string "new…$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
	.string "MAY: {PLAYER}{KUN}!\p"
	.string "Here's some advice before you challenge\n"
	.string "the CHAMPION…$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
	.string "MAY: Huh?\n"
	.string "What, what, what?\p"
	.string "{PLAYER}{KUN}…\n"
	.string "Could it be that…\l"
	.string "It's already over?$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
	.string "BRENDAN: {PLAYER}!\p"
	.string "How would you like some advice before\n"
	.string "you challenge the CHAMPION?…$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
	.string "BRENDAN: {PLAYER}…\p"
	.string "Are you trying to tell me…\n"
	.string "You've beaten the CHAMPION?$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
	.string "PROF. BIRCH: See?\n"
	.string "What did I tell you, {RIVAL}?\p"
	.string "Didn't I tell you that you don't need\n"
	.string "to worry about {PLAYER}{KUN}?\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}, you've finally done it.\p"
	.string "When I heard that you defeated your\n"
	.string "own father at the PETALBURG GYM,\l"
	.string "I thought perhaps you had a chance…\p"
	.string "But to think you've actually become\n"
	.string "the CHAMPION!\p"
	.string "Ah, yes!\p"
	.string "What became of your POKéDEX?\n"
	.string "Here, let me see.$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
	.string "PROF. BIRCH: Anyways,\n"
	.string "congratulations!\p"
	.string "Now, go proudly into the final room!$"

EverGrandeCity_ChampionsRoom_Text_StevenComeWithMe:
	.string "STEVEN: {PLAYER}{KUN}…\p"
	.string "No, the new CHAMPION!\p"
	.string "Come with me.$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
	.string "WALLACE: I'm sorry, but…\p"
	.string "From here on, only those TRAINERS who\n"
	.string "have become CHAMPIONS may enter.\p"
	.string "You'll have to wait outside with\n"
	.string "PROF. BIRCH.$"

EverGrandeCity_ChampionsRoom_Text_StevenWaitOutside:
	.string "STEVEN: I'm sorry, but…\p"
	.string "From here on, only those TRAINERS who\n"
	.string "have become CHAMPIONS may enter.\p"
	.string "You'll have to wait outside with the\n"
	.string "PROFESSOR.$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
	.string "MAY: Groan…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "I'm just joking! That's okay!\n"
	.string "That's the rule!\p"
	.string "{PLAYER}{KUN}!\n"
	.string "Honestly, congratulations!$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
	.string "BRENDAN: Whaaaat?! … … … … …\n"
	.string "… … … … … … … …\p"
	.string "It can't be helped if that's the rule.\p"
	.string "{PLAYER}, way to go!\n"
	.string "Congratulations!$"

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
	.string "WALLACE: Welcome, {PLAYER}{KUN}.\p"
	.string "Our paths cross again…\n"
	.string "but this time, I am the challenger.\p"
	.string "I watched as you brought peace to\n"
	.string "SOOTOPOLIS CITY… A remarkable feat,\l"
	.string "achieved with your POKéMON by your\l"
	.string "side.\p"
	.string "We TRAINERS raise POKéMON by giving\n"
	.string "them items and by teaching them new\l"
	.string "techniques for battle.\p"
	.string "But we ourselves also learn many\n"
	.string "things from POKéMON.\p"
	.string "You've shown the strength of a true\n"
	.string "CHAMPION, {PLAYER}{KUN}.\p"
	.string "But now, your achievements must be\n"
	.string "put to the ultimate test.\p"
	.string "Now! Who can most elegantly dance with\n"
	.string "their POKéMON in HOENN?\p"
	.string "Show me right here and now!$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
	.string "I, the challenger, fall in defeat…\n"
	.string "That was wonderful work.\l"
	.string "Kudos to you, {PLAYER}{KUN}!$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
	.string "WALLACE: The POKéMON you sent into\n"
	.string "battle…\p"
	.string "At times they danced like a spring\n"
	.string "breeze, and at times they struck\l"
	.string "like lightning.\p"
	.string "It was with light, yet surefooted,\n"
	.string "elegance that you led your POKéMON.\p"
	.string "Even I felt bedazzled by your\n"
	.string "masterful performance!\p"
	.string "You remain at the glorious peak\n"
	.string "of the POKéMON LEAGUE, {PLAYER}{KUN}.\p"
	.string "Congratulations… HOENN's CHAMPION.$"

EverGrandeCity_ChampionsRoom_Text_RematchMayAdvice:
	.string "MAY: {PLAYER}{KUN}!\p"
	.string "Wow! You did it!\n"
	.string "No advice this time… just congrats!\p"
	.string "Taking on WALLACE and winning…\n"
	.string "That's amazing!$"

EverGrandeCity_ChampionsRoom_Text_RematchBrendanAdvice:
	.string "BRENDAN: {PLAYER}{KUN}!\p"
	.string "Wow! You did it!\n"
	.string "No advice this time… just congrats!\p"
	.string "Taking on WALLACE and winning…\n"
	.string "That's amazing!$"

EverGrandeCity_ChampionsRoom_Text_RematchBirchArriveRatePokedex:
	.string "PROF. BIRCH: Well, {RIVAL}, looks like\n"
	.string "I was right about {PLAYER}{KUN}!\p"
	.string "I had no doubt you could defend your\n"
	.string "title, and here you are… still CHAMPION!\p"
	.string "It's amazing to see how far you've come.\n"
	.string "I knew you had talent, but this…\p"
	.string "{PLAYER}{KUN}, you've truly made history.\p"
	.string "Ah, yes! Your POKéDEX…\n"
	.string "Mind if I take a look at it? I'm eager\l"
	.string "to see the progress you've made.$"

EverGrandeCity_ChampionsRoom_Text_RematchBirchCongratulations:
	.string "PROF. BIRCH: Anyways,\n"
	.string "congratulations once more!\p"
	.string "Now, go proudly again into the\n"
	.string "final room!$"

EverGrandeCity_ChampionsRoom_Text_RematchWallaceComeWithMe:
	.string "WALLACE: {PLAYER}{KUN},\n"
	.string "you've proven yourself once again.\p"
	.string "Let's not waste any time.\n"
	.string "CHAMPION, follow me…\p"
	.string "It's time we head to the HALL OF FAME\n"
	.string "to record this latest triumph.$"

EverGrandeCity_ChampionsRoom_Text_RematchMayCantGoIn:
	.string "MAY: Hey, wait a second!\n"
	.string "WALLACE, you're not the CHAMPION.\p"
	.string "You shouldn't be going in!$"

EverGrandeCity_ChampionsRoom_Text_RematchBrendanCantGoIn:
	.string "BRENDAN: Hey, wait a second!\n"
	.string "WALLACE, you're not the CHAMPION.\p"
	.string "You shouldn't be going in!$"

EverGrandeCity_ChampionsRoom_Text_RematchWallaceChampion::
	.string "WALLACE: Ah, {RIVAL},\n"
	.string "You see, I was CHAMPION long ago,\l"
	.string "trading the title back and forth\l"
	.string "with STEVEN in a friendly rivalry.\p"
	.string "We each held the title many times,\n"
	.string "constantly pushing each other to\l"
	.string "improve.\p"
	.string "But today… today belongs to\n"
	.string "{PLAYER}{KUN}.\p"
	.string "Come, CHAMPION. Let us mark this moment\n"
	.string "in the HALL OF FAME!$"
