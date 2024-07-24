// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PanaceaProjectile.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef PANACEA_PanaceaProjectile_generated_h
#error "PanaceaProjectile.generated.h already included, missing '#pragma once' in PanaceaProjectile.h"
#endif
#define PANACEA_PanaceaProjectile_generated_h

#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_SPARSE_DATA
#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit);


#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_ACCESSORS
#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPanaceaProjectile(); \
	friend struct Z_Construct_UClass_APanaceaProjectile_Statics; \
public: \
	DECLARE_CLASS(APanaceaProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Panacea"), NO_API) \
	DECLARE_SERIALIZER(APanaceaProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APanaceaProjectile(APanaceaProjectile&&); \
	NO_API APanaceaProjectile(const APanaceaProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APanaceaProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APanaceaProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APanaceaProjectile) \
	NO_API virtual ~APanaceaProjectile();


#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_12_PROLOG
#define FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_SPARSE_DATA \
	FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_ACCESSORS \
	FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PANACEA_API UClass* StaticClass<class APanaceaProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Lpars_Documents_BreakingWaza_Panacea_Source_Panacea_PanaceaProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
