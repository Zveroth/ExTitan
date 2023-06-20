// Fill out your copyright notice in the Description page of Project Settings.
#include "Misc/ExerciseGamemode.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"



void AExerciseGamemode::BeginPlay()
{
	Super::BeginPlay();

	SetupInputContexts();
}

void AExerciseGamemode::SetupInputContexts()
{
	if (DefaultMappingContext.IsNull())
	{
		return;
	}

	UWorld* const World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	ULocalPlayer* const LocalPlayer = Cast<ULocalPlayer>(World->GetFirstLocalPlayerFromController());
	if (!IsValid(LocalPlayer))
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* const InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!IsValid(InputSystem))
	{
		return;
	}

	InputSystem->AddMappingContext(DefaultMappingContext.LoadSynchronous(), 0);
}