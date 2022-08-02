// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"
// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);
	//LidMesh->SetRelativeRotation(FRotator(130,0,0));

	TargetPitch = 110;
	IsRotating = false;
	RotationVelocity = FRotator(50.0,0.0,0.0); 
	
}


void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{

	//FVector::Equals
	
	
	//LidMesh->SetRelativeRotation(FRotator(0,0,0));
	float lidMeshRot = LidMesh->GetRelativeRotation().Pitch;
	if (!Used)
	{
		IsRotating = true;
		Used = true;
	}
	/*
	if ( FMath::IsNearlyEqual(lidMeshRot,180-TargetPitch,0.1f) )
	{
		LidMesh->SetRelativeRotation(FRotator(0,0,0));
	} else if ( FMath::IsNearlyEqual(lidMeshRot,0,0.1f) )
	{
		//LidMesh->SetRelativeRotation(FRotator(TargetPitch,0,0));
		IsRotating = true;
	}*/
	
	
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

	float lidMeshRot = LidMesh->GetRelativeRotation().Pitch;
	if (IsRotating)
	{
		//LidMesh->SetRelativeRotation(RotationVelocity*DeltaTime);
		//LidMesh->AddLocalRotation(RotationVelocity*DeltaTime);
		FRotator lidMeshCurrentRot = LidMesh->GetRelativeRotation();
		LidMesh->SetRelativeRotation(lidMeshCurrentRot+ (RotationVelocity*DeltaTime));
		
		lidMeshRot = LidMesh->GetRelativeRotation().Pitch;
		if ( FMath::IsNearlyEqual(lidMeshRot,90,0.1f) )
		{
			LidMesh->SetRelativeRotation(FRotator(TargetPitch,0,0));
			IsRotating = false;
		}
	}
	lidMeshRot = LidMesh->GetRelativeRotation().Pitch;
	
	FString DebugMSG = FString::Printf(TEXT("Rotate Value: %s"),*FString::SanitizeFloat(lidMeshRot));
	GEngine->AddOnScreenDebugMessage(1,0.0f,FColor::Green,DebugMSG);

}

