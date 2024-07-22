// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePanacea_init() {}
	PANACEA_API UFunction* Z_Construct_UDelegateFunction_Panacea_OnPickUp__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Panacea;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Panacea()
	{
		if (!Z_Registration_Info_UPackage__Script_Panacea.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Panacea_OnPickUp__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Panacea",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xDCE77A5C,
				0xEBA19B11,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Panacea.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Panacea.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Panacea(Z_Construct_UPackage__Script_Panacea, TEXT("/Script/Panacea"), Z_Registration_Info_UPackage__Script_Panacea, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xDCE77A5C, 0xEBA19B11));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
