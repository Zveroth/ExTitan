// Fill out your copyright notice in the Description page of Project Settings.
#include "Player/PlayerPawnBase.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"



// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetProjectionMode(ECameraProjectionMode::Perspective);
	Camera->SetFieldOfView(75.0f);
}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!ensure(IsValid(EnhancedInput)))
	{
		return;
	}
	
	EnhancedInput->BindAction(InteractionInputAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerPawnBase::InteractCallback);
}

void APlayerPawnBase::InteractCallback(const FInputActionInstance& Action)
{
	UE_LOG(LogTemp, Warning, TEXT("A"));
}