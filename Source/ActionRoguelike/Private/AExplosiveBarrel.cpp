// Fill out your copyright notice in the Description page of Project Settings.


#include "AExplosiveBarrel.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
AAExplosiveBarrel::AAExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");

}

// Called when the game starts or when spawned
void AAExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

