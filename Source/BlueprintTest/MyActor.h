#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class BLUEPRINTTEST_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	AMyActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Move(float Distance);
	void Turn(float Angle);
	void ExecuteOneStep();

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveDistance = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnAngle = 45.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	int32 RepeatCount = 10;

private:
	void PrintLocation();

	FTimerHandle StepTimerHandle;
	int32 CurrentStep = 0;
};