// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "../Weapons/Gun.h"
// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	//create a camera component
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FPCamera->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FPCamera);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	//spawning the gun
	if(GunBlueprint==NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun Blueprint missing"));
		return;
	}
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	
	Gun->TP_AnimInstance = GetMesh()->GetAnimInstance();
	Gun->FP_AnimInstance = Mesh1P->GetAnimInstance();
	//if it is player use the 1P mesh else default mesh
	//if possessed by player we bind action to the fire method
	if(InputComponent!=NULL)
	{
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void AMannequin::PullTrigger()
{
	Gun->OnFire();
}

