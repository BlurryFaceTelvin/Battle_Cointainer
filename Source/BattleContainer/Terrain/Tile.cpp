// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h "
#include "ActorPool.h"
// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToBeSpawn,int MinSpawn,int MaxSpawn,float Radius,bool canScale)
{
	float DefaultScale = 1,MaxScale = 4;
	int NumberOfSpawns = FMath::RandRange(MinSpawn, MaxSpawn);
	float randomScale = FMath::RandRange(DefaultScale, MaxScale);
	//generate random spawn locations
	for (int i = 0; i < NumberOfSpawns; i++)
	{
		FVector SpawnPoint;
		float scale = canScale ? randomScale : DefaultScale;
		bool found = FindEmptyLocation(SpawnPoint, Radius*scale);
		if(found)
		{
			float randomRotation = FMath::RandRange(-180.f, 180.f);
			InserActor(ToBeSpawn, SpawnPoint, randomRotation,scale); 
		}
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetPool(UActorPool * ActorPool)
{
	Pool = ActorPool;
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
	//calculate the min and max points of the tile 
	FVector Min(0,-2000,0);
	FVector Max(4000,2000,0);
	FBox Bounds(Min, Max);
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

void ATile::InserActor(TSubclassOf<AActor> ToBeSpawn, FVector SpawnPoint,float Rotation,float Scale)
{
		//spawn the actors and place them correctly
		AActor* SpawnedActor = GetWorld()->SpawnActor(ToBeSpawn);
		SpawnedActor->SetActorRelativeLocation(SpawnPoint);
		SpawnedActor->AttachToActor(this,FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
		SpawnedActor->SetActorRotation(FRotator(0, Rotation, 0));
		SpawnedActor->SetActorRelativeScale3D(FVector(Scale));
}



