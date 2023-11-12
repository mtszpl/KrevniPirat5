// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Bloodstore.h"
#include "Components/BoxComponent.h"

void ABloodstore::OnHit()
{
}

// Sets default values
ABloodstore::ABloodstore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));

	SetRootComponent(Root);
	Mesh->SetupAttachment(GetRootComponent());
	Collider->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ABloodstore::BeginPlay()
{
	Super::BeginPlay();	
}