//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// MSAA_AS_SSAA                             | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define DISABLE_BASE_COLOR_TEXTURE
#define DISABLE_TSNM
#include "forward\forward_input.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
#ifdef MSAA_AS_SSAA
float4 PS(PSInputPositionNormalTexture input, 
		  uint index : SV_SampleIndex) : SV_Target {
#else  // MSAA_AS_SSAA
float4 PS(PSInputPositionNormalTexture input) : SV_Target {
#endif // MSAA_AS_SSAA

	// Obtain the roughness of the material.
	const float roughness = GetMaterialParameters(input.tex_material).x;
	
	return float4(roughness, roughness, roughness, 1.0f);
}