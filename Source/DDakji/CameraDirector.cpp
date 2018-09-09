// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"

#include "MyStaticLibrary.h"

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

	APlayerController* OurPlayerController = UMyStaticLibrary::GetPlayerController();
	OurPlayerController->SetViewTarget(CameraOne);	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraDirector::ChangeCamera(int cameraNum)
{
	APlayerController* OurPlayerController = UMyStaticLibrary::GetPlayerController();

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
	case 4:
		OurPlayerController->SetViewTargetWithBlend(CameraFour, 0.75f);
		break;
	default:
		//디폴트는 일단 첫번째 카메라로 설정함
		OurPlayerController->SetViewTargetWithBlend(CameraOne, 0.75f);
		break;
	}


}