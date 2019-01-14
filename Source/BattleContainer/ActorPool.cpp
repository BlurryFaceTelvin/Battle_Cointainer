// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

AActor * UActorPool::CheckOut()
{
	UE_LOG(LogTemp, Warning, TEXT("Checking out"));
	return nullptr;
}

void UActorPool::Return(AActor * ActorToReturn)
{
	if (ActorToReturn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Returned Null Actor"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Mesh Returned: %s"),*ActorToReturn->GetName());
}

void UActorPool::Add(AActor * ActorToAdd)
{
	if (ActorToAdd == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add Null Actor"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Mesh Add: %s"), *ActorToAdd->GetName());
}
