// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Constructed"));
}


void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Init"));
}


void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	check(Engine);
	if (!Engine)
	{
		return;
	}

	Engine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Green, TEXT("Hosting"));


	UWorld* World = GetWorld();
	check(World);
	if (!World)
	{
		return;
	}

	//World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"));
	World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
}


void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	check(Engine);
	if (!Engine)
	{
		return;
	}

	Engine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));


	APlayerController* PlayerController = GetFirstLocalPlayerController();
	check(PlayerController);
	if (!PlayerController)
	{
		return;
	}

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
