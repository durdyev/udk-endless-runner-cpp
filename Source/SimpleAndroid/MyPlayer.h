// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyPlayer.generated.h"

UCLASS()
class SIMPLEANDROID_API AMyPlayer : public APawn
{
	GENERATED_BODY()
    
private:
    TSubclassOf<AActor> FloorActor;
    FVector* lastLocation = NULL;
    AActor* lastActor;
    void SpawnFloor();
protected:
    USceneComponent* RootComponent;
    USpringArmComponent* springArmComponent;
    UCameraComponent* camera;
	
public:
	// Sets default values for this actor's properties
	AMyPlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
