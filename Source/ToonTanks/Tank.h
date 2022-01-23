// P4Peemo copyright 2022

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent *SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent *Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.f;

	void Move(float Value);

	void Turn(float Value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
