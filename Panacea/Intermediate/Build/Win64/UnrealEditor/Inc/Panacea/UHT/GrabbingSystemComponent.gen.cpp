// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Panacea/GrabbingSystemComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGrabbingSystemComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_UInputComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UPhysicsHandleComponent_NoRegister();
	PANACEA_API UClass* Z_Construct_UClass_UGrabbingSystemComponent();
	PANACEA_API UClass* Z_Construct_UClass_UGrabbingSystemComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Panacea();
// End Cross Module References
	void UGrabbingSystemComponent::StaticRegisterNativesUGrabbingSystemComponent()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGrabbingSystemComponent);
	UClass* Z_Construct_UClass_UGrabbingSystemComponent_NoRegister()
	{
		return UGrabbingSystemComponent::StaticClass();
	}
	struct Z_Construct_UClass_UGrabbingSystemComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PhysicsHandle_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_PhysicsHandle;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InputComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_InputComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Reach_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Reach;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGrabbingSystemComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Panacea,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabbingSystemComponent_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabbingSystemComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "GrabbingSystemComponent.h" },
		{ "ModuleRelativePath", "GrabbingSystemComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_PhysicsHandle_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Physics Handle\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GrabbingSystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Physics Handle" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_PhysicsHandle = { "PhysicsHandle", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrabbingSystemComponent, PhysicsHandle), Z_Construct_UClass_UPhysicsHandleComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_PhysicsHandle_MetaData), Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_PhysicsHandle_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_InputComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Input Component\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GrabbingSystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Component" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_InputComponent = { "InputComponent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrabbingSystemComponent, InputComponent), Z_Construct_UClass_UInputComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_InputComponent_MetaData), Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_InputComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_Reach_MetaData[] = {
		{ "Category", "GrabbingSystemComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// How far ahead of the player can we reach in cm\n" },
#endif
		{ "ModuleRelativePath", "GrabbingSystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How far ahead of the player can we reach in cm" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_Reach = { "Reach", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrabbingSystemComponent, Reach), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_Reach_MetaData), Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_Reach_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGrabbingSystemComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_PhysicsHandle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_InputComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabbingSystemComponent_Statics::NewProp_Reach,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGrabbingSystemComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGrabbingSystemComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGrabbingSystemComponent_Statics::ClassParams = {
		&UGrabbingSystemComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGrabbingSystemComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UGrabbingSystemComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabbingSystemComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UGrabbingSystemComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabbingSystemComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UGrabbingSystemComponent()
	{
		if (!Z_Registration_Info_UClass_UGrabbingSystemComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGrabbingSystemComponent.OuterSingleton, Z_Construct_UClass_UGrabbingSystemComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGrabbingSystemComponent.OuterSingleton;
	}
	template<> PANACEA_API UClass* StaticClass<UGrabbingSystemComponent>()
	{
		return UGrabbingSystemComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGrabbingSystemComponent);
	UGrabbingSystemComponent::~UGrabbingSystemComponent() {}
	struct Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_GrabbingSystemComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_GrabbingSystemComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGrabbingSystemComponent, UGrabbingSystemComponent::StaticClass, TEXT("UGrabbingSystemComponent"), &Z_Registration_Info_UClass_UGrabbingSystemComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGrabbingSystemComponent), 421340200U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_GrabbingSystemComponent_h_3482273642(TEXT("/Script/Panacea"),
		Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_GrabbingSystemComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_GrabbingSystemComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
