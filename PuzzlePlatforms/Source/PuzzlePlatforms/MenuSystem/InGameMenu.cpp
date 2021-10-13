// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"


bool UInGameMenu::Initialize()
{
	bool bIsSuccess = Super::Initialize();
	if (!bIsSuccess)
	{
		return false;
	}


	return true;
}
