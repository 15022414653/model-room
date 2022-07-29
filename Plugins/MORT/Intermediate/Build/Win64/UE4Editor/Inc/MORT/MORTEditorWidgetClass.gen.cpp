// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MORT/Public/MORTEditorWidgetClass.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMORTEditorWidgetClass() {}
// Cross Module References
	MORT_API UEnum* Z_Construct_UEnum_MORT_EMORTAction();
	UPackage* Z_Construct_UPackage__Script_MORT();
	MORT_API UClass* Z_Construct_UClass_UMORTEditorWidgetClass_NoRegister();
	MORT_API UClass* Z_Construct_UClass_UMORTEditorWidgetClass();
	BLUTILITY_API UClass* Z_Construct_UClass_UEditorUtilityWidget();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
// End Cross Module References
	static UEnum* EMORTAction_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_MORT_EMORTAction, Z_Construct_UPackage__Script_MORT(), TEXT("EMORTAction"));
		}
		return Singleton;
	}
	template<> MORT_API UEnum* StaticEnum<EMORTAction>()
	{
		return EMORTAction_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EMORTAction(EMORTAction_StaticEnum, TEXT("/Script/MORT"), TEXT("EMORTAction"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_MORT_EMORTAction_Hash() { return 2211618154U; }
	UEnum* Z_Construct_UEnum_MORT_EMORTAction()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_MORT();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EMORTAction"), 0, Get_Z_Construct_UEnum_MORT_EMORTAction_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EMORTAction::ToLowerCase", (int64)EMORTAction::ToLowerCase },
				{ "EMORTAction::ToUpperCase", (int64)EMORTAction::ToUpperCase },
				{ "EMORTAction::RemoveFromStart", (int64)EMORTAction::RemoveFromStart },
				{ "EMORTAction::RemoveFromEnd", (int64)EMORTAction::RemoveFromEnd },
				{ "EMORTAction::Prefix", (int64)EMORTAction::Prefix },
				{ "EMORTAction::Suffix", (int64)EMORTAction::Suffix },
				{ "EMORTAction::RenameAndNumerate", (int64)EMORTAction::RenameAndNumerate },
				{ "EMORTAction::Numerate", (int64)EMORTAction::Numerate },
				{ "EMORTAction::FindAndReplace", (int64)EMORTAction::FindAndReplace },
				{ "EMORTAction::FindRegexAndReplace", (int64)EMORTAction::FindRegexAndReplace },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Comment", "/**\n * \n */" },
				{ "FindAndReplace.Comment", "/**\n * \n */" },
				{ "FindAndReplace.Name", "EMORTAction::FindAndReplace" },
				{ "FindRegexAndReplace.Comment", "/**\n * \n */" },
				{ "FindRegexAndReplace.Name", "EMORTAction::FindRegexAndReplace" },
				{ "ModuleRelativePath", "Public/MORTEditorWidgetClass.h" },
				{ "Numerate.Comment", "/**\n * \n */" },
				{ "Numerate.Name", "EMORTAction::Numerate" },
				{ "Prefix.Comment", "/**\n * \n */" },
				{ "Prefix.Name", "EMORTAction::Prefix" },
				{ "RemoveFromEnd.Comment", "/**\n * \n */" },
				{ "RemoveFromEnd.Name", "EMORTAction::RemoveFromEnd" },
				{ "RemoveFromStart.Comment", "/**\n * \n */" },
				{ "RemoveFromStart.Name", "EMORTAction::RemoveFromStart" },
				{ "RenameAndNumerate.Comment", "/**\n * \n */" },
				{ "RenameAndNumerate.Name", "EMORTAction::RenameAndNumerate" },
				{ "Suffix.Comment", "/**\n * \n */" },
				{ "Suffix.Name", "EMORTAction::Suffix" },
				{ "ToLowerCase.Comment", "/**\n * \n */" },
				{ "ToLowerCase.Name", "EMORTAction::ToLowerCase" },
				{ "ToUpperCase.Comment", "/**\n * \n */" },
				{ "ToUpperCase.Name", "EMORTAction::ToUpperCase" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_MORT,
				nullptr,
				"EMORTAction",
				"EMORTAction",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	DEFINE_FUNCTION(UMORTEditorWidgetClass::execOnEachSelectedActorDelegate)
	{
		P_GET_OBJECT(AActor,Z_Param_actor);
		P_GET_PROPERTY(FIntProperty,Z_Param_index);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnEachSelectedActorDelegate(Z_Param_actor,Z_Param_index);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMORTEditorWidgetClass::execOnEachSelectedAssetDelegate)
	{
		P_GET_OBJECT(UObject,Z_Param_asset);
		P_GET_PROPERTY(FIntProperty,Z_Param_index);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnEachSelectedAssetDelegate(Z_Param_asset,Z_Param_index);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMORTEditorWidgetClass::execSetup)
	{
		P_GET_ENUM(EMORTAction,Z_Param_action);
		P_GET_TARRAY(AActor*,Z_Param_actors);
		P_GET_TARRAY(UObject*,Z_Param_assets);
		P_GET_UBOOL(Z_Param_renameProjectAssets);
		P_GET_UBOOL(Z_Param_renameWorldActors);
		P_GET_PROPERTY(FStrProperty,Z_Param_textToFind);
		P_GET_PROPERTY(FStrProperty,Z_Param_targetText);
		P_GET_PROPERTY(FStrProperty,Z_Param_RegexPattern);
		P_GET_PROPERTY(FIntProperty,Z_Param_CapturingGroupNumber);
		P_GET_PROPERTY(FIntProperty,Z_Param_startNumber);
		P_GET_UBOOL(Z_Param_numeratePosition);
		P_GET_PROPERTY(FStrProperty,Z_Param_numerateSeparator);
		P_GET_PROPERTY(FIntProperty,Z_Param_charsToRemove);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Setup(EMORTAction(Z_Param_action),Z_Param_actors,Z_Param_assets,Z_Param_renameProjectAssets,Z_Param_renameWorldActors,Z_Param_textToFind,Z_Param_targetText,Z_Param_RegexPattern,Z_Param_CapturingGroupNumber,Z_Param_startNumber,Z_Param_numeratePosition,Z_Param_numerateSeparator,Z_Param_charsToRemove);
		P_NATIVE_END;
	}
	void UMORTEditorWidgetClass::StaticRegisterNativesUMORTEditorWidgetClass()
	{
		UClass* Class = UMORTEditorWidgetClass::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnEachSelectedActorDelegate", &UMORTEditorWidgetClass::execOnEachSelectedActorDelegate },
			{ "OnEachSelectedAssetDelegate", &UMORTEditorWidgetClass::execOnEachSelectedAssetDelegate },
			{ "Setup", &UMORTEditorWidgetClass::execSetup },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics
	{
		struct MORTEditorWidgetClass_eventOnEachSelectedActorDelegate_Parms
		{
			AActor* actor;
			int32 index;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_actor;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_index;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::NewProp_actor = { "actor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventOnEachSelectedActorDelegate_Parms, actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::NewProp_index = { "index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventOnEachSelectedActorDelegate_Parms, index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::NewProp_actor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::NewProp_index,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MORTEditorWidgetClass.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMORTEditorWidgetClass, nullptr, "OnEachSelectedActorDelegate", nullptr, nullptr, sizeof(MORTEditorWidgetClass_eventOnEachSelectedActorDelegate_Parms), Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics
	{
		struct MORTEditorWidgetClass_eventOnEachSelectedAssetDelegate_Parms
		{
			UObject* asset;
			int32 index;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_asset;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_index;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::NewProp_asset = { "asset", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventOnEachSelectedAssetDelegate_Parms, asset), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::NewProp_index = { "index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventOnEachSelectedAssetDelegate_Parms, index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::NewProp_asset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::NewProp_index,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MORTEditorWidgetClass.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMORTEditorWidgetClass, nullptr, "OnEachSelectedAssetDelegate", nullptr, nullptr, sizeof(MORTEditorWidgetClass_eventOnEachSelectedAssetDelegate_Parms), Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics
	{
		struct MORTEditorWidgetClass_eventSetup_Parms
		{
			EMORTAction action;
			TArray<AActor*> actors;
			TArray<UObject*> assets;
			bool renameProjectAssets;
			bool renameWorldActors;
			FString textToFind;
			FString targetText;
			FString RegexPattern;
			int32 CapturingGroupNumber;
			int32 startNumber;
			bool numeratePosition;
			FString numerateSeparator;
			int32 charsToRemove;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_action_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_action;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_actors_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_actors;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_assets_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_assets;
		static void NewProp_renameProjectAssets_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_renameProjectAssets;
		static void NewProp_renameWorldActors_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_renameWorldActors;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_textToFind;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_targetText;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_RegexPattern;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CapturingGroupNumber;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_startNumber;
		static void NewProp_numeratePosition_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_numeratePosition;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_numerateSeparator;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_charsToRemove;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_action_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_action = { "action", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, action), Z_Construct_UEnum_MORT_EMORTAction, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_actors_Inner = { "actors", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_actors = { "actors", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, actors), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_assets_Inner = { "assets", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_assets = { "assets", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, assets), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_renameProjectAssets_SetBit(void* Obj)
	{
		((MORTEditorWidgetClass_eventSetup_Parms*)Obj)->renameProjectAssets = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_renameProjectAssets = { "renameProjectAssets", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(MORTEditorWidgetClass_eventSetup_Parms), &Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_renameProjectAssets_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_renameWorldActors_SetBit(void* Obj)
	{
		((MORTEditorWidgetClass_eventSetup_Parms*)Obj)->renameWorldActors = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_renameWorldActors = { "renameWorldActors", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(MORTEditorWidgetClass_eventSetup_Parms), &Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_renameWorldActors_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_textToFind = { "textToFind", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, textToFind), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_targetText = { "targetText", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, targetText), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_RegexPattern = { "RegexPattern", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, RegexPattern), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_CapturingGroupNumber = { "CapturingGroupNumber", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, CapturingGroupNumber), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_startNumber = { "startNumber", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, startNumber), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_numeratePosition_SetBit(void* Obj)
	{
		((MORTEditorWidgetClass_eventSetup_Parms*)Obj)->numeratePosition = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_numeratePosition = { "numeratePosition", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(MORTEditorWidgetClass_eventSetup_Parms), &Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_numeratePosition_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_numerateSeparator = { "numerateSeparator", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, numerateSeparator), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_charsToRemove = { "charsToRemove", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(MORTEditorWidgetClass_eventSetup_Parms, charsToRemove), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_action_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_action,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_actors_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_actors,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_assets_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_assets,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_renameProjectAssets,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_renameWorldActors,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_textToFind,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_targetText,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_RegexPattern,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_CapturingGroupNumber,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_startNumber,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_numeratePosition,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_numerateSeparator,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::NewProp_charsToRemove,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::Function_MetaDataParams[] = {
		{ "Category", "Values" },
		{ "ModuleRelativePath", "Public/MORTEditorWidgetClass.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMORTEditorWidgetClass, nullptr, "Setup", nullptr, nullptr, sizeof(MORTEditorWidgetClass_eventSetup_Parms), Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UMORTEditorWidgetClass_Setup()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMORTEditorWidgetClass_Setup_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UMORTEditorWidgetClass_NoRegister()
	{
		return UMORTEditorWidgetClass::StaticClass();
	}
	struct Z_Construct_UClass_UMORTEditorWidgetClass_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMORTEditorWidgetClass_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UEditorUtilityWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_MORT,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UMORTEditorWidgetClass_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedActorDelegate, "OnEachSelectedActorDelegate" }, // 1622129432
		{ &Z_Construct_UFunction_UMORTEditorWidgetClass_OnEachSelectedAssetDelegate, "OnEachSelectedAssetDelegate" }, // 2352149095
		{ &Z_Construct_UFunction_UMORTEditorWidgetClass_Setup, "Setup" }, // 1027493933
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMORTEditorWidgetClass_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "MORTEditorWidgetClass.h" },
		{ "ModuleRelativePath", "Public/MORTEditorWidgetClass.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMORTEditorWidgetClass_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMORTEditorWidgetClass>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UMORTEditorWidgetClass_Statics::ClassParams = {
		&UMORTEditorWidgetClass::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UMORTEditorWidgetClass_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMORTEditorWidgetClass_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMORTEditorWidgetClass()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMORTEditorWidgetClass_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UMORTEditorWidgetClass, 162822782);
	template<> MORT_API UClass* StaticClass<UMORTEditorWidgetClass>()
	{
		return UMORTEditorWidgetClass::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMORTEditorWidgetClass(Z_Construct_UClass_UMORTEditorWidgetClass, &UMORTEditorWidgetClass::StaticClass, TEXT("/Script/MORT"), TEXT("UMORTEditorWidgetClass"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMORTEditorWidgetClass);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
