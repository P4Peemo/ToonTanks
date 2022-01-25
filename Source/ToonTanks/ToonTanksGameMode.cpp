// P4Peemo copyright 2022


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }

        GameOver(false);
    }
    else if (ATower *DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;

        if (TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    // Get the number of enemy towers to destroy
    TargetTowers = GetTargetTowersCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);
    
        FTimerHandle PlayerEnabledTimerHandle;
        FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );
        GetWorldTimerManager().SetTimer(
            PlayerEnabledTimerHandle,
            PlayerEnabledTimerDelegate,
            StartDelay,
            false
        );
    }
}

int32 AToonTanksGameMode::GetTargetTowersCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

    return Towers.Num();
}