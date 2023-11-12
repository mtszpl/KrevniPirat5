// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PirateAnim.h"
#include "../../Public/Characters/Krevni_PiratCharacter.h"
#include "../../Public/Controllers/PirateController.h"

void UPirateAnim::NativeBeginPlay()
{
	Pirat = Cast<AKrevni_PiratCharacter>(TryGetPawnOwner());
	Controller = Cast<APirateController>(TryGetPawnOwner()->GetController());
}

void UPirateAnim::NativeUpdateAnimation(float deltaSeconds)
{
	if (IsValid(Pirat))
	{
		bIsAiming = Pirat->GetIsAiming();
		bIsArmed = Pirat->GetIsArmed();
		Direction = CalculateDirection(Pirat->GetVelocity(), Pirat->GetControlRotation());
		Speed = Pirat->GetVelocity().Size();
		FRotator aim = Pirat->GetBaseAimRotation();
		FRotator rot = Pirat->GetActorRotation();
		Yaw = aim.Yaw - rot.Yaw;
		Pitch = aim.Pitch - rot.Pitch;
		FVector vec = Pirat->GetVelocity().RotateAngleAxis(Yaw, {0, 0, 1});
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, FString::SanitizeFloat(Direction));
	}
	if (IsValid(Controller))
	{
		bIsJumping = Controller->GetIsJumping();
		bIsFalling = Controller->GetIsFalling();
	}
}