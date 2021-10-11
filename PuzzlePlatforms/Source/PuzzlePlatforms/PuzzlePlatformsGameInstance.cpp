// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

#include "PlatformTrigger.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Constructed"));


	// ÉÅÉCÉìÉÅÉjÉÖÅ[
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	check(MenuBPClass.Class);
	if (!MenuBPClass.Class)
	{
		return;
	};

	UE_LOG(LogTemp, Warning, TEXT("Found class %s, in Constructor"), *MenuBPClass.Class->GetName());

	MenuClass = MenuBPClass.Class;
	
}


void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Init"));
	UE_LOG(LogTemp, Warning, TEXT("Founded class %s"), *MenuClass->GetName());
}


void UPuzzlePlatformsGameInstance::LoadMenu()
{
	check(MenuClass);
	if (!MenuClass)
	{
		return;
	}

	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	check(Menu);
	if (!Menu)
	{
		return;
	}

	Menu->bIsFocusable = true;
	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	check(PlayerController);
	if (!PlayerController)
	{
		return;
	}

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;


	Menu->SetMenuInterface(this);
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
