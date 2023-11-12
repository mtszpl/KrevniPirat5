// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Krevni_PiratGameMode.generated.h"

class AEnemySpawner;

UCLASS(minimalapi)
class AKrevni_PiratGameMode : public AGameModeBase
{
	GENERATED_BODY()

	FTimerHandle SpawnTimer;

	UPROPERTY()
		TArray<AEnemySpawner*> Spawners;

public:
	AKrevni_PiratGameMode();

	void RegisteSpawner(AEnemySpawner* Spawner);

	void SpawnWave();
};



