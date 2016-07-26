// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleAndroid.h"
#include "SimpleAndroidGameMode.h"
#include "MyPlayer.h"

ASimpleAndroidGameMode::ASimpleAndroidGameMode() {
    DefaultPawnClass = AMyPlayer::StaticClass();
}