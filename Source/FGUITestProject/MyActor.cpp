// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Runtime/Core/Public/Misc/Char.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include <string>
#include "stdio.h"
#include "io.h"
#include "Windows.h"
#include "Kismet/KismetSystemLibrary.h"


//#include "C:/Program Files(x86)/Windows Kits/10/Include\\10.0.19041.0\\um\\stringapiset.h"
//#include "C:/Program Files(x86)/Windows Kits/10/Include\\10.0.19041.0\\um\\stringapiset.h"

#include "Engine/EngineTypes.h"
//#include "D:\Program Files\Epic Games\UE_4.26\Engine/Source/Editor/MovieSceneTools/Public/AutomatedLevelSequenceCapture.h"
//#include "Runtime/MovieSceneCapture/Public/MovieSceneCaptureSettings.h"
//#include "Runtime/MovieSceneCapture/Public/MovieSceneCapture.h"
//#include "D:\\Program Files\\Epic Games\\UE_4.26\\Engine\\Plugins\\MovieScene\\SequencerScripting\\Source\\SequencerScriptingEditor\\Public\\SequencerTools.h"

#define BRICK_EDGE  1
#define BRICK_SIZE  2048
#define WOOD_SIZE  2048
#define ZHEZHAO_SIZE  512
#define BRICK_DETAIL_COUNT  3

const unsigned char* c_image1;
const unsigned char* c_image2;
const unsigned char* c_image3;
const unsigned char* c_image4;


FIBITMAP* image;
FIBITMAP* image1;
FIBITMAP* image2;
FIBITMAP* image3;
FIBITMAP* nei_Image;
float cut_width;
float cut_height;
float pic_cut_width;
float pic_cut_height;

int ratio_width, ratio_heigh;
struct stat buf;
FString project_path;

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AMyActor::GetProjectDir()
{
	FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::GameSourceDir());
	return ThePath;
}
FString AMyActor::GetPakRootDir()
{
	FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::RootDir());
	return ThePath;
}





//UTexture2D* AMyActor::LoadImageToTexture2D(const FString& ImagePath, UTexture2D*& InTexture, float& Width, float& Height, float floor_width, float floor_height)
UTexture2D* AMyActor::LoadImageToTexture2D(TArray<FString>& ImagePath, FString floor_id, UTexture2D*& InTexture, float& Width, float& Height, float floor_width, float floor_height)
{
	TArray64<uint8> OutRawData;

	//if (LoadImageToData(ImagePath, OutRawData, Width, Height))
	//Call the image calculation function and convert it to UTexture2D
	if (MyFunction(ImagePath, floor_id, OutRawData, Width, Height, floor_width, floor_height))
	{
		InTexture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
		if (InTexture)
		{

			void* TextureData = InTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, OutRawData.GetData(), OutRawData.Num());
			InTexture->PlatformData->Mips[0].BulkData.Unlock();
			InTexture->UpdateResource();
			return InTexture;
		}
	}

	return nullptr;
}

bool AMyActor::LoadImageToData(const FString& ImagePath, TArray64<uint8>& OutData, float& Width, float& Height)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (!PlatformFile.FileExists(*ImagePath))
	{
		return false;
	}
	//Get binary data of the picture
	TArray<uint8> ImageResultData;
	FFileHelper::LoadFileToArray(ImageResultData, *ImagePath);

	//Parse picture format
	FString Ex = FPaths::GetExtension(ImagePath, false);
	EImageFormat ImageFormat = EImageFormat::Invalid;
	if (Ex.Equals(TEXT("jpg"), ESearchCase::IgnoreCase) || Ex.Equals(TEXT("jpeg"), ESearchCase::IgnoreCase))
	{
		ImageFormat = EImageFormat::JPEG;
	}
	else if (Ex.Equals(TEXT("png"), ESearchCase::IgnoreCase))
	{
		ImageFormat = EImageFormat::PNG;
	}
	else if (Ex.Equals(TEXT("bmp"), ESearchCase::IgnoreCase))
	{
		ImageFormat = EImageFormat::BMP;
	}
	//Load picture processing module
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");
	//Create specific instances of different image processing classes according to different image formats
	TSharedPtr<IImageWrapper> ImageWrapperPtr = ImageWrapperModule.CreateImageWrapper(ImageFormat);
	if (ImageWrapperPtr.IsValid() && ImageWrapperPtr->SetCompressed(ImageResultData.GetData(), ImageResultData.GetAllocatedSize()))
	{
		//OutData Format independent color data
		ImageWrapperPtr->GetRaw(ERGBFormat::BGRA, 8, OutData);
		Width = ImageWrapperPtr->GetWidth();
		Height = ImageWrapperPtr->GetHeight();
		return true;
	}
	return false;
}

bool AMyActor::MyFunction(TArray<FString>& ImagePath, FString floor_id, TArray64<uint8>& OutData, float& Width, float& Height, float floor_width, float floor_height)
{
	typedef const char* (*FFreeImage_GetVersion)();
	FFreeImage_GetVersion FreeImage_GetVersion;

	typedef FREE_IMAGE_FORMAT(*FFreeImage_GetFileType)(const char* filename, int size);
	FFreeImage_GetFileType FreeImage_GetFileType;

	typedef FIBITMAP* (*FFreeImage_Load)(FREE_IMAGE_FORMAT fif, const char* filename, int flags);
	FFreeImage_Load FreeImage_Load;

	typedef FIBITMAP* (*FFreeImage_Rotate)(FIBITMAP* dib, double angle, const void* bkcolor);
	FFreeImage_Rotate FreeImage_Rotate;

	typedef BOOL(*FFreeImage_Save)(FREE_IMAGE_FORMAT fif, FIBITMAP* dib, const char* filename, int flags);
	FFreeImage_Save FreeImage_Save;

	typedef FIBITMAP* (*FFreeImage_Copy)(FIBITMAP* dib, int left, int top, int right, int bottom);
	FFreeImage_Copy FreeImage_Copy;//(coordinate sequence: left, top, right, bottom)

	typedef FIBITMAP* (*FFreeImage_Paste)(FIBITMAP* dst, FIBITMAP* src, int left, int top, int alpha);
	FFreeImage_Paste FreeImage_Paste;

	typedef unsigned(*FFreeImage_GetLine)(FIBITMAP* dib);
	FFreeImage_GetLine FreeImage_GetLine;

	typedef BYTE* (*FFreeImage_GetScanLine)(FIBITMAP* dib, int scanline);
	FFreeImage_GetScanLine FreeImage_GetScanLine;

	typedef unsigned(*FFreeImage_GetWidth)(FIBITMAP* dib);
	FFreeImage_GetWidth FreeImage_GetWidth;

	typedef unsigned(*FFreeImage_GetHeight)(FIBITMAP* dib);
	FFreeImage_GetHeight FreeImage_GetHeight;

	typedef FIBITMAP* (*FFreeImage_Rescale)(FIBITMAP* dib, int dst_width, int dst_height, FREE_IMAGE_FILTER);
	FFreeImage_Rescale FreeImage_Rescale;

	typedef FIBITMAP* (*FFreeImage_Allocate)(int width, int height, int bpp, unsigned red_mask, unsigned green_mask, unsigned blue_mask);
	FFreeImage_Allocate FreeImage_Allocate;

	typedef FIMEMORY* (*FFreeImage_OpenMemory)(BYTE* data, DWORD size_in_bytes);
	FFreeImage_OpenMemory FreeImage_OpenMemory;

	typedef FIBITMAP* (*FFreeImage_LoadFromMemory)(FREE_IMAGE_FORMAT fif, FIMEMORY* stream, int flags);
	FFreeImage_LoadFromMemory FreeImage_LoadFromMemory;

	typedef FIBITMAP* (*FFreeImage_ConvertTo32Bits)(FIBITMAP* dib);
	FFreeImage_ConvertTo32Bits FreeImage_ConvertTo32Bits;

	typedef unsigned (*FFreeImage_GetBPP)(FIBITMAP* dib);
	FFreeImage_GetBPP FreeImage_GetBPP;


	//FreeImage.dll  Library file path
	FString  fdll_path = FPaths::EngineDir() + "Binaries/ThirdParty/FreeImage/Win64/FreeImage.dll";
	const TCHAR* dll_path = *fdll_path;
	//Get handle of dll
	void* pDllHandler = FPlatformProcess::GetDllHandle(dll_path);


	//Initializing dynamic link library functions
	if (pDllHandler)
	{
		FString funcName = "FreeImage_GetVersion";
		FreeImage_GetVersion = (FFreeImage_GetVersion)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_GetVersion);
		const char* version = FreeImage_GetVersion();
		//Get picture type
		funcName = "FreeImage_GetFileType";
		FreeImage_GetFileType = (FFreeImage_GetFileType)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_GetFileType);


		//Load picture
		funcName = "FreeImage_Load";
		FreeImage_Load = (FFreeImage_Load)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_Load);

		//Rotate picture
		funcName = "FreeImage_Rotate";
		FreeImage_Rotate = (FFreeImage_Rotate)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_Rotate);
		//bitmap = FreeImage_Rotate(bitmap, 90, 0);
		//Crop picture
		funcName = "FreeImage_Copy";
		FreeImage_Copy = (FFreeImage_Copy)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_Copy);
		//FIBITMAP * tmpmap = FreeImage_Copy(bitmap, 0, 0, 1000, 1000);

		//Paste picture
		funcName = "FreeImage_Paste";
		FreeImage_Paste = (FFreeImage_Paste)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_Paste);


		//Get pixel row
		funcName = "FreeImage_GetLine";
		FreeImage_GetLine = (FFreeImage_GetLine)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_GetLine);

		//Scan pixel rows
		funcName = "FreeImage_GetScanLine";
		FreeImage_GetScanLine = (FFreeImage_GetScanLine)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_GetScanLine);

		//Get image width
		funcName = "FreeImage_GetWidth";
		FreeImage_GetWidth = (FFreeImage_GetWidth)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_GetWidth);

		//Get image height
		funcName = "FreeImage_GetHeight";
		FreeImage_GetHeight = (FFreeImage_GetHeight)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_GetHeight);

		//image compression
		funcName = "FreeImage_Rescale";
		FreeImage_Rescale = (FFreeImage_Rescale)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_Rescale);

		//Create image
		funcName = "FreeImage_Allocate";
		FreeImage_Allocate = (FFreeImage_Allocate)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_Allocate);

		//Save picture
		funcName = "FreeImage_Save";
		FreeImage_Save = (FFreeImage_Save)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_Save);

		//Open memory
		funcName = "FreeImage_OpenMemory";
		FreeImage_OpenMemory = (FFreeImage_OpenMemory)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_OpenMemory);

		//Load memory
		funcName = "FreeImage_LoadFromMemory";
		FreeImage_LoadFromMemory = (FFreeImage_LoadFromMemory)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_LoadFromMemory);

		//Convert to 32-bit image
		funcName = "FreeImage_ConvertTo32Bits";
		FreeImage_ConvertTo32Bits = (FFreeImage_ConvertTo32Bits)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_ConvertTo32Bits);

		//Get the number of bits of the image
		funcName = "FreeImage_GetBPP";
		FreeImage_GetBPP = (FFreeImage_GetBPP)FPlatformProcess::GetDllExport(pDllHandler, *funcName);
		check(FreeImage_GetBPP);


		//...................................................




		if (floor_id == "f101")
		{
			char* image_id = TCHAR_TO_UTF8(*ImagePath[0]);
			FIBITMAP* bitmap = f101(image_id, floor_width, floor_height, BRICK_SIZE, BRICK_SIZE, 0, TRUE);
			Width = (float)FreeImage_GetWidth(bitmap);
			Height = (float)FreeImage_GetHeight(bitmap);
			int bitmap_line = FreeImage_GetLine(bitmap);

			// Calculate the number of bytes per pixel (3 bytes for 24 bit pixels and 4 bytes for 32-bit pixels)
			int bytespp = round(bitmap_line / Width);
			//	
			//
			for (unsigned y = 0; y < FreeImage_GetHeight(bitmap); y++)
			{
				//	
				BYTE* bits = FreeImage_GetScanLine(bitmap, y);
				for (unsigned x = 0; x < FreeImage_GetWidth(bitmap); x++) {
					OutData.Add(bits[FI_RGBA_BLUE]);
					OutData.Add(bits[FI_RGBA_GREEN]);
					OutData.Add(bits[FI_RGBA_RED]);
					OutData.Add(bits[FI_RGBA_ALPHA]);//0 is transparent and 255 is opaque

					// Jump to next pixel
					bits += bytespp;
				}
			}
		}
		else if (floor_id == "f105")
		{
			char* image_id = TCHAR_TO_UTF8(*ImagePath[0]);
			FIBITMAP* bitmap = f105(image_id, floor_width, floor_height, BRICK_SIZE, BRICK_SIZE, 0, TRUE);
			Width = (float)FreeImage_GetWidth(bitmap);
			Height = (float)FreeImage_GetHeight(bitmap);
			int bitmap_line = FreeImage_GetLine(bitmap);

			// Calculate the number of bytes per pixel (3 bytes for 24 bit pixels and 4 bytes for 32-bit pixels)
			int bytespp = round(bitmap_line / Width);
			//	
			//
			for (unsigned y = 0; y < FreeImage_GetHeight(bitmap); y++)
			{
				//	
				BYTE* bits = FreeImage_GetScanLine(bitmap, y);
				for (unsigned x = 0; x < FreeImage_GetWidth(bitmap); x++) {
					OutData.Add(bits[FI_RGBA_BLUE]);
					OutData.Add(bits[FI_RGBA_GREEN]);
					OutData.Add(bits[FI_RGBA_RED]);
					OutData.Add(bits[FI_RGBA_ALPHA]);//0 is transparent and 255 is opaque

					// Jump to next pixel
					bits += bytespp;
				}
			}
		}
		else if (floor_id == "p204")
		{
			char* fg_id = TCHAR_TO_UTF8(*ImagePath[0]);
			char* bg_id = TCHAR_TO_UTF8(*ImagePath[1]);


			FIBITMAP* bitmap = p2(TCHAR_TO_UTF8(*floor_id), fg_id, bg_id, floor_width, floor_height, BRICK_SIZE, BRICK_SIZE, 0, TRUE);
			Width = (float)FreeImage_GetWidth(bitmap);
			Height = (float)FreeImage_GetHeight(bitmap);
			int bitmap_line = FreeImage_GetLine(bitmap);

			// Calculate the number of bytes per pixel (3 bytes for 24 bit pixels and 4 bytes for 32-bit pixels)
			int bytespp = round(bitmap_line / Width);
			for (unsigned y = 0; y < FreeImage_GetHeight(bitmap); y++)
			{
				//	
				BYTE* bits = FreeImage_GetScanLine(bitmap, y);
				for (unsigned x = 0; x < FreeImage_GetWidth(bitmap); x++) {


					OutData.Add(bits[FI_RGBA_BLUE]);
					OutData.Add(bits[FI_RGBA_GREEN]);
					OutData.Add(bits[FI_RGBA_RED]);
					OutData.Add(bits[FI_RGBA_ALPHA]);//0 is transparent and 255 is opaque


					// Jump to next pixel
					bits += bytespp;
				}
			}
		}


		//BOOL if_save =  FreeImage_Save(FIF_PNG, bitmap, "D:\\UE4_project\\play3\\play2\\Source\\Images\\ZW001_rotate.png",0);
	}


	return true;



}

FIBITMAP* AMyActor::f101(char* image_id, float diban_width, float diban_height, int width, int height, float y_high, bool if_edge)
{

	//cut string image_id , get multiple detailed pictures from the hard disk, and cut
	charToArray(image_id);

	//charToArray ,The cut detail picture is given to the global variable, and the global variable receives the local
	FIBITMAP* image_l = image;
	FIBITMAP* image_l1 = image1;
	FIBITMAP* image_l2 = image2;
	FIBITMAP* image_l3 = image3;
	//Create final image
	FIBITMAP* dstImage = NULL;


	//Actual dimension of width and height (m)
	float floor_width = cut_width;
	float floor_height = cut_height;
	//Width and height of picture (pixels)
	float image_l_w = pic_cut_width;//width
	float image_l_h = pic_cut_height;//height

	//Calculate the scaling factor of the large image to get the ratio_width and ratio_heigh, to the global variable
	bool result = ratio(diban_width, diban_height, floor_width, floor_height, image_l_w, image_l_h, width, height);

	//Calculate the width and height (pixels) of the picture after the large image scaling factor, and set the global variable ratio_width and ratio_heigh received local
	image_l_w = ratio_width;
	image_l_h = ratio_heigh;
	//Zoom the large picture to get the scaled flower pieces
	image_l = FreeImage_Rescale(image_l, image_l_w, image_l_h, FILTER_CATMULLROM);
	image_l1 = FreeImage_Rescale(image_l1, image_l_w, image_l_h, FILTER_CATMULLROM);
	image_l2 = FreeImage_Rescale(image_l2, image_l_w, image_l_h, FILTER_CATMULLROM);
	image_l3 = FreeImage_Rescale(image_l3, image_l_w, image_l_h, FILTER_CATMULLROM);



	//Add picture to variable array
	TArray<FIBITMAP*> imageArray;
	imageArray.Add(image_l);
	imageArray.Add(image_l1);
	imageArray.Add(image_l2);
	imageArray.Add(image_l3);

	if (if_edge)
	{
		dstImage = repeat_1_hun(imageArray, width, height, BRICK_EDGE, TRUE);
	}
	FreeImage_Save(FIF_PNG, dstImage, "D:\\Images\\srcImage.png", 0);
	return dstImage;
}

FIBITMAP* AMyActor::f105(char* image_id, float diban_width, float diban_height, int width, int height, float y_high, bool if_edge)
{

	//cut string image_id , get multiple detailed pictures from the hard disk, and cut
	charToArray(image_id);

	//charToArray ,The cut detail picture is given to the global variable, and the global variable receives the local
	FIBITMAP* image_l = image;
	FIBITMAP* image_l1 = image1;
	FIBITMAP* image_l2 = image2;
	FIBITMAP* image_l3 = image3;
	//Create final image
	FIBITMAP* dstImage = NULL;


	//Actual dimension of width and height (m)
	float floor_width = cut_width;
	float floor_height = cut_height;
	//Width and height of picture (pixels)
	float image_l_w = pic_cut_width;//宽
	float image_l_h = pic_cut_height;//高

	//Calculate the scaling factor of the large image to get the ratio_width and ratio_heigh, to the global variable
	bool result = ratio(diban_width, diban_height, floor_width, floor_height, image_l_w, image_l_h, width, height);

	//Calculate the width and height (pixels) of the picture after the large image scaling factor, and set the global variable ratio_width and ratio_heigh received local
	image_l_w = ratio_width;
	image_l_h = ratio_heigh;
	//Zoom the large picture to get the scaled flower pieces
	image_l = FreeImage_Rescale(image_l, image_l_w, image_l_h, FILTER_CATMULLROM);
	image_l1 = FreeImage_Rescale(image_l1, image_l_w, image_l_h, FILTER_CATMULLROM);
	image_l2 = FreeImage_Rescale(image_l2, image_l_w, image_l_h, FILTER_CATMULLROM);
	image_l3 = FreeImage_Rescale(image_l3, image_l_w, image_l_h, FILTER_CATMULLROM);

	//旋转90度，得到竖砖
	FIBITMAP* image_rotate = FreeImage_Rotate(image_l, 90, NULL);
	FIBITMAP* image_rotate1 = FreeImage_Rotate(image_l1, 90, NULL);
	FIBITMAP* image_rotate2 = FreeImage_Rotate(image_l2, 90, NULL);
	FIBITMAP* image_rotate3 = FreeImage_Rotate(image_l3, 90, NULL);

	//Add picture to variable array
	TArray<FIBITMAP*> imageArray;
	imageArray.Add(image_l);
	imageArray.Add(image_l1);
	imageArray.Add(image_l2);
	imageArray.Add(image_l3);
	//Add picture to variable array
	TArray<FIBITMAP*> imageArray1;
	imageArray1.Add(image_rotate);
	imageArray1.Add(image_rotate1);
	imageArray1.Add(image_rotate2);
	imageArray1.Add(image_rotate3);


	//花片坐标
	float x1, y1;

	int x_max, y_max;
	//横向循环因子
	x_max = width / image_l_h + 1;
	//纵向循环因子
	y_max = x_max;


	//Due to image calculation, half of the image cannot be pasted, and the size of the final image will be rounded
	FIBITMAP* resultingImage = FreeImage_Allocate(x_max * image_l_h, y_max * image_l_h, 24, 0, 0, 0);



	for (int y = 0; y < y_max; y++) //y是纵向的循环因子
	{//y开始




		for (int x = 0; x < x_max; x++) //x是横向的循环因子，补充对角线上方
		{//x开始

			//竖砖
			x1 = (y - 1) * image_l_h + (x - 1) * image_l_w + (x - 1) * image_l_h; //大砖横坐标
			y1 = (y - 1) * image_l_h + (x - 1) * image_l_h - (x - 1) * image_l_w; //大砖纵坐标
			int r = rand() % BRICK_DETAIL_COUNT;//Random numbers from 0 to 3
			FreeImage_Paste(resultingImage, imageArray1[r], x1, y1, 255);



			//横砖
			x1 = y * image_l_h + (x - 1) * image_l_w + (x - 1) * image_l_h; //横砖横坐标
			y1 = (y - 1) * image_l_h - (x - 1) * image_l_w + (x - 1) * image_l_h; //横砖纵坐标
			int r1 = rand() % BRICK_DETAIL_COUNT;//Random numbers from 0 to 3
			FreeImage_Paste(resultingImage, imageArray[r], x1, y1, 255);


		}//x结束
	}//y结束

	//FreeImage_Save(FIF_PNG, resultingImage, "D:\\Images\\srcImage2.png", 0);
	return resultingImage;


}



FIBITMAP* AMyActor::p2(char* src_id, char* fg_id, char* bg_id, float diban_width, float diban_height, float floor_width, float floor_height, int dst_width, int dst_height
)
{
	int alpha = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	FIBITMAP* maskImage = NULL;
	/*int pixColor = 0;
	int newA = 0;
	int newR = 0;
	int newG = 0;
	int newB = 0;
	int maskA = 0;
	int maskR = 0;
	int maskG = 0;
	int maskB = 0;*/




	//Get a mosaic pattern
	FIBITMAP* srcImage = findData_image_floor(src_id);
	unsigned dib = FreeImage_GetBPP(srcImage);

	//Get 2 flower slices from ImageStore table by id number      
	charToArray(fg_id);
	FIBITMAP* fgImage = image;//1 brick for mosaic
	charToArray(bg_id);
	FIBITMAP* bgImage = image;//2 brick for mosaic

	int width = FreeImage_GetWidth(srcImage); // src image width
	int height = FreeImage_GetHeight(srcImage); // src image height

	//Adjust the foreground and background pictures according to the size of the mosaic style
	fgImage = FreeImage_Rescale(fgImage, width, height, FILTER_CATMULLROM);
	bgImage = FreeImage_Rescale(bgImage, width, height, FILTER_CATMULLROM);



	if (dib == 32)
	{
		//Create a mask image according to the size of the mosaic style, 24 bits without transparent channels
		maskImage = FreeImage_Allocate(width, height, 32, 0, 0, 0);
		fgImage = FreeImage_ConvertTo32Bits(fgImage);
		bgImage = FreeImage_ConvertTo32Bits(bgImage);
	}
	else if (dib == 24)
	{
		//Create a mask image according to the size of the mosaic style, 24 bits without transparent channels
		maskImage = FreeImage_Allocate(width, height, 24, 0, 0, 0);

	}

	int bitmap_line = FreeImage_GetLine(srcImage);
	// Calculate the number of bytes per pixel (3 bytes for 24 bit pixels and 4 bytes for 32-bit pixels)
	int bytespp = round(bitmap_line / width);


	for (unsigned y = 0; y < FreeImage_GetHeight(srcImage); y++)
	{

		BYTE* srcBits = FreeImage_GetScanLine(srcImage, y);
		BYTE* fgBits = FreeImage_GetScanLine(fgImage, y);
		BYTE* bgBits = FreeImage_GetScanLine(bgImage, y);
		alpha = srcBits[FI_RGBA_ALPHA];


		for (unsigned x = 0; x < FreeImage_GetWidth(srcImage); x++)
		{
			red = srcBits[FI_RGBA_RED];
			green = srcBits[FI_RGBA_GREEN];
			blue = srcBits[FI_RGBA_BLUE];
			if ((red > 245))//red
			{

				srcBits[FI_RGBA_RED] = fgBits[FI_RGBA_RED];
				srcBits[FI_RGBA_GREEN] = fgBits[FI_RGBA_GREEN];
				srcBits[FI_RGBA_BLUE] = fgBits[FI_RGBA_BLUE];
				srcBits[FI_RGBA_ALPHA] = 255;

			}
			else if (green > 225)//green
			{
				srcBits[FI_RGBA_RED] = bgBits[FI_RGBA_RED];
				srcBits[FI_RGBA_GREEN] = bgBits[FI_RGBA_GREEN];
				srcBits[FI_RGBA_BLUE] = bgBits[FI_RGBA_BLUE];
				srcBits[FI_RGBA_ALPHA] = 255;
			}
			// Jump to the next pixel
			srcBits += bytespp;
			fgBits += bytespp;
			bgBits += bytespp;

		}
	}

	//FreeImage_Save(FIF_PNG, srcImage, "D:\\Images\\srcImage.png", 0);

	return srcImage;
}




FIBITMAP* AMyActor::repeat_1_hun(TArray<FIBITMAP*> imageArray, int width, int height, float edge, BOOL if_edge)
{

	float x1 = 0, y1 = 0;
	//Get array pointer from detailed image array imageArray
	FIBITMAP** ImagePtr = imageArray.GetData();
	//Get the first picture from the detailed picture array imageArray
	FIBITMAP* srcImage = ImagePtr[0];
	int w = (int)FreeImage_GetWidth(srcImage);//image width
	int h = (int)FreeImage_GetHeight(srcImage);//image height


	//Calculate the cycle factor of X and Y (if decimal, round it, so add 1)
	int x_max = width / w + 1;
	int y_max = height / h + 1;
	//Due to image calculation, half of the image cannot be pasted, and the size of the final image will be rounded
	FIBITMAP* resultingImage = FreeImage_Allocate(x_max * w, y_max * h, 24, 0, 0, 0);


	//Tile
	for (int y = 0; y < y_max; y++) //Y is the longitudinal cyclic factor
	{

		for (int x = 0; x < x_max; x++) //X is the horizontal circulation factor, which is added above the diagonal
		{//

			x1 = x * w; //horizontal coordinate of big brick
			y1 = y * h; //Vertical coordinate of big brick
			//Draw image
			int r = rand() % BRICK_DETAIL_COUNT;//Random numbers from 0 to 3

			FreeImage_Paste(resultingImage, ImagePtr[r], x1, y1, 255);
		}
	}

	if (if_edge)//With brick joints
	{
		int half_edge = (int)round(edge / 2);//Width of brick joint
		//Black vertical road on the left
		FIBITMAP* zhImage = FreeImage_Allocate(half_edge, height, 24, 180, 180, 180);
		//White vertical road on the left
		FIBITMAP* zbImage = FreeImage_Allocate(half_edge, height, 24, 255, 255, 255);
		//Black horizontal passage above
		FIBITMAP* shImage = FreeImage_Allocate(width, half_edge, 24, 180, 180, 180);
		//White horizontal passage above
		FIBITMAP* sbImage = FreeImage_Allocate(width, half_edge, 24, 255, 255, 255);


		//Draw vertical brick joints
		for (int x = 0; x < x_max; x++) //X is the horizontal circulation factor, which is added above the diagonal
		{//
			if (x > 0)
			{

				x1 = x * w - edge; //Abscissa of big brick
				y1 = 0;
			}
			FreeImage_Paste(resultingImage, zhImage, x1, y1, 255);
			FreeImage_Paste(resultingImage, zhImage, x1 + half_edge, y1, 255);

		}


		//Draw horizontal brick joints
		for (int y = 0; y < y_max; y++)
		{
			if (y > 0)
			{
				y1 = y * h - edge;
				x1 = 0;
			}
			FreeImage_Paste(resultingImage, sbImage, x1, y1, 255);
			FreeImage_Paste(resultingImage, shImage, x1, y1 + half_edge, 255);

		}
	}
	return resultingImage;

}


bool AMyActor::ratio(float diban_width, float diban_height, float floor_width, float floor_height, float d_Image_width, float d_Image_height, int width, int height)
{
	/*
	diban_width：floor width（m）diban_height：floor height（m）
	floor_width：image width（m）floor_height：image height（m）
	d_Image_width：image width（pixel） d_Image_height：image height（pixel）

	*/

	//Number of pieces paved on the floor
	float floor_in_object = 0;
	//Length and width of the element after scaling (pixels)
	float dst_width, dst_height;
	//When the width of the floor is the longest side

	if (diban_width > diban_height)
	{
		//Number of blocks of floor = actual size of floor width / element width (m), decimal
		floor_in_object = diban_width / floor_width;
		//Width after element scaling (pixels) =1024/ number of tiles, integer
		dst_width = (width / floor_in_object);
		//Height after element scaling (pixels) = original size of element height (pixels) / original size of element width (pixels) * width after element scaling (pixels)
		dst_height = (d_Image_height / d_Image_width * dst_width);
	}
	else
	{
		floor_in_object = diban_height / floor_height;
		dst_height = (height / floor_in_object);
		dst_width = (d_Image_width / d_Image_height * dst_height);

	}
	//Calculate the zoom factor for width and height
	ratio_width = dst_width;
	ratio_heigh = dst_height;
	return true;
}


void AMyActor::charToArray(char* image_id)
{
	//Cutting upper left corner coordinates x, y; Cutting width and height, ceramic tile width and height, unit: M
	float f_x, f_y, f_cut_width, f_cut_height, width, height;
	int if_yCut;
	char* yCut_style;

	char s[50] = { 0 };//Declare the char array of C language. 50 is the maximum number of strings allowed in this array
	strcpy(s, image_id);//Assign char* to char array
	const char* d = "-";//Separator
	char* p;
	p = strtok(s, d);//Disassemble to get the first string
	char* c_image_id = p;//image_id

	for (int i = 1; i < 9; i++)
	{
		p = strtok(NULL, d);
		if (i == 1)
		{
			f_x = atof(p);//X coordinate, M
		}
		else if (i == 2)
		{
			f_y = atof(p);//Y coordinate, M
		}
		else if (i == 3)
		{
			f_cut_width = atof(p);//Cutting width, M
		}
		else if (i == 4)
		{
			f_cut_height = atof(p);//Cutting height, M
		}
		else if (i == 5)
		{
			width = atof(p);//Ceramic tile width, M
		}
		else if (i == 6)
		{
			height = atof(p);//Ceramic tile height, M
		}
		else if (i == 7)
		{
			if_yCut = atoi(p);//Whether special-shaped cutting is adopted
		}
		else if (i == 8)
		{
			yCut_style = p;//Number of special-shaped water jet, starting from 0
		}
	}

	//Take out the original picture (detail picture) from the hard disk, and assign the detail picture to the global variables image, image1, image2, image3
	findData_image_detail(c_image_id);

	FIBITMAP* uImage = image;
	FIBITMAP* uImage1 = image1;
	FIBITMAP* uImage2 = image2;
	FIBITMAP* uImage3 = image3;
	float pic_width = (float)FreeImage_GetWidth(uImage);//Width of pictures in hard disk, pixels
	float pic_height = (float)FreeImage_GetHeight(uImage);//Height, pixels

	//Proportion between the coordinate XY of the upper left corner of the cutting starting point and the ceramic tile
	float x_percent = f_x / width;
	float y_percent = f_y / height;
	//Ratio of cutting width and height to ceramic tile
	float cut_width_percent = f_cut_width / width;
	float cut_height_percent = f_cut_height / height;


	//Convert the cutting parameters into pixels
	float x = x_percent * pic_width;
	float y = y_percent * pic_height;
	float f_pic_cut_width = cut_width_percent * pic_width;
	float f_pic_cut_height = cut_height_percent * pic_height;

	//Image cutting (coordinate order: left, top, right, bottom)
	image = FreeImage_Copy(uImage, x, y, f_pic_cut_width, f_pic_cut_height);
	image1 = FreeImage_Copy(uImage1, x, y, f_pic_cut_width, f_pic_cut_height);
	image2 = FreeImage_Copy(uImage2, x, y, f_pic_cut_width, f_pic_cut_height);
	image3 = FreeImage_Copy(uImage3, x, y, f_pic_cut_width, f_pic_cut_height);
	//Assign values to global variables
	cut_width = f_cut_width;//Cutting width, M
	cut_height = f_cut_height;//Cutting height, M
	pic_cut_width = f_pic_cut_width;//Cutting width, pixels
	pic_cut_height = f_pic_cut_height;//Cutting height, pixels


}




TArray<FString> AMyActor::findData_image_total()
{
	TArray<FString> t_image_id;//Array of all tile maps
	FString res = TEXT("");
	char* zErrMsg = 0;
	sqlite3* db = NULL;


	FString  fdb_path = FPaths::ProjectDir() + "Content/CityColor/DB/ImageLib.s3db";
	const char* db_path = TCHAR_TO_UTF8(*fdb_path);
	db = OpenDataBase(db_path);

	char* sql = "SELECT image_id FROM ImageStore WHERE brand_id= '0002' and profession_id = '01' ";


	int i = 0;



	sqlite3_stmt* stmt = NULL;

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);//-1 means to automatically calculate the length of SQL statements
	if (result == SQLITE_OK) {

		//Traverse the data, and the parameter position starts from 0

		while (sqlite3_step(stmt) == SQLITE_ROW) {

			const unsigned char* columnValue = sqlite3_column_text(stmt, 0);
			res = UTF8_TO_TCHAR(columnValue);
			t_image_id.Add(res);

		}
	}

	sqlite3_close(db);

	return t_image_id;

}


void AMyActor::findData_image_detail(char* no)
{
	char* image_detail_root_path = "D:/Images/JINYITAO/";
	char* file_type = ".png";
	char* file_name = new char[1];//初始化char数组
	char* temp = new char[50];//初始化char数组
	char* imageFile = new char[50];//初始化char数组
	strcpy(temp, image_detail_root_path);//将imageFile清空，将image_detail_root_path复制进来
	strcat(temp, no);//将no复制到imageFile的后面
	strcat(temp, "_");

	for (int x = 1; x < 5; x++)
	{//		
		sprintf(file_name, "%d%s", x, file_type);//Match the X of int with file_ Type connection, assigned to file_ name
		strcpy(imageFile, temp);
		strcat(imageFile, file_name);
		if (x == 1)
		{
			FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(imageFile, 0);
			image = FreeImage_Load(fifmt, imageFile, PNG_DEFAULT);
		}
		else if (x == 2)
		{
			FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(imageFile, 0);
			image1 = FreeImage_Load(fifmt, imageFile, PNG_DEFAULT);
		}
		else if (x == 3)
		{
			FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(imageFile, 0);
			image2 = FreeImage_Load(fifmt, imageFile, PNG_DEFAULT);
		}
		else if (x == 4)
		{
			FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(imageFile, 0);
			image3 = FreeImage_Load(fifmt, imageFile, PNG_DEFAULT);
		}
	}
}
//Query the floor image from the hard disk for mosaic
FIBITMAP* AMyActor::findData_image_floor(char* no)
{
	//floor  Mosaic root directory
	char* image_floor_root_path = "D:/Images/Floor/";
	char* file_type = ".png";

	char* imageFile = new char[50];//Initialize char array
	strcpy(imageFile, image_floor_root_path);// Empty the imageFile and  the image_floor_root_path copy in
	strcat(imageFile, no);//Copy no to the back of imageFile
	strcat(imageFile, file_type);//Copy file_type to the back of no

	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(imageFile, 0);
	FIBITMAP* uImage = FreeImage_Load(fifmt, imageFile, PNG_DEFAULT);
	return uImage;
}




sqlite3* AMyActor::OpenDataBase(FString DataBasePath)
{
	sqlite3* pDataBase = nullptr;//Database for storing pictures
	FString result = TEXT("");
	int nRes = sqlite3_open_v2(TCHAR_TO_UTF8(*DataBasePath), &pDataBase, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, nullptr);
	if (nRes != SQLITE_OK)
	{
		result += TEXT("Open DataBase Faield!    ");
		const char* error = sqlite3_errmsg(pDataBase);
		if (error != nullptr)
		{
			result += UTF8_TO_TCHAR(error);
		}
		sqlite3_close_v2(pDataBase);
		pDataBase = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("OPEN DATABASE FAILED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
		return false;
	}
	else
	{
		result = TEXT("Open DataBase Success!");
		UE_LOG(LogTemp, Warning, TEXT("OPEN DATABASE SUCC!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
	}
	return pDataBase;




}


//_style:0Without modifying the material, use the dynamic material copy to empty the stored dynamic material；1The unreplaced map turns yellow. Use replaceable dynamic materials to store dynamic materials；
//2The script changes the map and turns white, uses replaceable dynamic materials, and stores dynamic materials;3The script changes the map and turns yellow. Use replaceable dynamic materials to store dynamic materials
void AMyActor::setMat(const AStaticMeshActor* changeObject, UTexture* Texture, int _style)
{
	UMaterialInstanceDynamic* MaterialInstance;//Dynamic material
	//Get the mesh component of the object
	UStaticMeshComponent* changeObjectCom = changeObject->GetStaticMeshComponent();


	int indexOfChangeObject = getIndexOfChangeObject(changeObject->GetName(), change_object);
	UMaterialInterface* currentMat = nullptr;//Initialize dynamic materials


	if (if_change[indexOfChangeObject] != 0)//If the material has been modified
	{
		MaterialInstance = d_mat[indexOfChangeObject];// Take out Material instances   in d_mat
	}
	else//If the material has not been modified
	{
		currentMat = change_mat[0];//Obtained from material varieties
		MaterialInstance = UMaterialInstanceDynamic::Create(currentMat, nullptr);//According to current_mat create dynamic material instances
	}

	if (MaterialInstance)
	{

		if (_style == 0)//The material is not replaced, and the original material is restored
		{
			MaterialInstance = change_object_d_mat[indexOfChangeObject];//Take out the dynamic material copy
			d_mat[indexOfChangeObject] = nullptr;//d_matEmpty dynamic materials
		}
		else if (_style == 1)//The map is not changed, and double clicking turns yellow
		{
			MaterialInstance->SetVectorParameterValue(TEXT("color"), { 1, 2, 0 });//yellow
			d_mat[indexOfChangeObject] = MaterialInstance;//Store modified dynamic materials
		}
		else if (_style == 2)//Change the material map to white
		{
			MaterialInstance->SetTextureParameterValue(TEXT("Diffuse"), Texture);
			MaterialInstance->SetVectorParameterValue(TEXT("color"), { 1, 1, 1 });//white

			//MaterialInstance->SetScalarParameterValue(TEXT("metalic"), 0.3f);//Modify material parameters
			d_mat[indexOfChangeObject] = MaterialInstance;//Store modified dynamic materials
		}
		else if (_style == 3)//After changing the map, double click to turn yellow
		{
			MaterialInstance->SetVectorParameterValue(TEXT("color"), { 1, 2, 0 });//yellow
			d_mat[indexOfChangeObject] = MaterialInstance;//Store modified dynamic materials
		}
		else if (_style == 4)//After changing the map, click to rotate the main material
		{
			float _rotation = 0;
			MaterialInstance->GetScalarParameterValue(TEXT("Rotation"), _rotation, false);
			_rotation = _rotation + 0.125f;
			MaterialInstance->SetScalarParameterValue(TEXT("Rotation"), _rotation);//Rotate 45 degrees
			MaterialInstance->SetVectorParameterValue(TEXT("color"), { 1, 1, 1 });//white
			d_mat[indexOfChangeObject] = MaterialInstance;//Store modified dynamic materials			
		}
		else if (_style == 5)//After changing the map, click to select the parent material, which turns pink
		{
			MaterialInstance->SetVectorParameterValue(TEXT("color"), { 1, 0.72, 0.72 });//pink
			d_mat[indexOfChangeObject] = MaterialInstance;//Store modified dynamic materials
		}
		else if (_style == 6)//After selecting the parent material, paste the material
		{
			//MaterialInstance = copy_mat;//According to current_mat create dynamic material instances
			MaterialInstance->CopyInterpParameters(copy_mat);
			d_mat[indexOfChangeObject] = MaterialInstance;//Store modified dynamic materials
		}
	}
	changeObjectCom->SetMaterial(0, MaterialInstance);//Assign dynamic materials to object components
	if_change[indexOfChangeObject] = _style;//Material has been modified

}

//Get the parent material of the copied object
UMaterialInstanceDynamic* AMyActor::getCopyMat(int indexOfChangeObject)
{
	return d_mat[indexOfChangeObject];
}

//Save copied object parent material
void AMyActor::setCopyMat(UMaterialInstanceDynamic* copyMat)
{
	copy_mat = nullptr;
	copy_mat = UMaterialInstanceDynamic::Create(change_mat[0], nullptr);
	//Copy parent material to copy_mat
	copy_mat->CopyInterpParameters(copyMat);

}



//Get the current rotation angle of the main material of the object
float AMyActor::getRotation(const AStaticMeshActor* changeObject)
{
	float rotation;
	UMaterialInterface* MaterialInstance;//Dynamic material
	//Get the mesh component of the object
	UStaticMeshComponent* changeObjectCom = changeObject->GetStaticMeshComponent();


	//Get the material list of components

	TArray<class UMaterialInterface*> myMat = changeObjectCom->GetMaterials();
	MaterialInstance = myMat[0];
	MaterialInstance->GetScalarParameterValue(TEXT("Rotation"), rotation, true);

	return rotation;
}

char* AMyActor::constchar2char(const char* str)
{
	int nLen = strlen(str);

	char* pCh = new char[nLen + 1];
	strcpy(pCh, str);
	return pCh;

}
void AMyActor::setInt()
{
	Color123 = 10;
}

UTexture2D* AMyActor::getTex()
{
	return tex_2d;
}


//int AMyActor::getRoomCount()
//{
//	return location.Num();
//}
int AMyActor::getLivingRoomCamCount()
{
	return livingroom_location.Num();
}
int AMyActor::getBedRoomCamCount()
{
	return bedroom_location.Num();
}
int AMyActor::getKitchenCamCount()
{
	return kitchen_location.Num();
}
int AMyActor::getWCCamCount()
{
	return wc_location.Num();
}

//FTransform AMyActor::getLocation(int index)
//{
//	return location[index];
//}

FTransform AMyActor::getLivingroomLocation(int index)
{
	return livingroom_location[index];
}


float AMyActor::getLivingroomRotation(int index)
{
	return livingroom_rotation[index];
}

TArray<int> AMyActor::getLivingroomDirection()
{
	return livingroom_direction;
}

void AMyActor::setCurrentDirection(int direction)
{
	current_direction = direction;
}

int AMyActor::getCurrentDirection()
{
	return current_direction;
}


FTransform AMyActor::getBedroomLocation(int index)
{
	return bedroom_location[index];
}

float AMyActor::getBedroomRotation(int index)
{
	return bedroom_rotation[index];
}

TArray<int> AMyActor::getBedroomDirection()
{
	return bedroom_direction;
}


FTransform AMyActor::getKitchenLocation(int index)
{
	return kitchen_location[index];
}

float AMyActor::getKitchenRotation(int index)
{
	return kitchen_rotation[index];
}

TArray<int> AMyActor::getKitchenDirection()
{
	return kitchen_direction;
}



FTransform AMyActor::getWCLocation(int index)
{
	return wc_location[index];
}


float AMyActor::getWCRotation(int index)
{
	return wc_rotation[index];
}

TArray<int> AMyActor::getWCDirection()
{
	return wc_direction;
}




ALevelSequenceActor* AMyActor::getSequence()
{
	return sequence;
}
void AMyActor::setSize(AStaticMeshActor* doubleTapObject)
{

	UStaticMeshComponent* mesh = doubleTapObject->GetStaticMeshComponent();
	object_width = mesh->GetStaticMesh()->GetBounds().GetBox().GetSize().X;
	object_height = mesh->GetStaticMesh()->GetBounds().GetBox().GetSize().Y;
}
float AMyActor::getWidth()
{
	return object_width;
}
float AMyActor::getHeight()
{
	return object_height;
}

void AMyActor::setWidth(float objectWidth)
{
	object_width = objectWidth;
}
void AMyActor::setHeight(float objectHeight)
{
	object_height = objectHeight;
}


TArray<AStaticMeshActor*> AMyActor::getChangeObject()
{
	return change_object;
}

TArray<int> AMyActor::getIfChange()
{
	return if_change;
}

void AMyActor::setIfChange(int _style, int indexOfChangeObject)
{
	if_change[indexOfChangeObject] = _style;
}





//Double click to determine whether the object is change_object
int AMyActor::getIndexOfChangeObject(const FString& name, const TArray<AStaticMeshActor*>& changeObject)
{
	//
	int count = changeObject.Num();
	for (int x = 0; x < count; x++)
	{
		if (name == changeObject[x]->GetFName().ToString())
		{
			return x;//If the names are equal, return the number
		}
	}
	return -1;//If the names are not equal, return -1
}


void AMyActor::setDoubleTapObject(AStaticMeshActor* doubleTapObject)
{
	double_tap_object = doubleTapObject;
}

AStaticMeshActor* AMyActor::getDoubleTapObject()
{
	return double_tap_object;
}


void AMyActor::setCopyObject(AStaticMeshActor* copyObject)
{
	copy_object = copyObject;
}

AStaticMeshActor* AMyActor::getCopyObject()
{
	return copy_object;
}




void AMyActor::setTapObject(AStaticMeshActor* tapObject)
{
	tap_object = tapObject;
}

AStaticMeshActor* AMyActor::getTapObject()
{
	return tap_object;
}


void AMyActor::setIndexOfChangeObject(int indexOfChangeObject)
{
	index_of_change_object = indexOfChangeObject;
}

//Initialize array d_mat, Quantity equals change_object
void AMyActor::initD_mat(int count)
{
	d_mat.Init(nullptr, count);

}
//Initializes a dynamic material copy of the original shader of a replaceable material object
void AMyActor::initChangeObjectDMat()
{
	int count = change_object_mat.Num();
	change_object_d_mat.Init(nullptr, count);
	for (int i = 0; i < count; i++)
	{
		//According to change_object_mat create dynamic material instances
		UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(change_object_mat[i], nullptr);
		change_object_d_mat[i] = MaterialInstance;
	}

}
//Initialize array if_change, Quantity equals change_object
void AMyActor::initIf_change(int count)
{
	if_change.Init(0, count);
}



