// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h "

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToBeSpawn,int MinSpawn,int MaxSpawn)
{
	//calculate the min and max points of the tile 
	FVector Min(0,-2000,0);
	FVector Max(4000,2000,0);
	FBox Bounds(Min, Max);
	int NumberOfSpawns = FMath::RandRange(MinSpawn, MaxSpawn);
	//generate random spawn locations
	for (int i = 0; i < NumberOfSpawns; i++)
	{
		FVector Spawnpoints = FMath::RandPointInBox(Bounds);
		//spawn the actors and place them correctly
		AActor* SpawnedActor = GetWorld()->SpawnActor(ToBeSpawn);
		SpawnedActor->SetActorRelativeLocation(Spawnpoints);
		SpawnedActor->AttachToActor(this,FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	SphereCast(GetActorLocation(), 300);
	SphereCast(GetActorLocation()+FVector(0,0,1000), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::SphereCast(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, Radius, 32, ResultColor,true,100);
	return HasHit;
}



