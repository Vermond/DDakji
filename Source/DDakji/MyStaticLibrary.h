#pragma once

#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DDakjiGameModeBase.h"
#include "DDakjiPlayerController.h"
#include "MyStaticLibrary.generated.h"

//https://wiki.unrealengine.com/Trace_Functions
UCLASS()
class UMyStaticLibrary : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	//FORCEINLNE function
	static FORCEINLINE bool IsValid(AActor* TheActor)
	{
		if (!TheActor) return false;
		if (!TheActor->IsValidLowLevel()) return false;
		return true;
	}

	static bool Trace(
		UWorld* World,
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Pawn,
		bool ReturnPhysMat = false
	) {
		if (!World)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
		TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;		

		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);

		//Re-initialize hit info
		HitOut = FHitResult(ForceInit);

		//Trace!
		World->LineTraceSingleByChannel(
			HitOut,		//result
			Start,	//start
			End, //end
			CollisionChannel, //collision channel
			TraceParams
		);

		//Hit any Actor?
		return (HitOut.GetActor() != NULL);
	}

	static FORCEINLINE ADDakjiGameModeBase* GetGameMode(const UObject* object)
	{
		return (ADDakjiGameModeBase*)GEngine->GetWorldFromContextObject(object)->GetAuthGameMode();
	}

	static FORCEINLINE ADDakjiPlayerController* GetPlayerController(const UObject* object)
	{
		return (ADDakjiPlayerController*)GEngine->GetWorldFromContextObject(object)->GetFirstPlayerController();
	}
};