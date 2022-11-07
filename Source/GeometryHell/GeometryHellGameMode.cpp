// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeometryHellGameMode.h"
#include "GeometryHellHUD.h"
#include "GeometryHellCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGeometryHellGameMode::AGeometryHellGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGeometryHellHUD::StaticClass();
}
