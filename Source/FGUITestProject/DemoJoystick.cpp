#include "DemoJoystick.h"

void UDemoJoystick::OnDemoStart_Implementation()
{

    UUIPackage::AddPackage(TEXT("/Game/UI/Main"), this);
    sceneComp = UUIPackage::CreateObject("Main", "sceneCom", this)->As<UGComponent>();
    sceneComp->MakeFullScreen();
    sceneComp->SetParentToRoot();

    list = sceneComp->GetChild("n0")->As<UGList>();
    list->On(FUIEvents::ClickItem).AddUObject(this, &UDemoJoystick::__List_clickItem);//Members of scene list click event

    /*UUIPackage::AddPackage(TEXT("/Game/UI/Joystick"), this);

    MainView = UUIPackage::CreateObject("Joystick", "Main", this)->As<UGComponent>();
    MainView->MakeFullScreen();
    MainView->SetParentToRoot();

    Joystick = MakeShared<FJoystickModule>(MainView);

    UGObject* TextField = MainView->GetChild("n9");

    Joystick->OnMoving.BindLambda([TextField](float Degree) {
        TextField->SetText(FString::Printf(TEXT("%f"), Degree));
    });

    Joystick->OnMoveEnd.BindLambda([TextField]() {
        TextField->SetText(G_EMPTY_STRING);
    });*/
}


//
void UDemoJoystick::__List_clickItem(UEventContext* Context)
{
    UGButton* item = Cast<UGButton>(Context->GetData().AsUObject());
    const FString& name = item->GetTitle();
    fname = FName(*name);
    //fname = "Untitled";
    //FString fname = *name;
    UGameplayStatics::OpenLevel(GetWorld(), fname);
}



void UDemoJoystick::OnDemoEnd_Implementation()
{
    UUIPackage::RemovePackage("Joystick", this);
}