// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AgentBase.generated.h"



class UBehaviorTree;

UCLASS()
class EXTITAN_API AAgentBase : public ACharacter
{
	GENERATED_BODY()


	DECLARE_DELEGATE_OneParam(FAgentEvent, AAgentBase*);

public:
	// Sets default values for this pawn's properties
	AAgentBase();

	bool IsBusy() const { return m_bBusy; }

	void SetIsBusy(bool bInBusy);

	UStaticMeshComponent* GetCapsuleMesh() const { return CapsuleMesh; }

	void OverrideBehavior(UBehaviorTree* Behavior);
	void ClearBehaviorOverride();

protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	void SetupBehaviorTree();

public:

	FAgentEvent OnAgentBusyStateChanged;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CapsuleMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSoftObjectPtr<UBehaviorTree> DefaultBehaviorTree;

private:

	bool m_bBusy = false;
};
