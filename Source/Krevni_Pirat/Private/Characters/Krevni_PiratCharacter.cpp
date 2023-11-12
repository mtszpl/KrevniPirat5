// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Krevni_PiratCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Public/Actors/Sword.h"
#include "../../Public/Actors/Gun.h"

//////////////////////////////////////////////////////////////////////////
// AKrevni_PiratCharacter

void AKrevni_PiratCharacter::SwordGrab()
{
	GetWorld()->GetTimerManager().ClearTimer(SwordMoveHandle);
	Sword->AttachToComponent(SwordHand, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::SnapToTarget, false));
	Sword->SetIsDrawn(true);
	if (IsValid(SheathSwordMontage))
		SwordAnimTime = SheathSwordMontage->GetPlayLength() * SheathSwordMontage->RateScale;
	else
		SwordAnimTime = 0;
}

void AKrevni_PiratCharacter::SwordLeave()
{
	GetWorld()->GetTimerManager().ClearTimer(SwordMoveHandle);
	Sword->AttachToComponent(SwordAttach, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false));
	Sword->SetIsDrawn(false);
	if (IsValid(DrawSwordMontage))
		SwordAnimTime = DrawSwordMontage->GetPlayLength() * DrawSwordMontage->RateScale;
	else
		SwordAnimTime = 0;
}

void AKrevni_PiratCharacter::GunGrab()
{
	GetWorld()->GetTimerManager().ClearTimer(GunMoveHandle);
	Gun->AttachToComponent(GunHand, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false));
	if (IsValid(SheathGunMontage))
		GunAnimTime = SheathGunMontage->GetPlayLength();
	else
		GunAnimTime = 0;
}

void AKrevni_PiratCharacter::GunLeave()
{
	GetWorld()->GetTimerManager().ClearTimer(GunMoveHandle);
	Gun->AttachToComponent(GunAttach, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false));
	if (IsValid(DrawGunMontage))
		GunAnimTime = DrawGunMontage->GetPlayLength();
	else
		GunAnimTime = 0;
}

void AKrevni_PiratCharacter::AfterSwordAttack()
{
	bIsAttacking = false;
	Sword->SetIsUsed(false);
	GetWorld()->GetTimerManager().ClearTimer(AttackHandle);
}

void AKrevni_PiratCharacter::AfterGunFire()
{
	bIsAttacking = false;
	GetWorld()->GetTimerManager().ClearTimer(AttackHandle);
}

AKrevni_PiratCharacter::AKrevni_PiratCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SwordAttach = CreateDefaultSubobject<USceneComponent>(TEXT("SwordAttach"));
	GunAttach = CreateDefaultSubobject<USceneComponent>(TEXT("GunAttach"));
	SwordHand = CreateDefaultSubobject<USceneComponent>(TEXT("SwordHand"));
	GunHand = CreateDefaultSubobject<USceneComponent>(TEXT("GunHand"));

	SwordAttach->SetupAttachment(GetMesh());
	SwordHand->SetupAttachment(GetMesh());
	GunAttach->SetupAttachment(GetMesh());
	GunHand->SetupAttachment(GetMesh());
}

void AKrevni_PiratCharacter::ToggleArmed()
{
	if (!bIsArmed)
	{
		PlayAnimMontage(DrawSwordMontage);
		GetWorld()->GetTimerManager().SetTimer(SwordMoveHandle, this, &AKrevni_PiratCharacter::SwordGrab, SwordAnimTime / 2, false);
	}
	else
	{
		PlayAnimMontage(SheathSwordMontage);
		GetWorld()->GetTimerManager().SetTimer(SwordMoveHandle, this, &AKrevni_PiratCharacter::SwordLeave, SwordAnimTime / 2, false);
	}
	bIsArmed = !bIsArmed;
}

void AKrevni_PiratCharacter::StartAiming()
{
	if (!bIsArmed)
		return;
	if (IsValid(DrawGunMontage))
	{
		PlayAnimMontage(DrawGunMontage);
		GetWorld()->GetTimerManager().SetTimer(GunMoveHandle, this, &AKrevni_PiratCharacter::GunGrab, GunAnimTime / 2, false);
	}
	CameraBoom->SetRelativeLocation(CameraAimingOffset);
	GetCharacterMovement()->MaxWalkSpeed = 300;
	bIsAiming = true;
}

void AKrevni_PiratCharacter::StopAiming()
{
	if (!bIsArmed)
		return;
	if (IsValid(SheathGunMontage))
	{
		PlayAnimMontage(SheathGunMontage);
		GetWorld()->GetTimerManager().SetTimer(GunMoveHandle, this, &AKrevni_PiratCharacter::GunLeave , GunAnimTime / 2, false);
	}
	CameraBoom->SetRelativeLocation({0, 0, 0});
	GetCharacterMovement()->MaxWalkSpeed = 1200;
	bIsAiming = false;
}

void AKrevni_PiratCharacter::Attack()
{
	if (!bIsArmed || bIsAttacking)
		return;
	bIsAttacking = true;
	if(bIsAiming)
	{ 
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, "Attack");
		if (IsValid(GunFireMontage))
			PlayAnimMontage(GunFireMontage);
		float lastingTime = GunFireMontage->GetPlayLength() / GunFireMontage->RateScale;
		GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &ThisClass::AfterGunFire, lastingTime, false);
		PlayAnimMontage(GunFireMontage);
		if (IsValid(Gun))
			Gun->Fire(FollowCamera);
	}
	else
	{
		if (SwordAttackMontage.Num() < 1)
			return;
		int32 animIndex = FMath::RandRange(0, SwordAttackMontage.Num() - 1);
		float lastingTime = SwordAttackMontage[animIndex]->GetPlayLength() / SwordAttackMontage[animIndex]->RateScale;
		GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &ThisClass::AfterSwordAttack, lastingTime, false);
		Sword->SetIsUsed(true);
		PlayAnimMontage(SwordAttackMontage[animIndex]);
	}
}

bool AKrevni_PiratCharacter::GetIsArmed()
{
	return bIsArmed;
}

bool AKrevni_PiratCharacter::GetIsAiming()
{
	return bIsAiming;
}

void AKrevni_PiratCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(DrawSwordMontage))
		SwordAnimTime = DrawSwordMontage->GetPlayLength() * DrawSwordMontage->RateScale;
	if (IsValid(DrawGunMontage))
		GunAnimTime = DrawGunMontage->GetPlayLength() * DrawGunMontage->RateScale;

	SwordAttach->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false),
		FName("Pelvis"));
	GunAttach->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false),
		FName("Pelvis"));
	SwordHand->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::SnapToTarget, false),
		FName("hand_r"));
	GunHand->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, EAttachmentRule::SnapToTarget, false),
		FName("hand_l"));
	Sword = GetWorld()->SpawnActor<ASword>(SwordClass, SwordAttach->GetComponentLocation(), FRotator::ZeroRotator);
	Gun = GetWorld()->SpawnActor<AGun>(GunClass, GunAttach->GetComponentLocation(), FRotator::ZeroRotator);
	Gun->AttachToComponent(GunAttach, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false));
	Sword->AttachToComponent(SwordAttach, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false));
}

void AKrevni_PiratCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AKrevni_PiratCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}