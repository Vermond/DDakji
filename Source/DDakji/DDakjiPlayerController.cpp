// Fill out your copyright notice in the Description page of Project Settings.

#include "DDakjiPlayerController.h"

#include "DDakjiGameModeBase.h"
#include "MyStaticLibrary.h"

#include "UserWidget.h"
#include "EngineUtils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UnrealString.h"
#include "TimerManager.h"

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

void ADDakjiPlayerController::ChangeUIByPhase(Phase phase)
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

		SetUIDelayed(startUIWidget);
		break;
	case Target:
		//딱지치기를 위한 상단으로 카메라 이동
		cameraDirector->ChangeCamera(2);
		
		SetUIDelayed(nullptr);

		//틱에서 방해 시작
		SetActorTickEnabled(true);
		break;
	case Powering:
		cameraDirector->ChangeCamera(3);

		SetUIDelayed(powerUIWidget);
		break;
	case Result:
		cameraDirector->ChangeCamera(4);

		SetUIDelayed(resultUIWidget);
		break;
	default:
		break;
	}
}

void ADDakjiPlayerController::SetUI(TSubclassOf<class UUserWidget> targetWidget, bool showCursor)
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
		bShowMouseCursor = showCursor;
	}
}

void ADDakjiPlayerController::SetUIDelayed(TSubclassOf<class UUserWidget> targetWidget, bool showCursor)
{
	if (nullptr != currentUI)
	{
		currentUI->RemoveFromViewport();
		currentUI = nullptr;
	}

	FTimerDelegate tempDelegate;
	FTimerHandle TimerHandle;

	//타이머를 이용해 화면 전환 시간동안 UI 출력을 지연시킨다
	tempDelegate.BindUFunction(this, FName("SetUI"), targetWidget, showCursor);

	GetWorldTimerManager().SetTimer(TimerHandle, tempDelegate, .75f, false);
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

//원하는 시점이 아닌 곳에서 아무데나 빈 화면을 눌러도 바로 넘어가버리는 버그 있음
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
			//현재는 디버깅 위해 정보 텍스트로 출력중
			//다음 화면으로 데이터 넘겨주는 것으로 업데이트할 것
			FString resultText = FString::Printf(TEXT("[%s] %s"), *HitData.Actor->GetName(), *HitData.Location.ToString());

			GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, resultText);
		}

		ChangeUIByPhase(Phase::Powering);
	}
}