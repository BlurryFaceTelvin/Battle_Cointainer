// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class BATTLECONTAINER_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category = SpawnActor)
	void PlaceActors(TSubclassOf<AActor> ToBeSpawn, int MinSpawn , int MaxSpawn, float Radius, bool canScale);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	//check if the objects spawn(props) intersect with anything
	bool CanSpawnAtLocation(FVector Location,float Radius);
	bool FindEmptyLocation(FVector &OutLocation,float Radius);
	void InserActor(TSubclassOf<AActor> ToBeSpawn, FVector SpawnPoint,float Rotation,float Scale);

	
	
};
