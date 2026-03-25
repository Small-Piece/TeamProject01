#include "MyActor.h"
#include "Engine/Engine.h"  
AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	CurrentStep = 0;

	GetWorldTimerManager().SetTimer(
		StepTimerHandle,
		this,
		&AMyActor::ExecuteOneStep,
		1.0f,
		true,
		0.0f
	);

	UE_LOG(LogTemp, Warning, TEXT("AMyActor has begun play!"));
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyActor::ExecuteOneStep()
{
	if (CurrentStep >= RepeatCount)
	{
		GetWorldTimerManager().ClearTimer(StepTimerHandle);

		UE_LOG(LogTemp, Log, TEXT("All steps completed!"));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 5.0f, FColor::Yellow,
				TEXT("=== All steps completed! ==="));
		}
		return;
	}

	CurrentStep++;

	float RandDist = FMath::FRandRange(-MoveDistance, MoveDistance);
	float RandAngle = FMath::FRandRange(-TurnAngle, TurnAngle);

	UE_LOG(LogTemp, Log, TEXT("=== Step %d / %d ==="), CurrentStep, RepeatCount);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 8.0f, FColor::Cyan,
			FString::Printf(TEXT("=== Step %d / %d | Dist=%.1f  Angle=%.1f ==="),
				CurrentStep, RepeatCount, RandDist, RandAngle));
	}

	Turn(RandAngle);
	Move(RandDist);
}

void AMyActor::Move(float Distance)
{
	FVector Forward = GetActorForwardVector();
	FVector NewLocation = GetActorLocation() + (Forward * Distance);
	SetActorLocation(NewLocation);

	PrintLocation();
}

void AMyActor::Turn(float Angle)
{
	FRotator CurrentRot = GetActorRotation();
	FRotator DeltaRot(0.0f, Angle, 0.0f);
	SetActorRotation(CurrentRot + DeltaRot);

	UE_LOG(LogTemp, Log, TEXT("Turn: Yaw += %.1f -> Rotation = %s"),
		Angle, *GetActorRotation().ToString());
}

void AMyActor::PrintLocation()
{
	FVector Loc = GetActorLocation();

	UE_LOG(LogTemp, Log, TEXT("Current Location: X=%.1f  Y=%.1f  Z=%.1f"),
		Loc.X, Loc.Y, Loc.Z);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 5.0f, FColor::Green,
			FString::Printf(TEXT("Location: X=%.1f  Y=%.1f  Z=%.1f"),
				Loc.X, Loc.Y, Loc.Z));
	}
}