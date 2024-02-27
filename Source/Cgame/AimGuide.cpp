// Fill out your copyright notice in the Description page of Project Settings.

#include "AimGuide.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AAimGuide::AAimGuide()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating default components
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	BoxComponent->SetCollisionProfileName(TEXT("NoCollision"));
	BoxComponent->SetBoxExtent(FVector(20.f, 13.f, 1.f));
	BoxComponent->Mobility = EComponentMobility::Type::Movable; // Make the BoxComponent movable
	RootComponent = BoxComponent;

	// Definition for the Mesh that will serve as our visual representation.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/ThirdPerson/Meshes/Plane")); // In this case is the plane
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetEnableGravity(false);
	StaticMesh->SetupAttachment(RootComponent);

	// Set the Static Mesh and its position/scale if we successfully found a mesh asset to use.
	if (DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		StaticMesh->SetRelativeScale3D(FVector(0.4f, 0.26f, 1.0f));
	}
	
	UMaterial* mats = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("/Game/MapBuilder/Glass")));
	StaticMesh->SetMaterial(0, mats);

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

