// Copyright Epic Games, Inc. All Rights Reserved.

#include "CgameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ACgameCharacter

ACgameCharacter::ACgameCharacter()
{
	// Create An Actor Character
	GetCapsuleComponent()->InitCapsuleSize(12.f, 12.0f);// Set size for collision capsule

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->MaxWalkSpeed = 100.f; // set the character max movement speed

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent()); 
	CameraBoom->TargetArmLength = 200.0f; // The	camera follows at this distance behind the character	
	CameraBoom->bDoCollisionTest = false; // Dont want to pull the camera in when collides with an object

	// Making the camera stays fixed
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACgameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACgameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACgameCharacter::MoveRight);

	//// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	//// "turn" handles devices that provide an absolute delta, such as a mouse.
	//// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	
	// NOTE* we'll be using these as a reference to aiming
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &ACgameCharacter::TurnAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACgameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACgameCharacter::TouchStopped);

}

void ACgameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ACgameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ACgameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACgameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACgameCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACgameCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
