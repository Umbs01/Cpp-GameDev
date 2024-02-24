// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "AimGuide.h"

// Sets default values
AAimGuide::AAimGuide()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating default components
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComp->SetBoxExtent(FVector(20.f, 20.f, 1.f));

}

// Called when the game starts or when spawned
void AAimGuide::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAimGuide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

