// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDBase.generated.h"



class UListWidget;

struct FListWidgetEntryData;

UCLASS()
class EXTITAN_API AHUDBase : public AHUD
{
	GENERATED_BODY()
	

public:

	void DisplayListWidget(const TArray<FListWidgetEntryData>& InOptions, const TFunction<void(int32, UObject*)>& InCallback);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Classes")
	TSubclassOf<UListWidget> ListWidgetClass;
};