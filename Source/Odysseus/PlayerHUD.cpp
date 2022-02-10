// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

APlayerHUD::APlayerHUD()
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarObject(TEXT("/Game/Odysseus/Blueprints/BP_UI/UMG_UI_Gameplay"));
}
void APlayerHUD::DrawHUD()
{
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
