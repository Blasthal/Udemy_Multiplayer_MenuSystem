// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UPuzzlePlatformsGameInstance Constructed"));

	// メインメニュー
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	check(MenuBPClass.Class);
	if (!MenuBPClass.Class)
	{
		return;
	};

	UE_LOG(LogTemp, Warning, TEXT("Found class %s, in Constructor"), *MenuBPClass.Class->GetName());

	MenuClass = MenuBPClass.Class;

	// インゲームメニュー
	static ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	check(InGameMenuBPClass.Class);
	if (!InGameMenuBPClass.Class)
	{
		return;
	};

	UE_LOG(LogTemp, Warning, TEXT("Found class %s, in Constructor"), *InGameMenuBPClass.Class->GetName());

	InGameMenuClass = InGameMenuBPClass.Class;
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

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	check(Menu);
	if (!Menu)
	{
		return;
	}

	Menu->Setup();
	Menu->SetMenuInterface(this);
}


void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	check(InGameMenuClass);
	if (!InGameMenuClass)
	{
		return;
	}

	InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	check(InGameMenu);
	if (!InGameMenu)
	{
		return;
	}

	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}


void UPuzzlePlatformsGameInstance::Host()
{
	check(Menu);
	if (Menu)
	{
		Menu->TearDown();
	}


	UEngine* Engine = GetEngine();
	check(Engine);
	if (!Engine)
	{
		return;
	}


	UWorld* World = GetWorld();
	check(World);
	if (!World)
	{
		return;
	}


	UE_LOG(LogTemp, Warning, TEXT("Hosting"));
	Engine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Green, TEXT("Hosting"));

	//World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"));
	World->ServerTravel(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen"));
}


void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	check(Menu);
	if (Menu)
	{
		Menu->TearDown();
	}


	UEngine* Engine = GetEngine();
	check(Engine);
	if (!Engine)
	{
		return;
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	check(PlayerController);
	if (!PlayerController)
	{
		return;
	}


	UE_LOG(LogTemp, Warning, TEXT("Joining %s"), *Address);
	Engine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
