// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
	bool bIsSuccess = Super::Initialize();
	if (!bIsSuccess)
	{
		return false;
	}
	

	ensure(CancelButton);
	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);
	}


	ensure(QuitButton);
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);
	}


	return true;
}

void UInGameMenu::CancelPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed - %s"), *CancelButton->GetName());

	TearDown();
}

void UInGameMenu::QuitPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed - %s"), *QuitButton->GetName());

	check(MenuInterface);
	if (MenuInterface)
	{
		TearDown();
		MenuInterface->LoadMainMenu();
	}
}
