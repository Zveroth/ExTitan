// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interactions/MoveToInteractionComponent.h"
#include "SoundInteractionComponent.generated.h"



class USoundBase;

UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class EXTITAN_API USoundInteractionComponent : public UMoveToInteractionComponent
{
	GENERATED_BODY()
	

public:

	USoundInteractionComponent();

protected:

	virtual void OnReachLocation() override;

protected:

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSoftObjectPtr<USoundBase> Sound;
};
