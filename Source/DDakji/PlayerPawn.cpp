// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent->BindAction("Click", IE_Pressed, this, &APlayerPawn::GetWorldPosViaMouse);
	//PlayerInputComponent->BindAction("Click", IE_Pressed, this, &APlayerPawn::GetWorldPosViaMouse);
}

void APlayerPawn::GetWorldPosViaMouse()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Blue, TEXT("pawn"));
	/*
	ADDakjiGameModeBase* gamemode = (ADDakjiGameModeBase*)GetWorld()->GetAuthGameMode();

	if (gamemode->currentPhase == Phase::Target)
	{
		const FVector Start = GetFocalLocation();
		const FVector End = Start + GetControlRotation().Vector() * 256;

		FHitResult HitData(ForceInit);

		//if (LineTraceSingleForObjects(GetPawn(), Start, End, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitData, true))
		if(UMyStaticLibrary::Trace(GetWorld(), GetPawn(), Start, End, HitData))
		{
			FString resultText = FString::Printf(TEXT("[%s] %s"), *HitData.Actor->GetName(), *HitData.Location.ToString());

			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, resultText);
		}
	}*/
}
