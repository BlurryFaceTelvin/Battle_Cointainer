// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"
USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector Location;
	float Rotation;
	float Scale;
};


UCLASS()
class BATTLECONTAINER_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category = Spawning)
	void PlaceActors(TSubclassOf<AActor> ToBeSpawn, int MinSpawn , int MaxSpawn, float Radius, bool canScale);
	
	UFUNCTION(BlueprintCallable, Category = Spawning)
	void PlaceAIPawns(TSubclassOf<APawn> ToBeSpawn, int MinSpawn, int MaxSpawn, float Radius);
	TArray<FSpawnPosition> RandomSpawnPositions(int MinSpawn, int MaxSpawn, bool canScale, float Radius);

protected:
	UPROPERTY(EditDefaultsOnly, Category = Navigation)
	FVector NavigationBoundsOffset;
	UPROPERTY(EditDefaultsOnly,Category = Spawning)
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FVector MaxExtent;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Called when the object is destroyed in the game
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = Pool)
		void SetPool(class UActorPool* ActorPool);
	
private:
	class UActorPool* Pool = nullptr;
	AActor* NavMeshBoundsVolume = nullptr;
	void PositionNavMeshBoundsVolume();
	//check if the objects spawn(props) intersect with anything
	bool CanSpawnAtLocation(FVector Location,float Radius);
	bool FindEmptyLocation(FVector &OutLocation,float Radius);
	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToBeSpawn, int MinSpawn, int MaxSpawn, float Radius, bool canScale);

	void InserActor(TSubclassOf<AActor> ToBeSpawn, const FSpawnPosition& SpawnPosition);
	void InserActor(TSubclassOf<APawn> ToBeSpawn, const FSpawnPosition& SpawnPosition);
	

	
	
};

