// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interactable.h"
#include "BuildingBase.generated.h"



class UInteractionsManagerComponent;

UCLASS()
class EXTITAN_API ABuildingBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBase();

	virtual UInteractionsManagerComponent* GetInteractionsManager() const override { return InteractionsManager; }

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UInteractionsManagerComponent* InteractionsManager;
};