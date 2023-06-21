// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/Interactions/SoundInteractionComponent.h"

#include "Kismet/GameplayStatics.h"



USoundInteractionComponent::USoundInteractionComponent()
{
	InteractionText = FText::FromString("Sound");
}

void USoundInteractionComponent::OnReachLocation()
{
	UGameplayStatics::PlaySoundAtLocation(this, Sound.LoadSynchronous(), GetOwner()->GetActorLocation());
	EndInteractionProcess();
}