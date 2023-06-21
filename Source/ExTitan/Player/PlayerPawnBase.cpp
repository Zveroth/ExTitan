// Fill out your copyright notice in the Description page of Project Settings.
#include "Player/PlayerPawnBase.h"
#include "Camera/CameraComponent.h"
#include "Interaction/Interactable.h"
#include "Interaction/InteractionsManagerComponent.h"

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
	APlayerController* PlayerController = GetController<APlayerController>();
	check(IsValid(PlayerController));

	FHitResult HitResult;

	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, HitResult);

	AActor* const HitActor = HitResult.GetActor();
	if (!IsValid(HitActor))
	{
		return;
	}

	IInteractable* const Interactable = Cast<IInteractable>(HitActor);
	if (!Interactable)
	{
		return;
	}

	UInteractionsManagerComponent* InteractionsManager = Interactable->GetInteractionsManager();

	InteractionsManager->OnClicked();
}