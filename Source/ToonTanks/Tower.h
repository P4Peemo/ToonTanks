// P4Peemo copyright 2022

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void HandleDestruction() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank *Tank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

	void CheckFireCondition();

	bool InFireRange();
};
