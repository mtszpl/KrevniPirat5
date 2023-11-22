// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/VampireAnim.h"
//#include "KismetAnimationLibrary.h"
#include "../../Public/Characters/Vampire.h"
#include "../../Public/Controllers/VampireController.h"

void UVampireAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Vamp = Cast<AVampire>(TryGetPawnOwner());
	Controller = Cast<AVampireController>(TryGetPawnOwner()->GetController());
	if (IsValid(Vamp))
		Vamp->OnDeath.AddUObject(this, &ThisClass::Die);
}

void UVampireAnim::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);
	if (IsValid(Vamp))
	{
		Speed = Vamp->GetVelocity().Length();
		Direction = CalculateDirection(Vamp->GetVelocity(), Vamp->GetControlRotation());
	}
}

void UVampireAnim::Die()
{
	bIsDead = true;
}
