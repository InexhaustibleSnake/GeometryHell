// Project made by Alexey Guchmazov (Inexhaustible Snake) for educational purposes

#include "Character/MainCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ReflectionComponent.h"
#include "Components/StaminaComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/HealthComponent.h"

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

	ReflectionComponent = CreateDefaultSubobject<UReflectionComponent>("ReflectionComponent");
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>("StaminaComponent");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->JumpZVelocity = 550.0f;
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
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, StaminaComponent, &UStaminaComponent::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, StaminaComponent, &UStaminaComponent::StopSprinting);

	PlayerInputComponent->BindAction("Reflection", IE_Pressed, ReflectionComponent, &UReflectionComponent::ReflectionOn);
	PlayerInputComponent->BindAction("Reflection", IE_Released, ReflectionComponent, &UReflectionComponent::ReflectionOff);

	PlayerInputComponent->BindAction("UltraReflection", IE_Pressed, ReflectionComponent, &UReflectionComponent::UltraReflectionOn);
	PlayerInputComponent->BindAction("UltraReflection", IE_Released, ReflectionComponent, &UReflectionComponent::UltraReflectionOff);

	PlayerInputComponent->BindAction("ShootMainProjectile", IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("ShootMainProjectile", IE_Released, WeaponComponent, &UWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("ShootSpecialProjectile", IE_Pressed, WeaponComponent, &UWeaponComponent::SpecialShot);

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