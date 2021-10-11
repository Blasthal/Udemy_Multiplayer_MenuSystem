// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"


bool UMainMenu::Initialize()
{
	bool bIsSuccess = Super::Initialize();
	if (!bIsSuccess)
	{
		return false;
	}


	if (Host)
	{
		Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	}

	if (Join)
	{
		Join->OnClicked.AddDynamic(this, &UMainMenu::OnClickedJoin);
	}


	return true;
}


void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}


void UMainMenu::OnClickedJoin()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked - %s"), *Join->GetName());
}


void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("HostServer - %s"), *Host->GetName());

	check(MenuInterface);
	if (MenuInterface)
	{
		MenuInterface->Host();
	}
}
