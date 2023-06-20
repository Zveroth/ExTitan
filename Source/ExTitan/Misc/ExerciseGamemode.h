// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExerciseGamemode.generated.h"



class UInputMappingContext;

UCLASS()
class EXTITAN_API AExerciseGamemode : public AGameModeBase
{
	GENERATED_BODY()
	

protected:

	virtual void BeginPlay() override;

private:

	void SetupInputContexts();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game|Setup")
	TSoftObjectPtr<UInputMappingContext> DefaultMappingContext;
};
