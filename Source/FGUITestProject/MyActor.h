// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "..\..\..\..\Engine\Source\Runtime\LevelSequence\Public\LevelSequenceActor.h"
#include "ThirdParty/FreeImage/FreeImage-3.18.0/Dist/FreeImage.h"
#include "ThirdParty/Sqlite3/include/sqlite3.h"
#include "Engine/Classes/Engine/StaticMeshActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class FGUITESTPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MyInt;

	UPROPERTY(EditAnywhere)
		int Color123;
	UPROPERTY(EditAnywhere, Category = "MyActor")
		UTexture2D* tex_2d;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame

	virtual void Tick(float DeltaTime) override;







	//Array of replacement material objects in the scene
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<AStaticMeshActor*> change_object;
	UPROPERTY(EditAnywhere, Category = "MyActor")
		float object_width;// the width of the double click object
	UPROPERTY(EditAnywhere, Category = "MyActor")
		float object_height;//the height of the double click object
	//double click object
	UPROPERTY(EditAnywhere, Category = "MyActor")
		AStaticMeshActor* double_tap_object;

	//single click object
	UPROPERTY(EditAnywhere, Category = "MyActor")
		AStaticMeshActor* tap_object;

	//Copy the object of the parent material
	UPROPERTY(EditAnywhere, Category = "MyActor")
		AStaticMeshActor* copy_object;

	// Double click the object to get it index number of change_object
	UPROPERTY(EditAnywhere, Category = "MyActor")
		int index_of_change_object;
	//Original shader of replaceable material object
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<class UMaterialInterface*> change_object_mat;
	//A dynamic material copy of the original shader of a replaceable material object
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<UMaterialInstanceDynamic*> change_object_d_mat;
	//Replaceable shader
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<class UMaterialInterface*> change_mat;

	//Copy parent shader
	UPROPERTY(EditAnywhere, Category = "MyActor")
		UMaterialInstanceDynamic* copy_mat;

	//Temporary shaders, quantity equal to change_object
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<UMaterialInstanceDynamic*>  d_mat;
	//Whether the shader has been modified
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<int>  if_change;




	//First person living room location
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<FTransform>livingroom_location;
	//First person current direction signs
	UPROPERTY(EditAnywhere, Category = "MyActor")
		int current_direction;
	//First person living room angle
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<float>livingroom_rotation;
	//First person living room direction
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<int>livingroom_direction;

	//First person bed room location
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<FTransform>bedroom_location;
	//First person bed room rotation
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<float>bedroom_rotation;
	//First person bed room direction
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<int>bedroom_direction;

	//First person kitchen location
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<FTransform>kitchen_location;
	//First person kitchen rotation
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<float>kitchen_rotation;
	//First person kitchen direction
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<int>kitchen_direction;

	//First person wc location
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<FTransform>wc_location;
	//First person wc rotation
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<float>wc_rotation;
	//First person wc direction
	UPROPERTY(EditAnywhere, Category = "MyActor")
		TArray<int>wc_direction;




	UPROPERTY(EditAnywhere, Category = "MyActor")
		ALevelSequenceActor* sequence;//Main level sequence





//.........................................function

	UFUNCTION(BlueprintCallable, Category = "Picture Tool")
		static UTexture2D* LoadImageToTexture2D(TArray<FString>& ImagePath, FString floor_id, UTexture2D*& InTexture, float& Width, float& Height, float floor_width, float floor_height);

	UFUNCTION(BlueprintCallable, Category = "Picture Tool")
		static FString GetProjectDir();//Project path
	UFUNCTION(BlueprintCallable, Category = "Picture Tool")
		static FString GetPakRootDir();//Package path



	//set style
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setIfChange(int _style, int indexOfChangeObject);
	//get style
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		TArray<int> getIfChange();
	//get change_object array
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		TArray<AStaticMeshActor*> getChangeObject();
	//Double click to get the index of object'name in change_object, If  does not exist, return -1
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		int getIndexOfChangeObject(const FString& name, const TArray<AStaticMeshActor*>& changeObject);
	//set index_of_change_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setIndexOfChangeObject(int indexOfChangeObject);
	//set double_tap_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setDoubleTapObject(AStaticMeshActor* doubleTapObject);
	//get double_tap_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		AStaticMeshActor* getDoubleTapObject();


	//set copy_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setCopyObject(AStaticMeshActor* copyObject);
	//get copy_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		AStaticMeshActor* getCopyObject();



	//set tap_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setTapObject(AStaticMeshActor* tapObject);
	//get double_tap_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		AStaticMeshActor* getTapObject();

	//Initialize array d_mat,Quantity equals to change_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void initD_mat(int count);
	//Initializes a dynamic material copy of the original shader of a replaceable material object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void initChangeObjectDMat();
	//Initialize array  if_change,Quantity equals to change_object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void initIf_change(int count);

	//Get the current rotation angle of the main material of the object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		static float getRotation(const AStaticMeshActor* changeObject);

	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setMat(const AStaticMeshActor* changeObject, UTexture* Texture, int _style);

	//Save copied object parent material
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setCopyMat(UMaterialInstanceDynamic* copyMat);
	//Get the parent material of the copied object
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		UMaterialInstanceDynamic* getCopyMat(int indexOfChangeObject);


	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setInt();

	UFUNCTION(BlueprintCallable, Category = "MyActor")
		FTransform getLivingroomLocation(int index);
	//Obtain the rotation angle in the living room
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		float getLivingroomRotation(int index);
	//Get the first person living room direction sign
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		TArray<int> getLivingroomDirection();
	//set current direction
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setCurrentDirection(int direction);
	//get current direction
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		int getCurrentDirection();


	//get first person location in bedroom
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		FTransform getBedroomLocation(int index);
	//get first person rotation in bedroom
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		float getBedroomRotation(int index);
	//get first person direction in bedroom
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		TArray<int> getBedroomDirection();

	//get first person location in kitchen
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		FTransform getKitchenLocation(int index);
	//get first person rotation in kitchen
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		float getKitchenRotation(int index);
	//get first person direction in kitchen
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		TArray<int> getKitchenDirection();


	//get first person location in wc
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		FTransform getWCLocation(int index);
	//get first person rotation in wc
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		float getWCRotation(int index);
	//get first person direction in wc
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		TArray<int> getWCDirection();




	UFUNCTION(BlueprintCallable, Category = "MyActor")
		int getLivingRoomCamCount();//get the number of cameras in the living room
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		int getBedRoomCamCount();//get the number of cameras in the bed room
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		int getKitchenCamCount();//get the number of cameras in the kitchen
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		int getWCCamCount();//get the number of cameras in the wc



	UFUNCTION(BlueprintCallable, Category = "MyActor")
		UTexture2D* getTex();
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		ALevelSequenceActor* getSequence();
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setSize(AStaticMeshActor* doubleTapObject);
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		float getWidth();
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		float getHeight();

	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setWidth(float objectWidth);
	UFUNCTION(BlueprintCallable, Category = "MyActor")
		void setHeight(float objectHeight);





	static TArray<FString> findData_image_total();//Query all pictures id from the database

private:
	static bool LoadImageToData(const FString& ImagePath, TArray64<uint8>& OutData, float& Width, float& Height);
	static bool MyFunction(TArray<FString>& ImagePath, FString floor_id, TArray64<uint8>& OutData, float& Width, float& Height, float floor_width, float floor_height);


	static FIBITMAP* f101(char* image_id, float diban_width, float diban_height, int width, int height, float y_high, bool if_edge);
	static FIBITMAP* f105(char* image_id, float diban_width, float diban_height, int width, int height, float y_high, bool if_edge);
	static FIBITMAP* p2(char* src_id, char* fg_id, char* bg_id, float diban_width, float diban_height, float floor_width, float floor_height, int dst_width, int dst_height
	);


	static void charToArray(char* image_id);//Char* convert the array, and convert the string image_id segmentation, get multiple detailed pictures from the database, and cut
	static bool ratio(float diban_width, float diban_height, float floor_width, float floor_height, float d_Image_width, float d_Image_height, int width, int height);
	static void findData_image_detail(char* no);//Query the image from the hard disk and return the image uimage. The second detail is returned to the global variable image1, the third detail is returned to the global variable image2, and the fourth detail is returned to the global variable image3
	static FIBITMAP* findData_image_floor(char* no);//Query the floor image from the hard disk for mosaic
	static FIBITMAP* repeat_1_hun(TArray<FIBITMAP*> imageArray, int width, int height, float edge, BOOL if_edge);// Tile, whether there is brick joint (mixed row)

	static sqlite3* OpenDataBase(FString DataBasePath);
	static char* constchar2char(const char* str);



};
