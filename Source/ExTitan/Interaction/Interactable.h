// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};



class UInteractionsManagerComponent;

class EXTITAN_API IInteractable
{
	GENERATED_BODY()


public:

	virtual UInteractionsManagerComponent* GetInteractionsManager() const = 0;
};
