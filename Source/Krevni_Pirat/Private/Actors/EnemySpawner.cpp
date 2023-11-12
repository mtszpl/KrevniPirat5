// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "../../Public/Characters/Vampire.h"
#include "../../Public/GameModes/Krevni_PiratGameMode.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
}
void AEnemySpawner::SpawnEnemy()
{
	if (EnemyClass.Num() < 0)
		return;
	int32 Index = FMath::RandRange(0, EnemyClass.Num() - 1);
	GetWorld()->SpawnActor<AVampire>(EnemyClass[Index], SpawnPoint->GetComponentLocation(), FRotator::ZeroRotator);
}


// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	AKrevni_PiratGameMode* GM = Cast<AKrevni_PiratGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(GM))
		GM->RegisteSpawner(this);
}
