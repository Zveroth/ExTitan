// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionBaseComponent.generated.h"



class UInteractionsManagerComponent;
class AAgentBase;

UCLASS()
class EXTITAN_API UInteractionBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInteractionBaseComponent();

	const FText& GetInteractionText() const { return InteractionText; }

	void BeginInteractionProcess(AAgentBase* InteractingAgent);
	void BreakInteractionProcess();

	bool IsOccupied() const;

	bool CanBeUsed() const { return MaxUses != 0; }

protected:

	virtual void BeginPlay() override;

	void EndInteractionProcess();

	virtual void BeginInteraction_Implementation() {}
	virtual void BreakInteraction_Implementation(AAgentBase* InAgent) {}
	virtual void EndInteraction_Implementation(AAgentBase* InAgent) {}

private:

	UInteractionsManagerComponent* GetOwnerInteractionsManager() const;

	void RegisterInteraction();
	void UnregisterInteraction();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	FText InteractionText;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	int32 MaxUses = -1;

	UPROPERTY()
	AAgentBase* OccupyingAgent;
};
