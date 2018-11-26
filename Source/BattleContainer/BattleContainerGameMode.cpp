// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BattleContainerGameMode.h"
#include "BattleContainerHUD.h"
#include "BattleContainerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABattleContainerGameMode::ABattleContainerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABattleContainerHUD::StaticClass();
}
