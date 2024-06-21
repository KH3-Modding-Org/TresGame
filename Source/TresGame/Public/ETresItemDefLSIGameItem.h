#pragma once
#include "CoreMinimal.h"
#include "ETresItemDefLSIGameItem.generated.h"

UENUM(BlueprintType)
enum class ETresItemDefLSIGameItem : uint8 {
    NOTHING,
    ITEM01 UMETA(DisplayName = "Giantland"),
    ITEM02 UMETA(DisplayName = "Mickey, the Mail Pilot"),
    ITEM03 UMETA(DisplayName = "The Musical Farmer"),
    ITEM04 UMETA(DisplayName = "Building a Building"),
    ITEM05 UMETA(DisplayName = "The Mad Doctor"),
    ITEM06 UMETA(DisplayName = "Mickey Cuts Up"),
    ITEM07 UMETA(DisplayName = "Taxi Troubles"),
    ITEM08 UMETA(DisplayName = "The Barnyard Battle"),
    ITEM09 UMETA(DisplayName = "The Karnival Kid"),
    ITEM10 UMETA(DisplayName = "Cast Out to Sea"),
    ITEM11 UMETA(DisplayName = "Camping Out"),
    ITEM12 UMETA(DisplayName = "How to Play Golf"),
    ITEM13 UMETA(DisplayName = "Mickey's Circus"),
    ITEM14 UMETA(DisplayName = "The Wayward Canary"),
    ITEM15 UMETA(DisplayName = "Barnyard Sports"),
    ITEM16 UMETA(DisplayName = "The Klondike Kid"),
    ITEM17 UMETA(DisplayName = "Mickey's Kitten Catch"),
    ITEM18 UMETA(DisplayName = "Fishin' Frenzy"),
    ITEM19 UMETA(DisplayName = "Beach Party"),
    ITEM20 UMETA(DisplayName = "Mickey's Prison Escape"),
    ITEM21 UMETA(DisplayName = "How to Play Baseball"),
    ITEM22 UMETA(DisplayName = "Mickey's Mechanical Man"),
    ITEM23 UMETA(DisplayName = "Mickey Steps Out"),
    _MAX = 0x20,
};

