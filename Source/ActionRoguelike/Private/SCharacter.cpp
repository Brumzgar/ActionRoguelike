// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false; // 'b' at the front because its boolean

	AttackDelay = 0.2f;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControllerRotation = GetControlRotation();
	ControllerRotation.Pitch = 0.0f;
	ControllerRotation.Roll = 0.0f;

	AddMovementInput(ControllerRotation.Vector(), Value);

	//AddMovementInput(GetActorForwardVector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControllerRotation = GetControlRotation();
	ControllerRotation.Pitch = 0.0f;
	ControllerRotation.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControllerRotation).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);

	//AddMovementInput(GetActorRightVector(), Value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, AttackDelay);

	// GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack); // Function used to clear it if our character were to die?

	/*FVector RightHandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransformMatrix = FTransform(GetControlRotation(), RightHandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransformMatrix, SpawnParams);*/ // Moved to ASCharacter::PrimaryAttack_TimeElapsed() as an Attack with delay
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector RightHandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTransformMatrix = FTransform(GetControlRotation(), RightHandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransformMatrix, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}
