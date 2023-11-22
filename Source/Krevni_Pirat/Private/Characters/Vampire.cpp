// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Vampire.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AVampire::AVampire()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Vampire Mesh"));
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);
	Collider->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AVampire::BeginPlay()
{
	Super::BeginPlay();
	if(!IsValid(GetController()))
		SpawnDefaultController();
}

void AVampire::Attack()
{
	if (AttackMontages.IsEmpty())
		return;
	int32 Index = FMath::RandRange(0, AttackMontages.Num() - 1);
	Mesh->PlayAnimation(AttackMontages[Index], false);
}

void AVampire::GetHit(int32 damage)
{
	if (bIsDead)
		return;
	Hp -= damage;
	if (Hp <= 0)
		Die();
}

void AVampire::Die()
{
	GetController()->UnPossess();
	bIsDead = true;
	OnDeath.Broadcast();
	bBlockInput = true;
	SetLifeSpan(CorpseRemainTime);
}