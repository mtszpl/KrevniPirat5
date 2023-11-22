// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PirateController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Public/Characters/Krevni_PiratCharacter.h"
#include "../../Public/Huds/PirateHUD.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void APirateController::SetupInput()
{
	UEnhancedInputLocalPlayerSubsystem* Sys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Sys->ClearAllMappings();
	Sys->AddMappingContext(MappingContext, 0);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APirateController::Move);
		if (RotateAction)
			EnhancedInput->BindAction(RotateAction, ETriggerEvent::Triggered, this, &APirateController::Rotate);
		if (LookAction)
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APirateController::Look);
		if (DrawWeaponAction)
			EnhancedInput->BindAction(DrawWeaponAction, ETriggerEvent::Started, this, &APirateController::ToggleArmed);
		if (JumpAction)
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &APirateController::Jump);
		if (AttackAction)
			EnhancedInput->BindAction(AttackAction, ETriggerEvent::Started, this, &APirateController::Attack);
		if (AimAction)
		{
			EnhancedInput->BindAction(AimAction, ETriggerEvent::Started, this, &APirateController::StartAiming);
			EnhancedInput->BindAction(AimAction, ETriggerEvent::Canceled, this, &APirateController::StopAiming);
			EnhancedInput->BindAction(AimAction, ETriggerEvent::Completed, this, &APirateController::StopAiming);
		}

	}
}

#pragma region Movement

void APirateController::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	FVector InputValue = { Input.X, Input.Y, 0 };

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	GetCharacter()->AddMovementInput(Direction, InputValue.X);
	Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	GetCharacter()->AddMovementInput(Direction, InputValue.Y);
}

void APirateController::Look(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();
	AddPitchInput(Input * -MouseXSensitivity * GetWorld()->GetDeltaSeconds());
}

void APirateController::Rotate(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();
	AddYawInput(Input * MouseYSensitivity * GetWorld()->GetDeltaSeconds());
}

void APirateController::Jump()
{
	GetCharacter()->Jump();
	bIsJumping = true;
}

void APirateController::StartFalling()
{
	bIsJumping = false;
	bIsFalling = true;
}

void APirateController::OnCharacterFallDown(const FHitResult& Hit)
{
	bIsFalling = false;
	bIsJumping = false;
}

#pragma endregion

#pragma region Combat

void APirateController::Attack()
{
	AKrevni_PiratCharacter* Pirate = Cast< AKrevni_PiratCharacter>(GetCharacter());
	if (IsValid(Pirate))
	{
		Pirate->Attack();
	}
}

void APirateController::ToggleArmed()
{
	AKrevni_PiratCharacter* Pirate = Cast< AKrevni_PiratCharacter>(GetCharacter());
	if (IsValid(Pirate))
	{ 
		Pirate->ToggleArmed();
	}
}

void APirateController::StartAiming()
{
	AKrevni_PiratCharacter* Pirate = Cast< AKrevni_PiratCharacter>(GetCharacter());
	if (!Pirate->GetIsArmed())
		return;
	if (IsValid(Pirate))
	{
		Pirate->StartAiming();
	}
	if (IsValid(HUD))
	{
		HUD->StartAiming();
	}
}

void APirateController::StopAiming()
{
	AKrevni_PiratCharacter* Pirate = Cast< AKrevni_PiratCharacter>(GetCharacter());
	if (IsValid(Pirate))
	{
		Pirate->StopAiming();
	}
	if (IsValid(HUD))
	{
		HUD->StopAiming();
	}
}

#pragma endregion

void APirateController::BeginPlay()
{
	Super::BeginPlay();
	SetupInput();
	GetCharacter()->LandedDelegate.AddDynamic(this, &APirateController::OnCharacterFallDown);
	GetCharacter()->GetCharacterMovement()->bNotifyApex = true;
	GetCharacter()->OnReachedJumpApex.AddDynamic(this, &APirateController::StartFalling);
	HUD = GetHUD<APirateHUD>();
}

bool APirateController::GetIsJumping()
{
	return bIsJumping;
}

bool APirateController::GetIsFalling()
{
	return bIsFalling;
}
