// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleContainerGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECONTAINER_API AInfiniteTerrainGameMode : public ABattleContainerGameMode
{
	GENERATED_BODY()
public:
	AInfiniteTerrainGameMode();
	UFUNCTION(BlueprintCallable, Category = BoundsPool)
	void populateBoundsVolumePool();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pool)
		class UActorPool* NavMeshBoundsPool = nullptr;
private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);
	
	
};
