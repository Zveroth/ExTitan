// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Interactions/MoveToInteractionComponent.h"
#include "BehaviorInteractionComponent.generated.h"



class UBehaviorTree;

UCLASS(ClassGroup = (Interaction), meta = (BlueprintSpawnableComponent))
class EXTITAN_API UBehaviorInteractionComponent : public UMoveToInteractionComponent
{
	GENERATED_BODY()
	

public:

	UBehaviorInteractionComponent();

protected:

	virtual void OnReachLocation() override;

	virtual void BreakInteraction_Implementation(AAgentBase* InAgent) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSoftObjectPtr<UBehaviorTree> Behavior;
};
