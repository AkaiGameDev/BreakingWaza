// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Panacea/PanaceaGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePanaceaGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	PANACEA_API UClass* Z_Construct_UClass_APanaceaGameMode();
	PANACEA_API UClass* Z_Construct_UClass_APanaceaGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Panacea();
// End Cross Module References
	void APanaceaGameMode::StaticRegisterNativesAPanaceaGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APanaceaGameMode);
	UClass* Z_Construct_UClass_APanaceaGameMode_NoRegister()
	{
		return APanaceaGameMode::StaticClass();
	}
	struct Z_Construct_UClass_APanaceaGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_APanaceaGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Panacea,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APanaceaGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_APanaceaGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "PanaceaGameMode.h" },
		{ "ModuleRelativePath", "PanaceaGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_APanaceaGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APanaceaGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_APanaceaGameMode_Statics::ClassParams = {
		&APanaceaGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APanaceaGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_APanaceaGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_APanaceaGameMode()
	{
		if (!Z_Registration_Info_UClass_APanaceaGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APanaceaGameMode.OuterSingleton, Z_Construct_UClass_APanaceaGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_APanaceaGameMode.OuterSingleton;
	}
	template<> PANACEA_API UClass* StaticClass<APanaceaGameMode>()
	{
		return APanaceaGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(APanaceaGameMode);
	APanaceaGameMode::~APanaceaGameMode() {}
	struct Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_APanaceaGameMode, APanaceaGameMode::StaticClass, TEXT("APanaceaGameMode"), &Z_Registration_Info_UClass_APanaceaGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APanaceaGameMode), 3992665498U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaGameMode_h_2263453911(TEXT("/Script/Panacea"),
		Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
