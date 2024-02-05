// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(config=Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	// Top down camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	// Camera boom positioning the camera above the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	// default constructor
	ABaseCharacter();

	// default values for this character's properties
	int level;
	int maxHealth;
	int health;
	int damage;
	int superRechargeProgress;

	// Returns TopdownCameraComponent subobject 
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	// Returns CameraBoom subobject
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// testing
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called for forwards/backward input
	void MoveForward(float Value);

	// called for side to side input
	void MoveRight(float Value);

protected:
	// APawn inteface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	

	// setters for all the stats when spawned
	virtual void setCharacterStats();

};
