// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GeometryHellHUD.generated.h"

UCLASS()
class AGeometryHellHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGeometryHellHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

