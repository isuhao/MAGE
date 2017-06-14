#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_GUID_TRANSFORM_VS					L"transform_vs"
#define MAGE_GUID_EMISSIVE_PS					L"emissive_ps"
#define MAGE_GUID_LAMBERTIAN_PS					L"lambertian_ps"
#define MAGE_GUID_PHONG_PS						L"phong_ps"
#define MAGE_GUID_MODIFIED_PHONG_PS				L"modified_phong_ps"
#define MAGE_GUID_BLINN_PHONG_PS				L"blinn_phong_ps"
#define MAGE_GUID_MODIFIED_BLINN_PHONG_PS		L"modified_blinn_phong_ps"
#define MAGE_GUID_WARD_PS						L"ward_ps"
#define MAGE_GUID_WARD_DUER_PS					L"ward_duer_ps"
#define MAGE_GUID_COOK_TORRANCE_PS				L"cook_torrance_ps"
#define MAGE_GUID_TSNM_LAMBERTIAN_PS			L"tsnm_lambertian_ps"
#define MAGE_GUID_TSNM_PHONG_PS					L"tsnm_phong_ps"
#define MAGE_GUID_TSNM_MODIFIED_PHONG_PS		L"tsnm_modified_phong_ps"
#define MAGE_GUID_TSNM_BLINN_PHONG_PS			L"tsnm_blinn_phong_ps"
#define MAGE_GUID_TSNM_MODIFIED_BLINN_PHONG_PS	L"tsnm_modified_blinn_phong_ps"
#define MAGE_GUID_TSNM_WARD_PS					L"tsnm_ward_ps"
#define MAGE_GUID_TSNM_WARD_DUER_PS				L"tsnm_ward_duer_ps"
#define MAGE_GUID_TSNM_COOK_TORRANCE_PS			L"tsnm_cook_torrance_ps"
#define MAGE_GUID_SPRITE_VS						L"sprite_vs"
#define MAGE_GUID_SPRITE_PS						L"sprite_ps"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Returns the compiled transform vertex shader.

	 @return		The compiled transform vertex shader.
	 */
	const CompiledVertexShader CreateCompiledTransformVertexShader() noexcept;

	/**
	 Returns the compiled emissive pixel shader.

	 @return		The compiled emissive pixel shader.
	 */
	const CompiledPixelShader CreateCompiledEmissivePixelShader() noexcept;

	/**
	 Returns the compiled Lambertian pixel shader.

	 @return		The compiled Lambertian pixel shader.
	 */
	const CompiledPixelShader CreateCompiledLambertianPixelShader() noexcept;

	/**
	 Returns the compiled Phong pixel shader.

	 @return		The compiled Phong pixel shader.
	 */
	const CompiledPixelShader CreateCompiledPhongPixelShader() noexcept;

	/**
	 Returns the compiled Modified Phong pixel shader.

	 @return		The compiled Modified Phong pixel shader.
	 */
	const CompiledPixelShader CreateCompiledModifiedPhongPixelShader() noexcept;

	/**
	 Returns the compiled Blinn-Phong pixel shader.

	 @return		The compiled Blinn-Phong pixel shader.
	 */
	const CompiledPixelShader CreateCompiledBlinnPhongPixelShader() noexcept;

	/**
	 Returns the compiled Modified Blinn-Phong pixel shader.

	 @return		The compiled Modified Blinn-Phong pixel shader.
	 */
	const CompiledPixelShader CreateCompiledModifiedBlinnPhongPixelShader() noexcept;

	/**
	 Returns the compiled Ward pixel shader.

	 @return		The compiled Ward pixel shader.
	 */
	const CompiledPixelShader CreateCompiledWardPixelShader() noexcept;

	/**
	 Returns the compiled Ward-Duer pixel shader.

	 @return		The compiled Ward-Duer pixel shader.
	 */
	const CompiledPixelShader CreateCompiledWardDuerPixelShader() noexcept;

	/**
	 Returns the compiled Cook-Torrance pixel shader.

	 @return		The compiled Cook-Torrance pixel shader.
	 */
	const CompiledPixelShader CreateCompiledCookTorrancePixelShader() noexcept;

	/**
	 Returns the compiled Lambertian bump pixel shader.

	 @return		The compiled Lambertian bump pixel shader.
	 */
	const CompiledPixelShader CreateCompiledLambertianBumpPixelShader() noexcept;

	/**
	 Returns the compiled Phong bump pixel shader.

	 @return		The compiled Phong bump pixel shader.
	 */
	const CompiledPixelShader CreateCompiledPhongBumpPixelShader() noexcept;

	/**
	 Returns the compiled Modified Phong bump pixel shader.

	 @return		The compiled Modified Phong bump pixel shader.
	 */
	const CompiledPixelShader CreateCompiledModifiedPhongBumpPixelShader() noexcept;

	/**
	 Returns the compiled Blinn-Phong bump pixel shader.

	 @return		The compiled Blinn-Phong bump pixel shader.
	 */
	const CompiledPixelShader CreateCompiledBlinnPhongBumpPixelShader() noexcept;

	/**
	 Returns the compiled Modified Blinn-Phong bump pixel shader.

	 @return		The compiled Modified Blinn-Phong bump pixel shader.
	 */
	const CompiledPixelShader CreateCompiledModifiedBlinnPhongBumpPixelShader() noexcept;

	/**
	 Returns the compiled Ward bump pixel shader.

	 @return		The compiled Ward bump pixel shader.
	 */
	const CompiledPixelShader CreateCompiledWardBumpPixelShader() noexcept;

	/**
	 Returns the compiled Ward-Duer bump pixel shader.

	 @return		The compiled Ward-Duer bump pixel shader.
	 */
	const CompiledPixelShader CreateCompiledWardDuerBumpPixelShader() noexcept;

	/**
	 Returns the compiled Cook-Torrance bump pixel shader.

	 @return		The compiled Cook-Torrance bump pixel shader.
	 */
	const CompiledPixelShader CreateCompiledCookTorranceBumpPixelShader() noexcept;

	/**
	 Returns the compiled sprite vertex shader.

	 @return		The compiled sprite vertex shader.
	 */
	const CompiledVertexShader CreateCompiledSpriteVertexShader() noexcept;

	/**
	 Returns the compiled sprite pixel shader.

	 @return		The compiled sprite pixel shader.
	 */
	const CompiledPixelShader CreateCompiledSpritePixelShader() noexcept;
}