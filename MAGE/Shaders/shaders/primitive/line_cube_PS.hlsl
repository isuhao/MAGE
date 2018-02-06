//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(Color, SLOT_CBUFFER_COLOR) {
	// The color in linear space.
	float4 g_color : packoffset(c0);
};

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(float4 p : SV_Position) : SV_Target {
	return g_color;
}