// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMesh"));
	RootComponent = BaseStaticMesh;

	LidStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidStaticMesh"));
	LidStaticMesh->SetupAttachment(BaseStaticMesh);

	TargetPitch = 110;
}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidStaticMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));

}


// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

