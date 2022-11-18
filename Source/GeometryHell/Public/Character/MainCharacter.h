// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UReflectionComponent;
class UStaminaComponent;
class UWeaponComponent;

UCLASS()
class GEOMETRYHELL_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* GunMesh;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* ArmMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* MainCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UReflectionComponent* ReflectionComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaminaComponent* StaminaComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UWeaponComponent* WeaponComponent;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
};
