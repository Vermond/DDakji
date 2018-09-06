// Fill out your copyright notice in the Description page of Project Settings.

#include "DDakjiPlayerController.h"

#include "DDakjiGameModeBase.h"
#include "MyStaticLibrary.h"

#include "UserWidget.h"
#include "EngineUtils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UnrealString.h"

#include "DrawDebugHelpers.h"

ADDakjiPlayerController::ADDakjiPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	tickTime = 0;
}

void ADDakjiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	for (TActorIterator<ACameraDirector> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		cameraDirector = *ActorItr;
		break;
	}

	SetUI(startUIWidget);
}

void ADDakjiPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float nextAnnoyTime = .05f;	

	tickTime -= DeltaTime;

	if (tickTime < 0)
	{
		tickTime = nextAnnoyTime;

		FVector2D pos = FVector2D();
		GetMousePosition(pos.X, pos.Y);
		
		pos.X += rand() % 20 - 10;
		pos.Y += rand() % 20 - 10;

		SetMouseLocation((int)(pos.X), (int)(pos.Y));
	}
}

void ADDakjiPlayerController::ChangeUI(Phase phase)
{
	//페이즈 변경 처리를 임시로 이 함수에서 수행한다
	//적절한 위치 결정하면 꼭 옮기자
	ADDakjiGameModeBase* gameMode = (ADDakjiGameModeBase*)GetWorld()->GetAuthGameMode();
	gameMode->currentPhase = phase;

	//생성자 밖에서 틱 전환은 이 함수를 사용해야 한다
	SetActorTickEnabled(false);

	switch (phase)
	{
	case Start:
		//카메라 원위치
		cameraDirector->ChangeCamera(1);

		SetUI(startUIWidget);
		break;
	case Target:
		//딱지치기를 위한 상단으로 카메라 이동
		cameraDirector->ChangeCamera(2);

		//틱에서 방해 시작
		SetActorTickEnabled(true);

		//SetUI(targetUIWidget);
		SetUI(nullptr);
		break;
	case Powering:
		break;
	case Result:
		break;
	default:
		break;
	}
}

void ADDakjiPlayerController::SetUI(TSubclassOf<class UUserWidget> targetWidget, bool showCuror)
{
	if (nullptr != currentUI)
	{
		currentUI->RemoveFromViewport();
		currentUI = nullptr;
	}

	if (nullptr != targetWidget)
	{		
		currentUI = CreateWidget<UUserWidget>(this, targetWidget);
		currentUI->AddToViewport();
		bShowMouseCursor = showCuror;
	}
}

FVector2D ADDakjiPlayerController::GetMousePos()
{
	FVector2D pos = FVector2D();
	GetMousePosition(pos.X, pos.Y);

	return pos;
}

void ADDakjiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Click", IE_Pressed, this, &ADDakjiPlayerController::GetWorldPosViaMouse);
}

void ADDakjiPlayerController::GetWorldPosViaMouse()
{	
	ADDakjiGameModeBase* gamemode = (ADDakjiGameModeBase*)GetWorld()->GetAuthGameMode();

	if (gamemode->currentPhase == Phase::Target)
	{
		FHitResult HitData(ForceInit);

		FVector worldLocation;
		FVector worldDirection;
		//카메라 위치와 마우스 클릭을 기준으로 한다
		DeprojectMousePositionToWorld(worldLocation, worldDirection);
		
		const FVector Start = cameraDirector->CameraTwo->GetActorLocation();
		const FVector End = Start + cameraDirector->CameraTwo->GetActorRotation().Vector() * 512;

		//클릭 위치 확인용 (디버그용)
		//DrawDebugLine(GetWorld(), Start, End, FColor(0, 0, 255), false, 30.f, 0, 12.3f);

		if(UMyStaticLibrary::Trace(GetWorld(), GetPawn(), Start, End, HitData))
		{
			FString resultText = FString::Printf(TEXT("[%s] %s"), *HitData.Actor->GetName(), *HitData.Location.ToString());

			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, resultText);
		}
	}
}