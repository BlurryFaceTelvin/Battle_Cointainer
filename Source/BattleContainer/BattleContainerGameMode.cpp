// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BattleContainerGameMode.h"
#include "BattleContainerHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABattleContainerGameMode::ABattleContainerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Player/Behavior/FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/NPC/Behavior/PatrollingGuard"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABattleContainerHUD::StaticClass();
}
