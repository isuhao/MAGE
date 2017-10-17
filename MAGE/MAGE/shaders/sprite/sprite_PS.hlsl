//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_sprite, float4, SLOT_SRV_SPRITE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputColorTexture input) : SV_Target {
	// Gr := (C1 * C2)^(1/gamma) = C1^(1/gamma) C2^(1/gamma)
	return g_sprite.Sample(g_linear_wrap_sampler, input.tex) * input.color;
}