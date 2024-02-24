// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AimGuide.generated.h"

UCLASS()
class CGAME_API AAimGuide : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAimGuide();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
