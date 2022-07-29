// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DemoObject.h"
#include "DemoTreeView.generated.h"


//Static variable
static bool room;//room button in bList
static bool move;//move button in bList
static bool rotate; //rotate button in bList  
static bool del;//del button in bList 
static bool describe;//describe button in bList 
static bool cancel;//cancel button in bList 
static int i_rotate;//Whether the main material rotation is turned on
static int i_copy;//Whether master material copy is turned on
static UGController* room_c1;//Room controller
static UGList* bList;//bList list

static UGComponent* Comp;//Global components

UCLASS(Blueprintable)
class FGUITESTPROJECT_API UDemoTreeView : public UDemoObject
{
    GENERATED_BODY()



        //static UGButton* test_btn;



public:
    UDemoTreeView();
    virtual ~UDemoTreeView();

    virtual void OnDemoStart_Implementation() override;
    virtual void OnDemoEnd_Implementation() override;



    //...................................................................Communication function
    virtual void MakePic();//Making flower slices
    virtual void SetMat(AActor* OtherActor, AStaticMeshActor* doubleTapObject, UTexture* Texture, int _style);//Attach materials to the floor
    virtual float GetWidth(AActor* OtherActor);//Get the width of the double-click object
    virtual float GetHeight(AActor* OtherActor);//Get the height of the double-click object
    virtual void SetWidth(AActor* OtherActor, float objectWidth);    //set the width of the double-click object
    virtual void SetHeight(AActor* OtherActor, float objectHeight);//set the height of the double-click object


    virtual FTransform GetLivingroomLocation(AActor* OtherActor, int index);//Get the position of the first person in the living room
    virtual float GetLivingroomRotation(AActor* OtherActor, int index);//Get the angle of the first person in the living room
    virtual TArray<int> GetLivingroomDirection(AActor* OtherActor);//Get the direction sign array of the first person living room

    virtual FTransform GetBedroomLocation(AActor* OtherActor, int index);//Get the position of the first person in the bedroom
    virtual float GetBedroomRotation(AActor* OtherActor, int index);//Get the angle of the first person in the bedroom
    virtual TArray<int> GetBedroomDirection(AActor* OtherActor);//Get the direction sign array of the first person bedroom

    virtual FTransform GetKitchenLocation(AActor* OtherActor, int index);//Get the position of the first person in the kitchen
    virtual float GetKitchenRotation(AActor* OtherActor, int index);//Get the angle of the first person in the kitchen
    virtual TArray<int> GetKitchenDirection(AActor* OtherActor);//Get the direction sign array of the first person kitchen

    virtual FTransform GetWCLocation(AActor* OtherActor, int index);//Get the position of the first person in the toilet
    virtual float GetWCRotation(AActor* OtherActor, int index);//Get the angle of the first person in the toilet
    virtual TArray<int> GetWCDirection(AActor* OtherActor);//Get the direction sign array of the first person toilet


    virtual void GetLivingRoomCamCount(AActor* OtherActor);//Return to the number of cameras in the living room
    virtual void GetBedRoomCamCount(AActor* OtherActor);//Return to the number of cameras in the bedroom
    virtual void GetKitchenCamCount(AActor* OtherActor);//Return to the number of kitchen cameras
    virtual void GetWCCamCount(AActor* OtherActor);//Return to the number of toilet cameras

    virtual TArray<AStaticMeshActor*> GetChangeObject(AActor* OtherActor);//Returns an array of objects with replaceable materials  
    virtual void InitD_mat(AActor* OtherActor, int CountChangeObject); //Initialize array d_mat,Quantity equals change_object   
    virtual void InitIf_change(AActor* OtherActor, int CountChangeObject);//Initialize array if_change,Quantity equals change_object

    //assignment the global variable index_of_change_object
    virtual void SetIndexOfChangeObject(AActor* OtherActor, int indexOfChangeObject);
    //Save copied object parent material
    virtual void SetCopyMat(AActor* OtherActor, UMaterialInstanceDynamic* copyMat);


    //Initializes a dynamic material copy of the original shader of a replaceable material object
    virtual void InitChangeObjectDMat(AActor* OtherActor);
    //get the global variable double_tap_object
    virtual AStaticMeshActor* GetDoubleTapObject(AActor* OtherActor);
    //set the global variable double_tap_object  
    virtual void SetDoubleTapObject(AActor* OtherActor, AStaticMeshActor* doubleTapObject);
    //set the global variable tap_object  
    virtual void SetTapObject(AActor* OtherActor, AStaticMeshActor* TapObject);
    //set the global variable copy_object
    virtual void SetCopyObject(AActor* OtherActor, AStaticMeshActor* copyObject);

    //Set current direction sign  
    virtual  void SetCurrentDirection(AActor* OtherActor, int cam, TArray<int> t_dirction);

    //void OnClickNode(UEventContext* Context);
    //void RenderTreeNode(UGTreeNode* Node, UGComponent* Obj);
    //...................................................................Ordinary function
    UFUNCTION()
        bool CheckMakePic();//Test before generating flower pieces
    UFUNCTION()
        void CheckFloorNumSelected();//Check whether the number of selected tile pictures is sufficient
    UFUNCTION()
        void Add_Cam(int amount_cam);//Lens growth regression
    UFUNCTION()
        void Change_View();//Shot switching
    UFUNCTION()
        void fTabQuit();//Functions used by the close button in the scheme
    //...........................................................................Keyboard click event
    UFUNCTION()
        void OnClick_Keyboard_button(UEventContext* Context);//Keyboard button click event

    UFUNCTION()
        void OnClick_chang_up_button(UEventContext* Context);//"Long" up arrow button click event
    UFUNCTION()
        void OnClick_chang_down_button(UEventContext* Context);//"Long" down arrow button click event

    UFUNCTION()
        void OnClick_kuan_up_button(UEventContext* Context);//"Wide" up arrow button click event
    UFUNCTION()
        void OnClick_kuan_down_button(UEventContext* Context);//"Wide" down arrow button click event


    UFUNCTION()
        void OnClick_make_pic_button(UEventContext* Context);//Click event of Confirm button in scheme
    UFUNCTION()
        void OnClick_quit_button(UEventContext* Context);//Click event of close button in scheme
    UFUNCTION()
        void OnClick_clear_button(UEventContext* Context);//Click event of clear button in scheme

    UFUNCTION()
        void  OnClick_livingroom_button(UEventContext* Context);//Click event of secondary button livingroom_btn in bList
    UFUNCTION()
        void  OnClick_bedroom_button(UEventContext* Context);//Click event of secondary button bedroom_btn in bList
    UFUNCTION()
        void  OnClick_kitchen_button(UEventContext* Context);//Click event of secondary button kitchen_btn in bList
    UFUNCTION()
        void  OnClick_wc_button(UEventContext* Context);//Click event of secondary button wc_btn in bList
    UFUNCTION()
        void  OnClick_product_id_TextInput(UEventContext* Context);//Click event of product ID text input  in plist
    UFUNCTION()
        void  OnClick_search_btn(UEventContext* Context);// Click event of query button in pList

    //.................................................................................bLiat
    UFUNCTION()
        void  __bList_clickItem(UEventContext* Context);//Click event of bList
         //Initialize the controller of bList
    UFUNCTION()
        void Init_Controller(FString s_controller);

    //Highlight or unhighlight the button in bList
    UFUNCTION()
        void Init_Button(FString fname, int _style);
    //Initialize all values of myactor
    UFUNCTION()
        void Init_Myactor();

    UFUNCTION()
        void  __fList_clickItem(UEventContext* Context);//Click event of fList
    UFUNCTION()
        void __pList_select_clickItem(UEventContext* Context);//Click event of pList_select
    UFUNCTION()
        void __pList_clickItem(UEventContext* Context);//Click event of pList





    UFUNCTION()
        void RenderPListItem(int32 index, UGObject* obj);//render pList
    UFUNCTION()
        void RenderPListSearchItem(int32 index, UGObject* obj);//Render pList by query

    UFUNCTION()
        void RenderPListSelectItem(int32 index, UGObject* obj);//Render the product selection list in the pattern on the right
    UFUNCTION()
        void Init_you(FString floorId);
    UFUNCTION()
        void Clear_you_select();
    UFUNCTION()
        AActor* TongXin();
    UFUNCTION()
        void Show_Alert(FString s_result);//Pop up warning box
    UFUNCTION()
        void Close_Alert();//close warning box



    //.........................................................variable

private:
    APawn* pawn;//first person
    int current_room;//Number of the current room
    //int count_room;//房间数量
    int current_cam;//Current camera number
    int count_livingroom_cam;//Number of cameras in the living room
    int count_bedroom_cam;//Number of bedroom cameras
    int count_kitchen_cam;//Number of kitchen cameras
    int count_wc_cam;//Number of toilet cameras





    AActor* myactor;//myactor used For communication
    //........................................................Component

    UGButton* input_btn;//Confirm button of scheme
    UGComponent* bList_comp;//bList component
    UGComponent* pListComp;//pList component

    //.............................................scheme
    UGController* main;//main controller
    UGComponent* fTab;//fTab component
    UGTextInput* t_width_TextInput;//Text input box: select tile width
    UGTextInput* t_height_TextInput;//Text input box: select tile height
    UGTextInput* current_TextInput;//Current text input box

    UGButton* chang_up_btn;//"Long" up button
    UGButton* chang_down_btn;//"Long" down button
    UGButton* kuan_up_btn;//"Width" up button
    UGButton* kuan_down_btn;//"Width" down button
    int current_pList_select_index;


    UGList* fList1;//Pattern list single brick and double brick
    UGList* fList2;//Pattern list mosaic
    UGList* pList_select;//Product selection list in the pattern on the right side of the scheme
    UGButton* current_pList_select_button;//Currently selected button in the pattern on the right side of the scheme
    UGButton* next_pList_select_button;//Next alternative button in the pattern on the right side of the scheme
    //........................................controller
    UGController* bList_c1;//bList controller

    UGController* fTab_c1;//fTab controller


    UGComponent* alert_comp;//alert component
    UGButton* alert_btn;//alert button
    UGController* alert_c1;//alert controller
    FTimerHandle MyTimerHandle;//Timer handle
    //........................................button
    UGButton* make_pic_button;//Confirm button of scheme
    UGButton* quit_button;//Close button of scheme
    UGButton* clear_button;//Clear button of scheme

      //....................................................pList
    UGList* pList;//product list
    UGController* pList_c1;//pList controller
    UGTextInput* product_id_TextInput;//Text input box: Tiles id
    UGButton* search_btn;//Query button for pList
    FString search_image_id;//Products id entered in the query box





    //.........................................................bList



    UGButton* livingroom_btn;//livingroom button in bList
    UGButton* bedroom_btn;//bedroom button in bList
    UGButton* kitchen_btn;//kitchen button in bList
    UGButton* wc_btn;//wc button in bList


    int count;//Item number in pList
    TArray<FString> t_image_id;//Tile Map id array 
    TArray<FString> l_image_id;//array for selected tile，element style"CT8073AS-0-0-1.2-0.6-1.2-0.6-0-2"
    FString floor_id;//Flower pattern id
    FString current_image_id;//Currently selected tile id
    FString brick_width;//Currently selected tile width
    FString brick_height;//Currently selected tile height

    FString  style;//Flower pattern
    int floor_num;//Number of flower

    int count_change_object;//Number of replaceable material objects
    TArray<AStaticMeshActor*> t_change_object;//Replaceable material array

    TArray<FString> floor_size = { "300","600","800" };//Tile size array


    //.............................................keyboard
    UGComponent* keyboardComp;//keyboard componenet
    UGController* keyboard_c1;//keyboard controller
    UGButton* A_btn;//A button
    UGButton* B_btn;//B button
    UGButton* C_btn;//C button
    UGButton* D_btn;//D button
    UGButton* E_btn;//E button
    UGButton* F_btn;//F button
    UGButton* G_btn;//G button
    UGButton* H_btn;//H button
    UGButton* I_btn;//I button
    UGButton* J_btn;//J button
    UGButton* K_btn;//K button
    UGButton* L_btn;//L button
    UGButton* M_btn;//M button
    UGButton* N_btn;//N button
    UGButton* O_btn;//O button
    UGButton* P_btn;//P button
    UGButton* Q_btn;//Q button
    UGButton* R_btn;//R button
    UGButton* S_btn;//S button
    UGButton* T_btn;//T button
    UGButton* U_btn;//U button
    UGButton* V_btn;//V button
    UGButton* W_btn;//W button
    UGButton* X_btn;//X button
    UGButton* Y_btn;//Y button
    UGButton* Z_btn;//Z button
    UGButton* one_btn;//1 button
    UGButton* two_btn;//2 button
    UGButton* three_btn;//3 button
    UGButton* four_btn;//4 button
    UGButton* five_btn;//5 button
    UGButton* six_btn;//6 button
    UGButton* seven_btn;//7 button
    UGButton* eight_btn;//8 button
    UGButton* nine_btn;//9 button
    UGButton* zero_btn;//0 button
    UGButton* back_btn;//back button    
    UGButton* down_btn;//down button
    /*
    UGComponent* MainView;
    UGTree* Tree1;
    UGTree* Tree2;
    UGTreeNode* SpecialNode;
    */

    //set Comp
    UFUNCTION(BlueprintCallable, Category = "MyUI")
        static void setComp(UGComponent* comp);
    //All buttons are not selected in bList
    UFUNCTION(BlueprintCallable, Category = "MyUI")
        static void Init_bList_All_Button();

    //return i_rotate
    UFUNCTION(BlueprintCallable, Category = "MyUI")
        static int getIRotate();
    //set i_copy
    UFUNCTION(BlueprintCallable, Category = "MyUI")
        static void setICopy(int iCopy);
    //return i_copy
    UFUNCTION(BlueprintCallable, Category = "MyUI")
        static int getICopy();

    //Double click to initialize bList controller
    UFUNCTION(BlueprintCallable, Category = "MyUI")
        static void Init_bList();

};
