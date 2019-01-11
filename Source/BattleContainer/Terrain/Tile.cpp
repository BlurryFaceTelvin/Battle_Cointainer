// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"


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
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



