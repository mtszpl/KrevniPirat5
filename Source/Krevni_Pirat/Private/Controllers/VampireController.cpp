// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/VampireController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/GameplayStatics.h"
#include "../../Public/Characters/Vampire.h"

void AVampireController::BeginPlay()
{
	Super::BeginPlay();
	Vamp = GetPawn<AVampire>();
	if(IsValid(VampBT))
	{
		RunBehaviorTree(VampBT);
		//VampBT->BlackboardAsset->Value
	}
}

void AVampireController::Attack()
{
	if (IsValid(Vamp))
		Vamp->Attack();
}
