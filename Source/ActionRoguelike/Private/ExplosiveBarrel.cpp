// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Core/Public/Delegates/Delegate.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//StaticMeshComp->OnComponentHit.AddDynamic(this,&AExplosiveBarrel::BarrelExplode());
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetSimulatePhysics(true);
	RootComponent = StaticMeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(StaticMeshComp);
	ForceComp->SetAutoActivate(false);

	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	ForceComp->bImpulseVelChange = true;
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarrel::BarrelExplode() 
{
	//ForceComp->FireImpulse();

}

