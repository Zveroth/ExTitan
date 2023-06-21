// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionsManagerComponent.generated.h"


class UInteractionBaseComponent;

struct FListWidgetEntryData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTITAN_API UInteractionsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionsManagerComponent();

	void RegisterInteraction(UInteractionBaseComponent* Interaction);
	void UnregisterInteraction(UInteractionBaseComponent* Interaction);

	void OnClicked();

private:

	TArray<FListWidgetEntryData> GetInteractionUIOptions() const;

private:

	UPROPERTY(VisibleAnywhere, Category = "Debug")
	TSet<UInteractionBaseComponent*> m_Interactions;
};
