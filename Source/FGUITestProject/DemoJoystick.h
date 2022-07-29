// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DemoObject.h"
#include "JoystickModule.h"
#include "DemoJoystick.generated.h"


static UGComponent* sceneComp;//Global component


/**
 *
 */
UCLASS(Blueprintable)
class FGUITESTPROJECT_API UDemoJoystick : public UDemoObject
{
    GENERATED_BODY()

public:
    virtual void OnDemoStart_Implementation() override;
    virtual void OnDemoEnd_Implementation() override;


    UFUNCTION()
        void  __List_clickItem(UEventContext* Context);//bList click event
private:
    //........................................................component

    UGList* list;//scene list
    FName fname;


    /* UGComponent* MainView;
     TSharedPtr<FJoystickModule> Joystick;*/
};
