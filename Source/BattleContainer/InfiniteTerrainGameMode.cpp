// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "Runtime/NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsPool = CreateAbstractDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrainGameMode::populateBoundsVolumePool()
{
	///find the navMesh bounds volume in the world and add it to the pool
	auto NavMeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while(NavMeshIterator)
	{
		AddToPool(*NavMeshIterator);
		//go to the next
		++NavMeshIterator;
	}
}
void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume * VolumeToAdd)
{
	NavMeshBoundsPool->Add(VolumeToAdd);
}
