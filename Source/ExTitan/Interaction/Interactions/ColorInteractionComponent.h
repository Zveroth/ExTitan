// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interactions/MoveToInteractionComponent.h"
#include "ColorInteractionComponent.generated.h"



UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class EXTITAN_API UColorInteractionComponent : public UMoveToInteractionComponent
{
	GENERATED_BODY()


public:

	UColorInteractionComponent();

protected:

	virtual void OnReachLocation() override;

protected:

	UPROPERTY(EditAnywhere, Category = "Setup")
	FLinearColor Color;
};
