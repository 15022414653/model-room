#include "DemoTreeView.h"
#include "MyActor.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"

UDemoTreeView::UDemoTreeView()
{

}

UDemoTreeView::~UDemoTreeView()
{
}

void UDemoTreeView::OnDemoStart_Implementation()
{



    //Get player 0 from world settings
    pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    //Dynamic get myactor for communication
    myactor = TongXin();


    //Return the number of cameras in each room
    GetLivingRoomCamCount(myactor);
    GetBedRoomCamCount(myactor);
    GetKitchenCamCount(myactor);
    GetWCCamCount(myactor);
    //Get an array of replaceable materials
    t_change_object = GetChangeObject(myactor);
    //Number of replaceable material objects
    count_change_object = t_change_object.Num();
    //Initialize array d_mat,quantity equals to change_object
    InitD_mat(myactor, count_change_object);
    //Initialize array if_change,quantity equals to change_object
    InitIf_change(myactor, count_change_object);
    //Initializes a dynamic material copy of the original shader of a replaceable material object
    InitChangeObjectDMat(myactor);


    //First person initialization is located in the living room
    current_room = 0;
    current_cam = -1;
    Change_View();




    




   /* UUIPackage::AddPackage(TEXT("/Game/UI/Main"), this);
    Comp = UUIPackage::CreateObject("Main", "mainCom", this)->As<UGComponent>();
    Comp->MakeFullScreen();
    Comp->SetParentToRoot();*/

    //Initialize warning button
    alert_comp = Comp->GetChild("n42")->As<UGComponent>();
    alert_btn = alert_comp->GetChild("n1")->As<UGButton>();
    alert_c1 = Comp->GetController("alert_c1");//Get warning controller

    //.........................................................................................bList
    bList_comp = Comp->GetChild("n6")->As<UGComponent>();//bList componenet
    bList = bList_comp->GetChild("n0")->As<UGList>();//bList list
    bList_c1 = Comp->GetController("bList_c1");
    bList_c1->SetSelectedIndex(1);

    bList->On(FUIEvents::ClickItem).AddUObject(this, &UDemoTreeView::__bList_clickItem);
    //room controller
    room_c1 = bList_comp->GetController("c9");



    //Secondary button in bList
    livingroom_btn = bList_comp->GetChild("n58")->As<UGButton>();//livingroom button
    livingroom_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_livingroom_button);

    bedroom_btn = bList_comp->GetChild("n59")->As<UGButton>();//bedroom button
    bedroom_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_bedroom_button);

    kitchen_btn = bList_comp->GetChild("n55")->As<UGButton>();//kitchen button
    kitchen_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_kitchen_button);

    wc_btn = bList_comp->GetChild("n60")->As<UGButton>();//wc button
    wc_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_wc_button);

    //make_pic_button->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_make_pic_button);

    //bList->OnClickChild("s_btn", &UDemoTreeView::OnClick_s_btn);


    ///.................................................................pList Initialization (product list)
    pListComp = Comp->GetChild("n43")->As<UGComponent>();//get pList componenet
    pList = pListComp->GetChild("n10")->As<UGList>();//get pList
    pList_c1 = Comp->GetController("pList_c1");//get pList controller
    //.....................................................................Query input box in pList

    UGComponent* product_id_comp = pListComp->GetChild("n9")->As<UGComponent>();
    product_id_TextInput = product_id_comp->GetChild("n0")->As<UGTextInput>();//get input box
    product_id_TextInput->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_product_id_TextInput);

    //.............................................................test button
    input_btn = pListComp->GetChild("n29")->As<UGButton>();
    input_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_product_id_TextInput);

    search_btn = pListComp->GetChild("n12")->As<UGButton>();//get search button
    search_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_search_btn);

    //Initialize keyboard component
    keyboardComp = Comp->GetChild("n50")->As<UGComponent>();
    A_btn = keyboardComp->GetChild("n0")->As<UGButton>();
    B_btn = keyboardComp->GetChild("n3")->As<UGButton>();
    C_btn = keyboardComp->GetChild("n18")->As<UGButton>();
    D_btn = keyboardComp->GetChild("n19")->As<UGButton>();
    E_btn = keyboardComp->GetChild("n20")->As<UGButton>();
    F_btn = keyboardComp->GetChild("n21")->As<UGButton>();
    G_btn = keyboardComp->GetChild("n22")->As<UGButton>();
    H_btn = keyboardComp->GetChild("n23")->As<UGButton>();
    I_btn = keyboardComp->GetChild("n24")->As<UGButton>();
    J_btn = keyboardComp->GetChild("n25")->As<UGButton>();
    K_btn = keyboardComp->GetChild("n35")->As<UGButton>();
    L_btn = keyboardComp->GetChild("n36")->As<UGButton>();
    M_btn = keyboardComp->GetChild("n41")->As<UGButton>();
    N_btn = keyboardComp->GetChild("n40")->As<UGButton>();
    O_btn = keyboardComp->GetChild("n32")->As<UGButton>();
    P_btn = keyboardComp->GetChild("n33")->As<UGButton>();
    Q_btn = keyboardComp->GetChild("n26")->As<UGButton>();
    R_btn = keyboardComp->GetChild("n28")->As<UGButton>();
    S_btn = keyboardComp->GetChild("n34")->As<UGButton>();
    T_btn = keyboardComp->GetChild("n29")->As<UGButton>();
    U_btn = keyboardComp->GetChild("n31")->As<UGButton>();
    V_btn = keyboardComp->GetChild("n39")->As<UGButton>();
    W_btn = keyboardComp->GetChild("n27")->As<UGButton>();
    X_btn = keyboardComp->GetChild("n38")->As<UGButton>();
    Y_btn = keyboardComp->GetChild("n30")->As<UGButton>();
    Z_btn = keyboardComp->GetChild("n37")->As<UGButton>();

    one_btn = keyboardComp->GetChild("n5")->As<UGButton>();
    two_btn = keyboardComp->GetChild("n9")->As<UGButton>();
    three_btn = keyboardComp->GetChild("n10")->As<UGButton>();
    four_btn = keyboardComp->GetChild("n12")->As<UGButton>();
    five_btn = keyboardComp->GetChild("n14")->As<UGButton>();
    six_btn = keyboardComp->GetChild("n13")->As<UGButton>();
    seven_btn = keyboardComp->GetChild("n11")->As<UGButton>();
    eight_btn = keyboardComp->GetChild("n15")->As<UGButton>();
    nine_btn = keyboardComp->GetChild("n16")->As<UGButton>();
    zero_btn = keyboardComp->GetChild("n17")->As<UGButton>();

    back_btn = keyboardComp->GetChild("n46")->As<UGButton>();
    down_btn = keyboardComp->GetChild("n44")->As<UGButton>();

    keyboard_c1 = Comp->GetController("keyboard_c1");//keyboard controller
    A_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    B_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    C_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    D_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    E_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    F_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    G_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    H_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    I_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    J_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    K_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    L_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    M_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    N_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    O_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    P_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    Q_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    R_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    S_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    T_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    U_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    V_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    W_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    X_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    Y_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    Z_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);

    one_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    two_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    three_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    four_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    five_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    six_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    seven_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    eight_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    nine_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    zero_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    back_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    down_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_Keyboard_button);
    //Query all tile icons from the hard disk and put them into the array
    t_image_id = AMyActor::findData_image_total();
    //Number of all tile icons
    count = t_image_id.Num();

    t_image_id.Add("JYT001");
    t_image_id.Add("JYT002");
    t_image_id.Add("JYT003");
    t_image_id.Add("JYT004");

    count = 4;
    //............................pList
    //render pList
    pList->SetItemRenderer(FListItemRenderer::CreateUObject(this, &UDemoTreeView::RenderPListItem));
    pList->SetNumItems(count);//Set the number of elements in the pList
    pList->On(FUIEvents::ClickItem).AddUObject(this, &UDemoTreeView::__pList_clickItem);//Click event of pList

    //............................scheme

    fTab = Comp->GetChild("n3")->As<UGComponent>();//scheme componenet
    fTab_c1 = Comp->GetController("fTab_c1");//scheme controller
    main = fTab->GetController("main");//First layer main controller

    //...................button in scheme
    //confirm button
    make_pic_button = fTab->GetChild("n19")->As<UGButton>();//confirm button:Making flower slices
    make_pic_button->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_make_pic_button);
    //close button
    quit_button = fTab->GetChild("n18")->As<UGButton>();
    quit_button->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_quit_button);
    //clear button
    clear_button = fTab->GetChild("n66")->As<UGButton>();
    clear_button->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_clear_button);

    //.........................................................................Left side of scheme
    fList1 = fTab->GetChild("n12")->As<UGList>();//Get pattern - single brick list
    fList1->On(FUIEvents::ClickItem).AddUObject(this, &UDemoTreeView::__fList_clickItem);
    fList2 = fTab->GetChild("n16")->As<UGList>();//Get pattern - patchwork list
    fList2->On(FUIEvents::ClickItem).AddUObject(this, &UDemoTreeView::__fList_clickItem);


    //.........................................................................Right side of the scheme
    pList_select = fTab->GetChild("n23")->As<UGList>();//Product selection list in the pattern on the right side of the scheme
    pList_select->On(FUIEvents::ClickItem).AddUObject(this, &UDemoTreeView::__pList_select_clickItem);//Click event on the right side of the scheme
    t_width_TextInput = fTab->GetChild("t_width")->As<UGTextInput>();//Text input box: select tile width
    t_height_TextInput = fTab->GetChild("t_height")->As<UGTextInput>();//Text input box: select tile height
    chang_up_btn = fTab->GetChild("n141")->As<UGButton>();//"Long" up button
    chang_down_btn = fTab->GetChild("n139")->As<UGButton>();//"Long" down button
    chang_up_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_chang_up_button);
    chang_down_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_chang_down_button);
    kuan_up_btn = fTab->GetChild("n144")->As<UGButton>();//"width" up button
    kuan_down_btn = fTab->GetChild("n145")->As<UGButton>();//"width" down button
    kuan_up_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_kuan_up_button);
    kuan_down_btn->OnClick.AddUniqueDynamic(this, &UDemoTreeView::OnClick_kuan_down_button);
    /*
    UUIPackage::AddPackage(TEXT("/Game/UI/TreeView"), this);

    MainView = UUIPackage::CreateObject("TreeView", "Main", this)->As<UGComponent>();
    MainView->MakeFullScreen();
    MainView->SetParentToRoot();

    Tree1 = MainView->GetChild("tree")->As<UGTree>();
    Tree1->On(FUIEvents::ClickItem).AddUObject(this, &UDemoTreeView::OnClickNode);

    Tree2 = MainView->GetChild("tree2")->As<UGTree>();
    Tree2->On(FUIEvents::ClickItem).AddUObject(this, &UDemoTreeView::OnClickNode);
    Tree2->SetTreeNodeRenderer(FTreeNodeRenderer::CreateUObject(this, &UDemoTreeView::RenderTreeNode));

    UGTreeNode* TopNode = UGTreeNode::CreateNode(true);
    TopNode->UserData = FString("I'm a top node");
    Tree2->GetRootNode()->AddChild(TopNode);
    for (int32 i = 0; i < 5; i++)
    {
        UGTreeNode* Node = UGTreeNode::CreateNode();
        Node->UserData = FString("Hello " + FString::FromInt(i));
        TopNode->AddChild(Node);
    }

    UGTreeNode* AFolderNode = UGTreeNode::CreateNode(true);
    AFolderNode->UserData = FString("A folder node");
    TopNode->AddChild(AFolderNode);
    for (int32 i = 0; i < 5; i++)
    {
        UGTreeNode* Node = UGTreeNode::CreateNode();
        Node->UserData = FString("Good " + FString::FromInt(i));
        AFolderNode->AddChild(Node);
    }

    for (int32 i = 0; i < 3; i++)
    {
        UGTreeNode* Node = UGTreeNode::CreateNode();
        Node->UserData = FString("World " + FString::FromInt(i));
        TopNode->AddChild(Node);
    }

    SpecialNode = UGTreeNode::CreateNode();
    SpecialNode->UserData = FString("I'm a top node too");
    Tree2->GetRootNode()->AddChild(SpecialNode);
    */
}

void UDemoTreeView::RenderPListItem(int32 index, UGObject* obj)
{
    FString image_id = t_image_id[index];
    FString icon_address = "/Game/CityColor/Icons/" + t_image_id[index] + "." + t_image_id[index];
    UGButton* item = obj->As<UGButton>();
    item->GetChild("title")->SetText(image_id);
    item->SetIcon(icon_address);
}

void UDemoTreeView::RenderPListSearchItem(int32 index, UGObject* obj)
{
    FString searchImageId = search_image_id;
    FString icon_address = "/Game/Icons/" + searchImageId + "." + searchImageId;
    UGButton* item = obj->As<UGButton>();
    item->GetChild("title")->SetText(searchImageId);
    item->SetIcon(icon_address);
}


void UDemoTreeView::RenderPListSelectItem(int32 index, UGObject* obj)
{
    UGButton* button = obj->As<UGButton>();


    if (index != 0)
    {
        button->SetTouchable(false);
    }

    if (style == "f" || style == "p")
    {
        button->GetChild("title")->SetText("0*0mm");

    }



}
void UDemoTreeView::__bList_clickItem(UEventContext* Context)
{
    //
    UGButton* item = Cast<UGButton>(Context->GetData().AsUObject());
    const FString& name = item->GetTitle();
    FString fname = *name;

    UE_LOG(LogTemp, Warning, TEXT(""));
    if (fname == TEXT("room_btn"))//room button
    {
        Init_Controller("room");//Room Popup
    }
    else if (fname == TEXT("s_btn"))//Scheme button
    {
        Init_Controller("fangan");//Scheme Popup

    }
    else if (fname == TEXT("c_btn"))//camera button
    {
        Init_Controller("ChangeView"); //camera change
    }
    else if (fname == TEXT("r_btn"))//rotate button
    {
        Init_Controller("rotate");//rotate on
    }
    else if (fname == TEXT("copy_btn"))//copy button
    {
        Init_Controller("copy"); //copy on
    }
    else if (fname == TEXT("del_btn"))//delete button
    {
        Init_Controller("delete");//delete on
    }
    else if (fname == TEXT("u_btn"))//Undo button
    {
        //Initialize all values of myactor
        Init_Myactor();
        //Initialize bList
        Init_Controller("cancel");
        //First person initialization is located in the living room
        current_room = 0;
        current_cam = -1;
        Change_View();
    }

}
//living room click button
void UDemoTreeView::OnClick_livingroom_button(UEventContext* Context)
{
    current_cam = -1;//The current number of cameras is set to 0
    current_room = 0;//The current room is the living room
    Change_View();//change camera to another
}
//bed room click button
void UDemoTreeView::OnClick_bedroom_button(UEventContext* Context)
{
    current_cam = -1;//The current number of cameras is set to 0
    current_room = 1;//The current room is the bed room
    Change_View();//change camera to another
}
//kitchen room click button
void UDemoTreeView::OnClick_kitchen_button(UEventContext* Context)
{
    current_cam = -1;//The current number of cameras is set to 0
    current_room = 2;//The current room is the kitchen room
    Change_View();//change camera to another
}
//wc room click button
void UDemoTreeView::OnClick_wc_button(UEventContext* Context)
{
    current_cam = -1;//The current number of cameras is set to 0
    current_room = 3;//The current room is the wc room
    Change_View();//change camera to another
}

//Click event of query button in pList
void UDemoTreeView::OnClick_search_btn(UEventContext* Context)
{
    search_image_id = product_id_TextInput->GetText();
    if (t_image_id.Contains(search_image_id))
    {
        //render pList     
        pList->SetItemRenderer(FListItemRenderer::CreateUObject(this, &UDemoTreeView::RenderPListSearchItem));
        pList->SetNumItems(1);//Number of elements in pList
    }

}

//Text input box click event in pList
void  UDemoTreeView::OnClick_product_id_TextInput(UEventContext* Context)
{
    keyboard_c1->SetSelectedIndex(1);//Keyboard popup
    current_TextInput = product_id_TextInput;//The current input box is the product ID input box
}
void UDemoTreeView::__fList_clickItem(UEventContext* Context)
{
    UGButton* item = Cast<UGButton>(Context->GetData().AsUObject());
    const FString& name = item->GetTitle();
    floor_id = *name;//Flower pattern id
    Init_you(floor_id);//initialize right side of scheme


}
//On the right side of the scheme, click the event in the detail area of the pattern
void UDemoTreeView::__pList_select_clickItem(UEventContext* Context)
{
    UGButton* button = Cast<UGButton>(Context->GetData().AsUObject());
    const FString& name = button->GetTitle();


    UE_LOG(LogTemp, Warning, TEXT(""));
    current_pList_select_button = button;//assignment the currently selected button  pItem_select 
    pList_c1->SetSelectedIndex(1);//pList popup

    //Index number of currently selected pItem_select
    current_pList_select_index = FCString::Atoi(*button->GetName());
    current_pList_select_index = current_pList_select_index + 1;
    if (current_pList_select_index > (floor_num - 1))
    {
        current_pList_select_index = 0;//If the next alternative button exceeds, return to 0
        next_pList_select_button = nullptr;
    }
    else
    {
        next_pList_select_button = pList_select->GetChildAt(current_pList_select_index)->As<UGButton>();//assignment the next alternative button 
    }
}
//click event of pList
void UDemoTreeView::__pList_clickItem(UEventContext* Context)
{

    pList_c1->SetSelectedIndex(0);//pList收回
    UGButton* button = Cast<UGButton>(Context->GetData().AsUObject());
    //Get the title of the selected button in plist
    const FString& name = button->GetChild("title")->GetText();
    current_image_id = *name;//get the selected image_id

    FString icon_address = TEXT("/Game/Icons/") + current_image_id + TEXT(".") + current_image_id;

    brick_width = t_width_TextInput->GetText();//Get the selected tile width
    brick_height = t_height_TextInput->GetText();//Get the selected tile height
    //On the right side of the scheme, select the tile details button to assign values: style：CT8073AS  600*600
    current_pList_select_button->GetChild("title")->SetText(current_image_id + "\n" + brick_width + "*" + brick_height);
    current_pList_select_button->SetIcon(icon_address);
    //Obtain the width and height of the selected tiles, converted from centimeters to meters
    float i_brick_width = FCString::Atof(*brick_width) / 1000;
    float i_brick_height = FCString::Atof(*brick_height) / 1000;
    //Get the width and height of the selected tiles, and convert them from float to string
    brick_width = FString::SanitizeFloat(i_brick_width);
    brick_height = FString::SanitizeFloat(i_brick_height);
    //image_id style：CT8073AS-0-0-1.2-0.6-1.2-0.6-0-2
    FString image_id = current_image_id + "-0-0-" + brick_width + "- " + brick_height + "- " + brick_width + "- " + brick_height + "- 0 - 2";
    //seleted image_id style added to l_image_id array
    l_image_id.Add(image_id);
    //Current alternative button is invalid
    current_pList_select_button->SetTouchable(false);
    //Activate next alternate button
    if (next_pList_select_button)
    {
        next_pList_select_button->SetTouchable(true);
    }

}
void UDemoTreeView::Init_you(FString floorId)
{
    pList_select->RemoveChildren();
    style = floorId.Left(1);//Take out the first letter pattern：f
    floor_num = FCString::Atoi(*(floorId.Mid(1, 1)));//Take out the number of flower pieces of the second letter：1
    pList_select->SetItemRenderer(FListItemRenderer::CreateUObject(this, &UDemoTreeView::RenderPListSelectItem));
    pList_select->SetNumItems(floor_num);//Set the number of elements in the list
}
//Keyboard button click event
void UDemoTreeView::OnClick_Keyboard_button(UEventContext* Context)
{
    UGButton* button = Cast<UGButton>(Context->GetSender());
    //Get the name of the key
    FString key = button->GetTitle();
    //Get the text of the current input box
    FString current_text = current_TextInput->GetText();
    if (key == "back")
    {
        int len = current_text.Len();
        current_text = current_text.Left(len - 1);
    }
    else if (key == "down")
    {
        keyboard_c1->SetSelectedIndex(0);//Keyboard retraction
    }
    else
    {
        current_text = current_text + key;
    }
    current_TextInput->SetText(current_text);
}


//"width" down arrow button click event
void UDemoTreeView::OnClick_chang_down_button(UEventContext* Context)
{
    //Length of tile size array
    int _count = floor_size.Num();
    //Number of the next number
    int _next = 0;
    //Get the text of the tile length input box
    FString current_text = t_width_TextInput->GetText();
    //The next text displayed in the tile length input box
    FString next_text = "";

    //foreach array
    for (int x = 0; x < _count; x++)
    {
        if (current_text == floor_size[x])
        {
            if ((x - 1) < 0)
            {
                _next = _count - 1;
            }
            else
            {
                _next = x - 1;
            }
            next_text = floor_size[_next];
            t_width_TextInput->SetText(next_text);
            return;
        }
        else
        {
            next_text = floor_size[0];
        }

    }
    t_width_TextInput->SetText(next_text);
}
//"width" up arrow button click event
void UDemoTreeView::OnClick_chang_up_button(UEventContext* Context)
{
    //Length of tile size array
    int _count = floor_size.Num();
    //Number of the next number
    int _next = 0;
    //Get the text of the tile length input box
    FString current_text = t_width_TextInput->GetText();
    //The next text displayed in the tile length input box
    FString next_text = "";

    //foreach array
    for (int x = 0; x < _count; x++)
    {
        if (current_text == floor_size[x])
        {
            if ((x + 1) == _count)
            {
                _next = 0;
            }
            else
            {
                _next = x + 1;
            }
            next_text = floor_size[_next];
            t_width_TextInput->SetText(next_text);
            return;
        }
        else
        {
            next_text = floor_size[0];
        }

    }
    t_width_TextInput->SetText(next_text);
}

//"height" down arrow button click event
void UDemoTreeView::OnClick_kuan_down_button(UEventContext* Context)
{
    //Length of tile size array
    int _count = floor_size.Num();
    //Number of the next number
    int _next = 0;
    //Get the text of the tile height input box
    FString current_text = t_height_TextInput->GetText();
    //The next text displayed in the tile height input box
    FString next_text = "";

    //foreach array
    for (int x = 0; x < _count; x++)
    {
        if (current_text == floor_size[x])
        {
            if ((x - 1) < 0)
            {
                _next = _count - 1;
            }
            else
            {
                _next = x - 1;
            }
            next_text = floor_size[_next];
            t_height_TextInput->SetText(next_text);
            return;
        }
        else
        {
            next_text = floor_size[0];
        }

    }
    t_height_TextInput->SetText(next_text);
}
//"height" up arrow button click event
void UDemoTreeView::OnClick_kuan_up_button(UEventContext* Context)
{
    //Length of tile size array
    int _count = floor_size.Num();
    //Number of the next number
    int _next = 0;
    //Get the text of the tile height input box
    FString current_text = t_height_TextInput->GetText();
    //The next text displayed in the tile height input box
    FString next_text = "";

    //foreach array
    for (int x = 0; x < _count; x++)
    {
        if (current_text == floor_size[x])
        {
            if ((x + 1) == _count)
            {
                _next = 0;
            }
            else
            {
                _next = x + 1;
            }
            next_text = floor_size[_next];
            t_height_TextInput->SetText(next_text);
            return;
        }
        else
        {
            next_text = floor_size[0];
        }

    }
    t_height_TextInput->SetText(next_text);
}




//confirm button
void UDemoTreeView::OnClick_make_pic_button(UEventContext* Context)
{
    //Generate flower pieces
    MakePic();
    //Close scheme
    fTabQuit();

}
//Close button click event of scheme
void UDemoTreeView::OnClick_quit_button(UEventContext* Context)
{
    fTabQuit();
}
//Clear button click event of scheme
void UDemoTreeView::OnClick_clear_button(UEventContext* Context)
{
    Init_you(floor_id);//initialize right side of  scheme
    l_image_id.Empty();//Empty the selected tile array
}

//Functions used by the close button in the scheme
void UDemoTreeView::fTabQuit()
{
    pList_c1->SetSelectedIndex(0);//pList take back
    fTab_c1->SetSelectedIndex(0);//fTab take back
    Clear_you_select();//清空方案右侧
    l_image_id.Empty();//Empty the selected tile array
}


void UDemoTreeView::OnDemoEnd_Implementation()
{
    UUIPackage::RemovePackage("Main", this);
    //UUIPackage::RemovePackage("TreeView", this);
}

/*
void UDemoTreeView::OnClickNode(UEventContext* Context)
{
    UGTreeNode* Node = Cast<UGObject>(Context->GetData().AsUObject())->GetTreeNode();
    UE_LOG(LogFairyGUI, Warning, TEXT("click node %s"), *Node->GetText());
}

void UDemoTreeView::RenderTreeNode(UGTreeNode* Node, UGComponent* Obj)
{
    if (Node->IsFolder())
    {
        Obj->SetText(Node->UserData.AsString());
    }
    else
    {
        if (Node == SpecialNode)
            Obj->SetIcon("ui://TreeView/heart");
        else
            Obj->SetIcon("ui://TreeView/file");
        Obj->SetText(Node->UserData.AsString());
    }
}
*/

AActor* UDemoTreeView::TongXin()
{
    TSubclassOf<AMyActor> classToFind;
    classToFind = AMyActor::StaticClass();
    TArray<AActor*> foundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundEnemies);

    AActor* amyactor = foundEnemies[0];
    //NotifyActorBeginOverlap(myactor, Texture);
    return amyactor;
}
//Test before generating flower pieces
bool UDemoTreeView::CheckMakePic()
{
    //Get the Value of global variable double_tap_object in MyActor    
    AStaticMeshActor* doubleTapObject = GetDoubleTapObject(myactor);
    if (doubleTapObject == nullptr)
    {
        Show_Alert(TEXT("Tip: please choose an object with replaceable material！"));
        return false;
    }

    if (floor_id == "")
    {
        Show_Alert(TEXT("Tip: please choose the pattern of parquet！"));
        return false;
    }

    if ((floor_id == "f101" && (l_image_id.Num() < 1)) || (floor_id == "p204" && (l_image_id.Num() < 2)))
    {
        Show_Alert(TEXT("Tip: the number of tiles you choose is not enough！"));
        return false;
    }
    return true;

}
//Check whether the number of selected tile pictures is sufficient
void UDemoTreeView::CheckFloorNumSelected()
{
    if (floor_id == "f101")
    {
        if (l_image_id.Num() < 1)//To avoid insufficient bricks for the return type selection, click the OK button
        {
            Show_Alert("Tip: insufficient ceramic tiles！");
            return;
        }
    }
}

//Making flower slices
void UDemoTreeView::MakePic()
{
    UTexture2D* tex = nullptr;
    UTexture* u_tex = nullptr;
    float Width = 0;
    float Height = 0;
    float width = 0;
    float height = 0;

    //Check before generating flower pieces: 1. Whether replaceable material objects are selected; 2. Whether the number of selected ceramic tile pictures is sufficient
    if (CheckMakePic() == false)
    {
        return;
    }
    else
    {
        //get the width and height of the double click object
        width = GetWidth(myactor) / 100;
        height = GetHeight(myactor) / 100;

        //get double_tap_object        
        AStaticMeshActor* doubleTapObject = GetDoubleTapObject(myactor);

        if (floor_id == "f101")//Tile
        {
            //Generate a tile map in the format of utexture2d*, where the variables tex, width and height can be null, and width and height are the width and height of the object obtained by double clicking
            tex = (AMyActor::LoadImageToTexture2D(l_image_id, floor_id, tex, Width, Height, width, height));
            //UTexture2D switch to UTexture
            u_tex = (UTexture*)tex;
            //Dynamically call the SetMat function in myactor to change the material of the floor, and 2 means to change the texture
            SetMat(myactor, doubleTapObject, u_tex, 2);
        }
        else if (floor_id == "f105")//Tile
        {
            //Generate a tile map in the format of utexture2d*, where the variables tex, width and height can be null, and width and height are the width and height of the object obtained by double clicking
            tex = (AMyActor::LoadImageToTexture2D(l_image_id, floor_id, tex, Width, Height, width, height));
            //UTexture2D switch to UTexture
            u_tex = (UTexture*)tex;
            //Dynamically call the SetMat function in myactor to change the material of the floor, and 2 means to change the texture
            SetMat(myactor, doubleTapObject, u_tex, 2);
        }
        else if (floor_id == "p204")//Parquet p204
        {
            tex = (AMyActor::LoadImageToTexture2D(l_image_id, floor_id, tex, Width, Height, width, height));
            u_tex = (UTexture*)tex;
            SetMat(myactor, doubleTapObject, u_tex, 2);
        }


        //Clear parameters in myactor
        SetWidth(myactor, 0);
        SetHeight(myactor, 0);
        SetDoubleTapObject(myactor, nullptr);
        SetIndexOfChangeObject(myactor, 0);

    }


}



void UDemoTreeView::SetMat(AActor* OtherActor, AStaticMeshActor* doubleTapObject, UTexture* Texture, int _style)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setInt();
        RotatingActorCheck->setMat(doubleTapObject, Texture, _style);//2 means to change the material, and 4 means to rotate the main material       
    }
}


//Get the number of cameras in the living room
void UDemoTreeView::GetLivingRoomCamCount(AActor* OtherActor)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        count_livingroom_cam = RotatingActorCheck->getLivingRoomCamCount();
    }
}
//Get the number of cameras in the bed room
void UDemoTreeView::GetBedRoomCamCount(AActor* OtherActor)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        count_bedroom_cam = RotatingActorCheck->getBedRoomCamCount();
    }
}
//Get the number of cameras in the kitchen room
void UDemoTreeView::GetKitchenCamCount(AActor* OtherActor)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        count_kitchen_cam = RotatingActorCheck->getKitchenCamCount();
    }
}
//Get the number of cameras in the wc room
void UDemoTreeView::GetWCCamCount(AActor* OtherActor)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        count_wc_cam = RotatingActorCheck->getWCCamCount();
    }
}

// the id of camera +1. If it is greater than the total number of cameras, it will return to 0
void UDemoTreeView::Add_Cam(int amount_cam)
{
    current_cam = current_cam + 1;
    if (current_cam > (amount_cam - 1))
    {
        current_cam = 0;
    }
}
//camera switch
void UDemoTreeView::Change_View()
{

    float rotation;
    FTransform location;
    TArray<int> t_dirction;

    if (current_room == 0)//livingroom
    {
        //change view
        Add_Cam(count_livingroom_cam);
        //Get the position, angle and direction signs of the first person in the living room
        location = GetLivingroomLocation(myactor, current_cam);
        rotation = GetLivingroomRotation(myactor, current_cam);
        t_dirction = GetLivingroomDirection(myactor);
    }
    else if (current_room == 1)//bedroom
    {

        Add_Cam(count_bedroom_cam);
        location = GetBedroomLocation(myactor, current_cam);
        rotation = GetBedroomRotation(myactor, current_cam);
        t_dirction = GetBedroomDirection(myactor);
    }
    else if (current_room == 2)//kitchen
    {
        Add_Cam(count_kitchen_cam);
        location = GetKitchenLocation(myactor, current_cam);
        rotation = GetKitchenRotation(myactor, current_cam);
        t_dirction = GetKitchenDirection(myactor);
    }
    else if (current_room == 3)//wc
    {
        Add_Cam(count_wc_cam);
        location = GetWCLocation(myactor, current_cam);
        rotation = GetWCRotation(myactor, current_cam);
        t_dirction = GetWCDirection(myactor);
    }
    //Get the current angle
    float curren_rotation = pawn->GetControlRotation().Yaw;
    //Target angle - current angle / default conversion scale
    float delta_rotation = (rotation - curren_rotation) / 2.5f;
    pawn->SetActorTransform(location, false, nullptr, ETeleportType::TeleportPhysics);
    //Character rotation
    pawn->AddControllerYawInput(delta_rotation);
    //Set current direction sign
    SetCurrentDirection(myactor, current_cam, t_dirction);

}





//FTransform UDemoTreeView::GetLocation(AActor* OtherActor, int index)
//{
//    FTransform location ;
//    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
//    {
//        location = RotatingActorCheck->getLocation(index);
//    }
//    return location;
//}

FTransform UDemoTreeView::GetLivingroomLocation(AActor* OtherActor, int index)
{
    FTransform location;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        location = RotatingActorCheck->getLivingroomLocation(index);
    }
    return location;
}

float UDemoTreeView::GetLivingroomRotation(AActor* OtherActor, int index)
{
    float rotation;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        rotation = RotatingActorCheck->getLivingroomRotation(index);
    }
    return rotation;
}

TArray<int> UDemoTreeView::GetLivingroomDirection(AActor* OtherActor)
{
    TArray<int> livingroomDirection;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        livingroomDirection = RotatingActorCheck->getLivingroomDirection();
    }
    return livingroomDirection;
}


FTransform UDemoTreeView::GetBedroomLocation(AActor* OtherActor, int index)
{
    FTransform location;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        location = RotatingActorCheck->getBedroomLocation(index);
    }
    return location;
}

float UDemoTreeView::GetBedroomRotation(AActor* OtherActor, int index)
{
    float rotation;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        rotation = RotatingActorCheck->getBedroomRotation(index);
    }
    return rotation;
}

TArray<int> UDemoTreeView::GetBedroomDirection(AActor* OtherActor)
{
    TArray<int> bedroomDirection;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        bedroomDirection = RotatingActorCheck->getBedroomDirection();
    }
    return bedroomDirection;
}


FTransform UDemoTreeView::GetKitchenLocation(AActor* OtherActor, int index)
{
    FTransform location;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        location = RotatingActorCheck->getKitchenLocation(index);
    }
    return location;
}

float UDemoTreeView::GetKitchenRotation(AActor* OtherActor, int index)
{
    float rotation;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        rotation = RotatingActorCheck->getKitchenRotation(index);
    }
    return rotation;
}

TArray<int> UDemoTreeView::GetKitchenDirection(AActor* OtherActor)
{
    TArray<int> kitchenDirection;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        kitchenDirection = RotatingActorCheck->getKitchenDirection();
    }
    return kitchenDirection;
}


FTransform UDemoTreeView::GetWCLocation(AActor* OtherActor, int index)
{
    FTransform location;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        location = RotatingActorCheck->getWCLocation(index);
    }
    return location;
}

float UDemoTreeView::GetWCRotation(AActor* OtherActor, int index)
{
    float rotation;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        rotation = RotatingActorCheck->getWCRotation(index);
    }
    return rotation;
}

TArray<int> UDemoTreeView::GetWCDirection(AActor* OtherActor)
{
    TArray<int> wcDirection;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        wcDirection = RotatingActorCheck->getWCDirection();
    }
    return wcDirection;
}





float UDemoTreeView::GetWidth(AActor* OtherActor)
{
    float width = 0;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {

        width = RotatingActorCheck->getWidth();
    }
    return width;
}
float UDemoTreeView::GetHeight(AActor* OtherActor)
{
    float height = 0;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {

        height = RotatingActorCheck->getHeight();
    }
    return height;
}

void UDemoTreeView::SetWidth(AActor* OtherActor, float objectWidth)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setWidth(objectWidth);
    }
}
void UDemoTreeView::SetHeight(AActor* OtherActor, float objectHeight)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setHeight(objectHeight);
    }
}



TArray<AStaticMeshActor*> UDemoTreeView::GetChangeObject(AActor* OtherActor)
{
    TArray<AStaticMeshActor*> change_object;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {

        change_object = RotatingActorCheck->getChangeObject();
    }
    return change_object;
}

void UDemoTreeView::InitD_mat(AActor* OtherActor, int CountChangeObject)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->initD_mat(CountChangeObject);
    }
}


void UDemoTreeView::InitChangeObjectDMat(AActor* OtherActor)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->initChangeObjectDMat();
    }
}


void UDemoTreeView::SetIndexOfChangeObject(AActor* OtherActor, int indexOfChangeObject)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setIndexOfChangeObject(indexOfChangeObject);
    }
}


void UDemoTreeView::SetCopyMat(AActor* OtherActor, UMaterialInstanceDynamic* copyMat)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setCopyMat(copyMat);
    }
}




void UDemoTreeView::InitIf_change(AActor* OtherActor, int CountChangeObject)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->initIf_change(CountChangeObject);
    }
}


AStaticMeshActor* UDemoTreeView::GetDoubleTapObject(AActor* OtherActor)
{
    AStaticMeshActor* doubleTapObject = nullptr;
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        doubleTapObject = RotatingActorCheck->getDoubleTapObject();
    }
    return doubleTapObject;
}

void UDemoTreeView::SetDoubleTapObject(AActor* OtherActor, AStaticMeshActor* doubleTapObject)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setDoubleTapObject(doubleTapObject);
    }
}

void UDemoTreeView::SetTapObject(AActor* OtherActor, AStaticMeshActor* TapObject)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setTapObject(TapObject);
    }
}


void UDemoTreeView::SetCopyObject(AActor* OtherActor, AStaticMeshActor* copyObject)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setCopyObject(copyObject);
    }
}


void UDemoTreeView::SetCurrentDirection(AActor* OtherActor, int cam, TArray<int> t_dirction)
{
    if (AMyActor* RotatingActorCheck = Cast<AMyActor>(OtherActor))
    {
        RotatingActorCheck->setCurrentDirection(t_dirction[cam]);
    }
}




void UDemoTreeView::Clear_you_select()
{
    pList_select->RemoveChildren();
}

void UDemoTreeView::Show_Alert(FString s_result)
{
    alert_btn->SetText(s_result);
    alert_c1->SetSelectedIndex(1);//alert popup

    //Close the warning window after 2 seconds
    GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UDemoTreeView::Close_Alert, 1.0f, true, 2.0f);

}

void UDemoTreeView::Close_Alert()
{
    alert_c1->SetSelectedIndex(0);//Close warning window
    GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);//Reset the timer to 0 and retime
}

//双击初始化bList的控制器

void UDemoTreeView::Init_bList()
{
    room = false;
    move = false;
    rotate = false;

    del = false;
    describe = false;
    cancel = false;
    i_rotate = 0;//关闭旋转主材45度
    i_copy = 0;//关闭复制主材

    room_c1->SetSelectedIndex(0);//切换房间收回

    Init_bList_All_Button();//bList中所有按钮处于未选中状态
}
//bList中按钮高亮或者取消高亮
void UDemoTreeView::Init_Button(FString fname, int _style)
{
    //循环bList所有item
    for (int i = 0; i < bList->GetNumItems(); i++)
    {
        UGButton* button = bList->GetChildAt(i)->As<UGButton>();
        const FString& name = button->GetTitle();

        if (*name == fname)
        {
            UGController* c1 = button->GetController("button");
            c1->SetSelectedIndex(_style);//取消高亮
        }
    }
}


//所有瓷砖材质恢复初始值，并销毁动态生成的图片

void UDemoTreeView::Init_Myactor()
{
    //还原材质；清空d_mat；if_change归0
    UTexture* u_tex = nullptr;//材质贴图付空值   
    //循环change_object数组
    for (int i = 0; i < count_change_object; i++)
    {
        //获得MyActor中全局变量double_tap_object的值         
        AStaticMeshActor* doubleTapObject = t_change_object[i];
        SetIndexOfChangeObject(myactor, i);
        if (doubleTapObject)//防止用户直接点击删除按钮
        {
            //动态调用myactor中setMat函数给地板更换材质,0表示还原材质球
            SetMat(myactor, doubleTapObject, u_tex, 0);
        }
    }
    //清空Myactor中的参数
    SetWidth(myactor, 0);
    SetHeight(myactor, 0);
    SetDoubleTapObject(myactor, nullptr);
    SetTapObject(myactor, nullptr);
    SetCopyObject(myactor, nullptr);
    SetIndexOfChangeObject(myactor, 0);
    SetCopyMat(myactor, nullptr);
}





// bList中所有按钮处于未选中状态
void UDemoTreeView::Init_bList_All_Button()
{
    //取消所有按钮的高亮
    for (int i = 0; i < bList->GetNumItems(); i++)//循环左侧list所有item
    {
        UGButton* button = bList->GetChildAt(i)->As<UGButton>();
        UGController* c1 = button->GetController("button");
        c1->SetSelectedIndex(0);//取消所有光圈
    }
}


//initialize bList controller
void UDemoTreeView::Init_Controller(FString s_controller)
{
    room_c1->SetSelectedIndex(0);//room take back
    i_rotate = 0;//Close and rotate the main material 45 degrees
    //If copy is on, the copy button is highlighted
    if (i_copy != 0)
    {
        Init_Button("copy_btn", 1);
    }


    if (s_controller == "room")
    {
        room = !room;
        move = false;
        rotate = false;
        del = false;
        describe = false;
        if (room)
        {
            room_c1->SetSelectedIndex(1);// room popup
        }
        else
        {
            room_c1->SetSelectedIndex(0);// room take back

        }
    }


    else if (s_controller == "rotate")
    {
        rotate = !rotate;
        room = false;
        move = false;


        del = false;
        describe = false;
        cancel = false;
        if (rotate)
        {
            i_rotate = 1;//Open and rotate the main material 45 degrees                      
        }
    }

    else if (s_controller == "fangan")//scheme
    {
        room = false;
        move = false;
        rotate = false;

        del = false;
        describe = false;
        cancel = false;

        fTab_c1->SetSelectedIndex(1);//scheme popup
        main->SetSelectedIndex(0);//Pattern button click to add: the default display pattern - single brick page


    }
    else if (s_controller == "copy")//Copy wall face
    {
        if (i_copy == 0)
        {
            i_copy = 1;//Enable copy function

        }


        room = false;

        move = false;
        rotate = false;
        del = false;
        describe = false;
        cancel = false;
    }
    else if (s_controller == "delete")
    {
        //del = !del;
        room = false;
        move = false;
        rotate = false;

        describe = false;
        cancel = false;


        UTexture* u_tex = nullptr;//Empty value of material map
        //get double_tap_object        
        AStaticMeshActor* doubleTapObject = GetDoubleTapObject(myactor);
        if (doubleTapObject)//Prevent users from directly clicking the delete button
        {
            //Dynamically call the SetMat function in myactor to change the material of the floor, and 0 means to restore the shader
            SetMat(myactor, doubleTapObject, u_tex, 0);
        }


    }

    else if (s_controller == "ChangeView")
    {
        room = false;

        move = false;
        rotate = false;

        del = false;
        describe = false;
        cancel = false;
        Change_View();
    }
    else if (s_controller == "describe")//Scenario description
    {
        describe = !describe;
        room = false;
        move = false;
        rotate = false;

        del = false;
        cancel = false;
        if (describe)
        {

        }
    }

    else if (s_controller == "cancel")
    {
        cancel = !cancel;
        room = false;
        del = false;
        move = false;
        rotate = false;
        describe = false;

        i_copy = 0;//close copy
        Init_bList_All_Button();//All buttons unhighlight

    }

    else if (s_controller == "none")//all
    {
        room = false;


        move = false;
        rotate = false;

        del = false;
        describe = false;
        cancel = false;

    }
    else if (s_controller == "init")//Initial ownership, cancellation of exclusive use
    {
        room = false;
        move = false;
        rotate = false;
        del = false;
        describe = false;

    }


}






int UDemoTreeView::getIRotate()
{
    return i_rotate;
}

void UDemoTreeView::setICopy(int iCopy)
{
    i_copy = iCopy;
}

int UDemoTreeView::getICopy()
{
    return i_copy;
}

void UDemoTreeView::setComp(UGComponent* comp)
{
    Comp = comp;
}