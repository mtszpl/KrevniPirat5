// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Sword.h"
#include "Components/BoxComponent.h"
#include "../../Public/Characters/Vampire.h"

void ASword::OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsUsed || !bIsDrawn)
		return;
	AVampire* Vampire = Cast<AVampire>(OtherActor);
	if (!IsValid(Vampire))
		return;
	Vampire->GetHit(damage);

}

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Mesh);
	Collider->SetupAttachment(Mesh);
}

void ASword::SetIsDrawn(bool isDrawn)
{
	bIsDrawn = isDrawn;
}

void ASword::SetIsUsed(bool isUsed)
{
	bIsUsed = isUsed;
}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(Collider))
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ASword::OnSwordOverlap);
	
}