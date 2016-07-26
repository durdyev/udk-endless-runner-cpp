// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleAndroid.h"
#include "MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    static ConstructorHelpers::FObjectFinder<UBlueprint> FloorBP(TEXT("Blueprint'/Game/FloorBP'"));
    FloorActor = (UClass*)FloorBP.Object->GeneratedClass;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    springArmComponent->SetupAttachment(RootComponent);
    springArmComponent->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 30.0f), FRotator(-30.0f, 0.0f, 0.0f));
    springArmComponent->TargetArmLength = 400.0f;
    springArmComponent->bEnableCameraLag = true;
    springArmComponent->CameraLagSpeed = 3.0f;
    
    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
    camera->SetupAttachment(springArmComponent, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
    SpawnFloor();
    SpawnFloor();
    SpawnFloor();
}

void AMyPlayer::SpawnFloor() {
    // spawn floor
    if (FloorActor) {
        UWorld* const world = GetWorld();
        if (world) {
            FVector location = RootComponent->GetComponentLocation();
            FRotator rotation = RootComponent->GetComponentRotation();
            if (lastLocation == NULL) {
                lastActor = world->SpawnActor(FloorActor, &location, &rotation);
                lastLocation = &location;
            } else {
                lastLocation->Set(lastActor->GetActorLocation().X + 500, lastActor->GetActorLocation().Y, lastActor->GetActorLocation().Z);
                lastActor = world->SpawnActor(FloorActor, lastLocation, &rotation);
                UE_LOG(LogTemp, Warning, TEXT("LastlocationX_2: %f"), lastActor->GetActorLocation().X);

            }
        }
    }
}

// Called every frame
void AMyPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    FVector direction = GetActorForwardVector();
    FVector location = GetActorLocation();
    SetActorRelativeLocation(FVector(location.X + (direction.X + 150.0f * DeltaTime),
                                     location.Y, location.Z));
    
    if (location.X >= lastActor->GetActorLocation().X - 500) {
        UE_LOG(LogTemp, Warning, TEXT("LocationX: %f"), location.X);
        UE_LOG(LogTemp, Warning, TEXT("LastlocationX: %f"), lastActor->GetActorLocation().X);
        SpawnFloor();
        SpawnFloor();
        SpawnFloor();
    }
}

