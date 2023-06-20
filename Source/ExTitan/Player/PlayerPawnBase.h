// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"



struct FInputActionInstance;

class UCameraComponent;
class UInputAction;

UCLASS()
class EXTITAN_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup|Input")
	TSoftObjectPtr<UInputAction> InteractionInputAction;

private:

	void InteractCallback(const FInputActionInstance& Action);
};
