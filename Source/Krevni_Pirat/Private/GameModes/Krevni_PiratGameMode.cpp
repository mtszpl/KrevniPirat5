// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/Krevni_PiratGameMode.h"
#include "Characters/Krevni_PiratCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "../../Public/Actors/EnemySpawner.h"

AKrevni_PiratGameMode::AKrevni_PiratGameMode()
{
}

void AKrevni_PiratGameMode::RegisteSpawner(AEnemySpawner* Spawner)
{
	Spawners.Add(Spawner);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AKrevni_PiratGameMode::SpawnWave, 5, true);
}


void AKrevni_PiratGameMode::SpawnWave()
{
	for (AEnemySpawner* Spawner : Spawners)
		Spawner->SpawnEnemy();
}
