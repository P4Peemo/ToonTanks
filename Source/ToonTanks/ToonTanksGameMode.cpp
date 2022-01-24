// P4Peemo copyright 2022


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        APlayerController *TankPlayerController = Tank->GetTankPlayerController();
        if (TankPlayerController)
        {
            Tank->DisableInput(TankPlayerController);
            TankPlayerController->bShowMouseCursor = false;
        }
    }
    else if (ATower *DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}