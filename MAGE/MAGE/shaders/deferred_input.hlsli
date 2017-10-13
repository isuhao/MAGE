//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerFrame, SLOT_CBUFFER_PER_FRAME) {
	// CAMERA
	// The projection values of the view-to-projection transformation matrix.
	// g_projection_values.x = 1 / view_to_projection00
	// g_projection_values.y = 1 / view_to_projection11
	// g_projection_values.z =  view_to_projection32
	// g_projection_values.w = -view_to_projection22
	float4 g_projection_values : packoffset(c0);
};

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_base_color_texture, float4, SLOT_SRV_BASE_COLOR);
TEXTURE_2D(g_material_texture,   float4, SLOT_SRV_MATERIAL);
TEXTURE_2D(g_normal_texture,     float3, SLOT_SRV_NORMAL);
TEXTURE_2D(g_depth_texture,      float,  SLOT_SRV_DEPTH);

//-----------------------------------------------------------------------------
// Definitions and Declarations
//-----------------------------------------------------------------------------

/**
 Returns the base color of the material from the GBuffer corresponding to the 
 given location.

 @param[in]		location
				The location.
 @return		The base color of the material from the GBuffer corresponding 
				to the given location.
 */
float3 GetGBufferMaterialBaseColor(float2 location) {
	// Load the base color from the GBuffer base color texture.
	return g_base_color_texture[location].xyz;
}

/**
 Returns the parameters of the material from the GBuffer corresponding to the 
 given location.

 @param[in]		location
				The location.
 @return		The parameters of the material [roughness, metalness] from the 
				GBuffer corresponding to the given location.
 */
float2 GetGBufferMaterialParameters(float2 location) {
	// Load the material data the GBuffer material texture.
	return g_material_texture[location].xy;
}

/**
 Returns the view-space normal from the GBuffer corresponding to the given 
 location.

 @param[in]		location
				The location.
 @return		The view-space normal from the GBuffer corresponding to the 
				given location.
 */
float3 GetGBufferNormal(float2 location) {
	// Load and unpack the view-space normal from the GBuffer normal texture.
	return UnpackNormal(g_normal_texture[location]);
}

/**
 Returns the view-space position from the GBuffer corresponding to the given 
 location.

 @param[in]		p_ndc_xy
				The x and y coordinates of the NDC-space hit position.
 @param[in]		location
				The location.
 @return		The view-space position from the GBuffer corresponding to the 
				given location.
 */
float3 GetGBufferPosition(float2 location, float2 p_ndc_xy) {
	// Load the depth from the GBuffer depth texture.
	const float depth  = g_depth_texture[location];
	// Obtain the NDC space coodinates.
	const float3 p_ndc = float3(p_ndc_xy, depth);
	// Obtain the view space coodinates.
	return NDCtoView(p_ndc, g_projection_values);
}