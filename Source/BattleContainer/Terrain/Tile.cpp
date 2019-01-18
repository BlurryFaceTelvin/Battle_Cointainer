// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "ActorPool.h"
// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NavigationBoundsOffset = FVector(2000, 0, 0);
	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(2000, 4000, 0);

}


template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToBeSpawn, int MinSpawn, int MaxSpawn, float Radius, bool canScale)
{
	float DefaultScale = 1, MaxScale = 4;
	int NumberOfSpawns = FMath::RandRange(MinSpawn, MaxSpawn);
	float randomScale = FMath::RandRange(DefaultScale, MaxScale);
	if(ToBeSpawn==nullptr)
	{
		return;
	}
	//generate random spawn locations
	for (int i = 0; i < NumberOfSpawns; i++)
	{
		FSpawnPosition spawnPosition;
		spawnPosition.Scale = canScale ? randomScale : DefaultScale;
		bool found = FindEmptyLocation(spawnPosition.Location, Radius*spawnPosition.Scale);
		if (found)
		{
			spawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			InserActor(ToBeSpawn, spawnPosition);
		}
	}
}

void ATile::PlaceActors(TSubclassOf<AActor> ToBeSpawn,int MinSpawn,int MaxSpawn,float Radius,bool canScale)
{
	RandomlyPlaceActors(ToBeSpawn, MinSpawn, MaxSpawn, Radius, canScale);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToBeSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
	
	RandomlyPlaceActors(ToBeSpawn, MinSpawn, MaxSpawn, Radius, false);
}



// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//check if we have a pool and a navmesh volume
	if (Pool!=nullptr&&NavMeshBoundsVolume != nullptr)
	{
		//return Navmesh to the pool
		Pool->Return(NavMeshBoundsVolume);
	}
	else {
		return;
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetPool(UActorPool * ActorPool)
{
	Pool = ActorPool;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->CheckOut();
	if(NavMeshBoundsVolume==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Not enough Pool Actors"),*GetName());
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation()+NavigationBoundsOffset);
	//update the navigation system
	FNavigationSystem::Build(*GetWorld());
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	return !HasHit;
}

bool ATile::FindEmptyLocation(FVector &OutLocation,float Radius)
{ 	
	FBox Bounds(MinExtent, MaxExtent);
	//loop 100 times till we find an empty location
	const int MAX_ATTEMPTS = 10;
	for (int i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector EmptyLocation = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(EmptyLocation, Radius)) 
		{
			OutLocation = EmptyLocation;
			return true;
		}
	}
	return false;
}



void ATile::InserActor(TSubclassOf<AActor> ToBeSpawn, const FSpawnPosition& SpawnPosition)
{
		//spawn the actors and place them correctly
		AActor* SpawnedActor = GetWorld()->SpawnActor(ToBeSpawn);
		if (SpawnedActor)
		{
			SpawnedActor->SetActorRelativeLocation(SpawnPosition.Location);
			SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
			SpawnedActor->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
			SpawnedActor->SetActorRelativeScale3D(FVector(SpawnPosition.Scale));
		}
}
void ATile::InserActor(TSubclassOf<APawn> ToBeSpawn, const FSpawnPosition& SpawnPosition)
{
	//spawn the actors and place them correctly
	FRotator rotation = FRotator(0, SpawnPosition.Rotation, 0);
	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(ToBeSpawn,SpawnPosition.Location,rotation);
	if (SpawnedPawn)
	{
		SpawnedPawn->SetActorRelativeLocation(SpawnPosition.Location);
		SpawnedPawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		SpawnedPawn->SpawnDefaultController();
		SpawnedPawn->Tags.Add(FName("Enemy"));
	}
}



