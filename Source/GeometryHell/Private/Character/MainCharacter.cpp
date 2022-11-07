#include "Character/MainCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(GetRootComponent());

	ArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ArmMesh");
	ArmMesh->SetupAttachment(MainCamera);
	ArmMesh->CastShadow = false;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunMesh");
	GunMesh->SetupAttachment(ArmMesh);
	GunMesh->CastShadow = false;
	GunMesh->AttachTo(ArmMesh, "GripPoint");
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseX", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &AMainCharacter::AddControllerPitchInput);
}

void AMainCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AMainCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}