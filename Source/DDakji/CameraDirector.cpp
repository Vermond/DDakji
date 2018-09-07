// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTarget(CameraOne);	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;

	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		// 로컬 플레이어의 콘트롤을 처리하는 액터를 찾습니다.
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				// 1 번 카메라로 즉시 컷해 들어갑니다.
				OurPlayerController->SetViewTarget(CameraOne);
			}
			else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			{
				// 2 번 카메라로 부드럽게 전환합니다.
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
			}
		}
	}*/
}

void ACameraDirector::ChangeCamera(int cameraNum)
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	switch (cameraNum)
	{
	case 1:
		OurPlayerController->SetViewTargetWithBlend(CameraOne, 0.75f);
		break;
	case 2:
		OurPlayerController->SetViewTargetWithBlend(CameraTwo, 0.75f);
		break;
	case 3:
		OurPlayerController->SetViewTargetWithBlend(CameraThree, 0.75f);
		break;
	default:
		//디폴트는 일단 첫번째 카메라로 설정함
		OurPlayerController->SetViewTargetWithBlend(CameraOne, 0.75f);
		break;
	}


}