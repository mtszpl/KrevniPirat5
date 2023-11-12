// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bloodstore.generated.h"

class UBoxComponent;

UCLASS()
class KREVNI_PIRAT_API ABloodstore : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Collider;

	UFUNCTION()
	void OnHit();
	
public:	
	// Sets default values for this actor's properties
	ABloodstore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
