// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "Mannequin.h"
#include "../Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create camera component
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCameraComponent"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	//Create arms mesh to FP Character
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1p"));
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);




}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	if (GunBlueprint == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing"));
		return;
	}

	Mesh1P->bOnlyOwnerSee = true;
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),TEXT("GripPoint"));
	Gun->AnimInstance = Mesh1P->GetAnimInstance();
	
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void AMannequin::Fire() {
	Gun->OnFire();
}