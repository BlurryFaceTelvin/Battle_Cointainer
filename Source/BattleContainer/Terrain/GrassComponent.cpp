// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"

void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnGrass();
}

void UGrassComponent::SpawnGrass()
{
	//spawning the grass
	for (size_t i = 0; i < SpawnCount; i++)
	{
		FVector Location = FMath::RandPointInBox(SpawningExtents);
		AddInstance(FTransform(Location));
	}
}
