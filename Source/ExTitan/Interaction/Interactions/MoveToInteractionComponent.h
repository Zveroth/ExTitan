// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InteractionBaseComponent.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "MoveToInteractionComponent.generated.h"



UCLASS()
class EXTITAN_API UMoveToInteractionComponent : public UInteractionBaseComponent
{
	GENERATED_BODY()
	

protected:

	virtual void BeginInteraction_Implementation() override;
	virtual void BreakInteraction_Implementation(AAgentBase* InAgent) override;
	virtual void EndInteraction_Implementation(AAgentBase* InAgent) override;

	virtual void OnReachLocation();

private:

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
};
