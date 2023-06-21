// Fill out your copyright notice in the Description page of Project Settings.
#include "Building/BuildingBase.h"
#include "Interaction/InteractionsManagerComponent.h"



// Sets default values
ABuildingBase::ABuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	InteractionsManager = CreateDefaultSubobject<UInteractionsManagerComponent>(TEXT("InteractionsManager"));
}