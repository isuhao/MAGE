#ifndef MAGE_HEADER_GLOBAL
#define MAGE_HEADER_GLOBAL

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "..\src\hlsl.hpp"
#include "hlsl_syntax.hlsli"
#include "math.hlsli"
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Samplers
//-----------------------------------------------------------------------------
SAMPLER_STATE(g_variable_sampler0,          SLOT_SAMPLER_VARIABLE_0);
SAMPLER_STATE(g_variable_sampler1,          SLOT_SAMPLER_VARIABLE_1);
SAMPLER_STATE(g_variable_sampler2,          SLOT_SAMPLER_VARIABLE_2);
SAMPLER_STATE(g_variable_sampler3,          SLOT_SAMPLER_VARIABLE_3);

SAMPLER_STATE(g_point_wrap_sampler,         SLOT_SAMPLER_POINT_WRAP);
SAMPLER_STATE(g_point_clamp_sampler,        SLOT_SAMPLER_POINT_CLAMP);
SAMPLER_STATE(g_point_mirror_sampler,       SLOT_SAMPLER_POINT_MIRROR);
SAMPLER_STATE(g_linear_wrap_sampler,        SLOT_SAMPLER_LINEAR_WRAP);
SAMPLER_STATE(g_linear_clamp_sampler,       SLOT_SAMPLER_LINEAR_CLAMP);
SAMPLER_STATE(g_linear_mirror_sampler,      SLOT_SAMPLER_LINEAR_MIRROR);
SAMPLER_STATE(g_anisotropic_wrap_sampler,   SLOT_SAMPLER_ANISOTROPIC_WRAP);
SAMPLER_STATE(g_anisotropic_clamp_sampler,  SLOT_SAMPLER_ANISOTROPIC_CLAMP);
SAMPLER_STATE(g_anisotropic_mirror_sampler, SLOT_SAMPLER_ANISOTROPIC_MIRROR);

SAMPLER_COMPARISON_STATE(g_pcf_sampler,     SLOT_SAMPLER_PCF);

//-----------------------------------------------------------------------------
// Constant Buffers 
//-----------------------------------------------------------------------------

CBUFFER(World, SLOT_CBUFFER_WORLD) {

	//-------------------------------------------------------------------------
	// Member Variables: Display Resolution
	//-------------------------------------------------------------------------

	// The resolution of the display.
	// .x = the display width
	// .y = the display height
	uint2    g_display_resolution          : packoffset(c0);
	// The inverse of the resolution of the display.
	// g_display_inv_resolution = 1 / g_display_resolution
	float2   g_display_inv_resolution      : packoffset(c0.z);
	// The resolution of the super-sampled display.
	// .x = the super-sampled display width
	// .y = the super-sampled display height
	uint2    g_ss_display_resolution       : packoffset(c1);
	// The inverse of the resolution of the super-sampled display.
	// g_ss_display_inv_resolution = 1 / g_ss_display_resolution
	float2   g_ss_display_inv_resolution   : packoffset(c1.z);

	//-------------------------------------------------------------------------
	// Member Variables: Voxelization
	//-------------------------------------------------------------------------

	// The center of the voxel grid expressed in world space.
	float3   g_voxel_grid_center           : packoffset(c2.x);
	// The maximum mip level of the voxel texture.
	uint     g_voxel_texture_max_mip_level : packoffset(c2.w);
	// The resolution of the voxel grid for all dimensions.
	uint     g_voxel_grid_resolution       : packoffset(c3.x);
	// The inverse resolution of the voxel grid for all dimensions.
	float    g_voxel_grid_inv_resolution   : packoffset(c3.y);
	// The size of a voxel for all dimensions expressed in world space.
	float    g_voxel_size                  : packoffset(c3.z);
	// The inverse size of a voxel for all dimensions.
	float    g_voxel_inv_size              : packoffset(c3.w);

	//-------------------------------------------------------------------------
	// Member Variables: Time
	//-------------------------------------------------------------------------

	// The time.
	float    g_time                        : packoffset(c4.x);

	//-------------------------------------------------------------------------
	// Member Variables: Gamma Correction
	//-------------------------------------------------------------------------

	// The inverse of the gamma exponent used for gamma correction.
	float    g_inv_gamma                   : packoffset(c4.y);
};

CBUFFER(PrimaryCamera, SLOT_CBUFFER_PRIMARY_CAMERA) {
	
	//-------------------------------------------------------------------------
	// Member Variables: Transformations
	//-------------------------------------------------------------------------
	
	// The world-to-camera transformation matrix.
	float4x4 g_world_to_camera             : packoffset(c0);
	// The camera-to-projection transformation matrix.
	float4x4 g_camera_to_projection        : packoffset(c4);
	// The projection-to-camera transformation matrix.
	float4x4 g_projection_to_camera        : packoffset(c8);
	// The camera-to-world transformation matrix.
	float4x4 g_camera_to_world             : packoffset(c12);

	//-------------------------------------------------------------------------
	// Member Variables: Viewports
	//-------------------------------------------------------------------------

	// The top left corner of the camera viewport.
	float2   g_viewport_top_left           : packoffset(c16);
	// The resolution of the camera viewport.
	// .x = the viewport width
	// .y = the viewport height
	uint2    g_viewport_resolution         : packoffset(c16.z);
	// The top left corner of the super-sampled camera viewport.
	float2   g_ss_viewport_top_left        : packoffset(c17);
	// The resolution of the super-sampled camera viewport.
	// .x = the super-sampled viewport width
	// .y = the super-sampled viewport height
	uint2    g_ss_viewport_resolution      : packoffset(c17.z);
	// The inverse of the resolution of the camera viewport.
	// g_viewport_inv_resolution = 1 / g_viewport_resolution
	float2   g_viewport_inv_resolution     : packoffset(c18);
	// The inverse of the resolution of the super-sampled camera viewport.
	// g_ss_viewport_inv_resolution = 1 / g_ss_viewport_resolution
	float2   g_ss_viewport_inv_resolution  : packoffset(c18.z);
	
	//-------------------------------------------------------------------------
	// Member Variables: Fog
	//-------------------------------------------------------------------------

	// The (linear) color of the fog.
	float3   g_fog_color                   : packoffset(c19);
	// The density of the fog.
	float    g_fog_density                 : packoffset(c19.w);

	//-------------------------------------------------------------------------
	// Member Variables: Sky
	//-------------------------------------------------------------------------

	// The scaling factor of the z component of sky domes.
	float    g_sky_dome_scale_z            : packoffset(c20.x);

	//-------------------------------------------------------------------------
	// Member Variables: Voxel Cone Tracing
	//-------------------------------------------------------------------------

	// The step multiplier of the cone while marching.
	// A high step multiplier results in faster, but less-precise marching.
	// A low  step multiplier results in slower, but more-precise marching.
	float    g_cone_step_multiplier        : packoffset(c20.y);
	// The maximal cone distance expressed in normalized texture coordinates.
	float    g_max_cone_distance           : packoffset(c20.z);

	//-------------------------------------------------------------------------
	// Member Variables: Post-processing
	//-------------------------------------------------------------------------

	// The lens radius of this camera.
	float    g_lens_radius                 : packoffset(c20.w);
	// The focal length of this camera.
	float    g_focal_length                : packoffset(c21.x);
	// The maximum circle-of-confusion radius of this camera.
	float    g_max_coc_radius              : packoffset(c21.y);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Transformations
//-----------------------------------------------------------------------------
// world                  <-> voxel UVW                
// world                  <-> voxel index
// 
// NDC                     -> world
// depth (= NDC z)         -> camera z
// 
// display                <-> viewport
// super-sampled display  <-> super-sampled viewport
// display                <-> UV
// super-sampled display  <-> UV
// viewport               <-> UV
// super-sampled viewport <-> UV

/**
 Returns the position of the camera expressed in world space.

 @return		The position of the camera expressed in world space.
 */
float3 GetCameraPosition() {
	return g_camera_to_world._m30_m31_m32;
}

/**
 Converts the given position expressed in world space to the corresponding 
 voxel UVW coordinates.

 @param[in]		p_world
				The position expressed in world space.
 @return		The voxel UVW coordinates.
 */
float3 WorldToVoxelUVW(float3 p_world) {
	const float3 voxel = (p_world - g_voxel_grid_center) * g_voxel_inv_size 
		               * g_voxel_grid_inv_resolution;
	// [-1/2,1/2]^3 -> [0,1]x[1,0]x[0,1]
	return float3(1.0f, -1.0f, 1.0f) * voxel + 0.5f;
}

/**
 Converts the given voxel UVW coordinates to the corresponding position 
 expressed in world space.

 @param[in]		uvw
				The voxel UVW coordinates.
 @return		The position expressed in world space.
 */
float3 VoxelUVWtoWorld(float3 uvw) {
	// [0,1]x[1,0]x[0,1] -> [-1/2,1/2]^3
	const float3 voxel = float3( 1.0f, -1.0f,  1.0f) * uvw
		               + float3(-0.5f,  0.5f, -0.5f);
	return g_voxel_grid_center + voxel * g_voxel_size * g_voxel_grid_resolution;
}

/**
 Converts the given position expressed in world space to the corresponding 
 voxel index.

 @param[in]		p_world
				The position expressed in world space.
 @return		The voxel index.
 */
int3 WorldToVoxelIndex(float3 p_world) {
	const float3 voxel = (p_world - g_voxel_grid_center) * g_voxel_inv_size 
		               + 0.5f * g_voxel_grid_resolution;
	// [0,R)^3 -> [0,R)x(R,0]x[0,R)
	return int3(0, g_voxel_grid_resolution, 0) + int3(1, -1, 1) * floor(voxel);
}

/**
 Converts the given voxel index to the corresponding position expressed in 
 world space (i.e. left, lower, near corner of the voxel).

 @param[in]		p_world
				The position expressed in world space.
 @return		The voxel index.
 */
float3 VoxelIndexToWorld(uint3 voxel_index) {
	// [0,R]x[R,0]x[0,R] -> [-R/2,R/2]^3
	const float3 voxel = float3( 1.0f, -1.0f,  1.0f) * voxel_index
		               + float3(-0.5f,  0.5f, -0.5f) * g_voxel_grid_resolution;
	return g_voxel_grid_center + voxel * g_voxel_size;
}

/**
 Converts the given position expressed in NDC space to the corresponding 
 position expressed in world space.

 @param[in]		p_ndc
				The position expressed in NDC space.
 @return		The position expressed in world space.
 */
float3 NDCToWorld(float3 p_ndc) {
	const float4 p_hcamera = mul(float4(p_ndc, 1.0f), g_projection_to_camera);
	const float3 p_camera  = HomogeneousDivide(p_hcamera);
	return mul(float4(p_camera, 1.0f), g_camera_to_world).xyz;
}

/**
 Converts the given (non-linear) depth expressed in NDC space to the 
 corresponding (linear) depth expressed in camera space.

 @param[in]		depth
				The (non-linear) depth expressed in NDC space.
 @return		The (linear) depth expressed in camera space.
 */
float DepthToCameraZ(float depth) {
	const float2 p_camera_zw = mul(float4(0.0f, 0.0f, depth, 1.0f), 
								   g_projection_to_camera).zw;
	return p_camera_zw.x / p_camera_zw.y;
}

/**
 Converts the given position expressed in display space to the corresponding 
 position expressed in viewport space.

 @param[in]		p_display
				The position expressed in display space.
 @return		The position expressed in viewport space.
 */
float2 DisplayToViewport(float2 p_display) {
	return p_display - g_viewport_top_left;
}

/**
 Converts the given position expressed in super-sampled display space to the 
 corresponding position expressed in super-sampled viewport space.

 @param[in]		p_ss_display
				The position expressed in super-sampled display space.
 @return		The position expressed in super-sampled viewport space.
 */
float2 SSDisplayToSSViewport(float2 p_ss_display) {
	return p_ss_display - g_ss_viewport_top_left;
}

/**
 Converts the given position expressed in viewport space to the corresponding 
 position expressed in display space.

 @param[in]		p_viewport
				The position expressed in viewport space.
 @return		The position expressed in display space.
 */
float2 ViewportToDisplay(float2 p_viewport) {
	return g_viewport_top_left + p_viewport;
}

/**
 Converts the given position expressed in super-sampled viewport space to the 
 corresponding position expressed in super-sampled display space.

 @param[in]		p_ss_viewport
				The position expressed in super-sampled viewport space.
 @return		The position expressed in super-sampled display space.
 */
float2 SSViewportToSSDisplay(float2 p_ss_viewport) {
	return g_ss_viewport_top_left + p_ss_viewport;
}

/**
 Converts the given position expressed in display space to the corresponding 
 position expressed in UV space.

 @param[in]		p_display
				The position expressed in display space.
 @return		The position expressed in UV space.
 */
float2 DisplayToUV(float2 p_display) {
	// .x: [0, g_display_resolution.x] -> [0,1]
	// .y: [0, g_display_resolution.y] -> [0,1]
	return p_display * g_display_inv_resolution;
}

/**
 Converts the given position expressed in super-sampled display space to the 
 corresponding position expressed in UV space.

 @param[in]		p_ss_display
				The position expressed in super-sampled display space.
 @return		The position expressed in UV space.
 */
float2 SSDisplayToUV(float2 p_ss_display) {
	// .x: [0, g_ss_display_resolution.x] -> [0,1]
	// .y: [0, g_ss_display_resolution.y] -> [0,1]
	return p_ss_display * g_ss_display_inv_resolution;
}

/**
 Converts the given position expressed in viewport space to the corresponding 
 position expressed in UV space.

 @param[in]		p_viewport
				The position expressed in viewport space.
 @return		The position expressed in UV space.
 */
float2 ViewportToUV(float2 p_viewport) {
	// .x: [0, g_viewport_resolution.x] -> [0,1]
	// .y: [0, g_viewport_resolution.y] -> [0,1]
	return p_viewport * g_viewport_inv_resolution;
}

/**
 Converts the given position expressed in super-sampled viewport space to the 
 corresponding position expressed in UV space.

 @param[in]		p_ss_viewport
				The position expressed in super-sampled viewport space.
 @return		The position expressed in UV space.
 */
float2 SSViewportToUV(float2 p_ss_viewport) {
	// .x: [0, g_ss_viewport_resolution.x] -> [0,1]
	// .y: [0, g_ss_viewport_resolution.y] -> [0,1]
	return p_ss_viewport * g_ss_viewport_inv_resolution;
}

/**
 Converts the given position expressed in super-sampled viewport space to the 
 corresponding position expressed in UV space.

 @param[in]		p_ss_viewport
				The position expressed in super-sampled viewport space.
 @return		The position expressed in UV space.
 */
float2 SSViewportToUV(uint2 p_ss_viewport) {
	return SSViewportToUV((float2)p_ss_viewport + 0.5f);
}

/**
 Converts the given position expressed in UV space to the corresponding 
 position expressed in display space.

 @param[in]		uv
				The position expressed in UV space.
 @return		The position expressed in display space.
 */
float2 UVtoDisplay(float2 uv) {
	// .x: [0,1] -> [0, g_display_resolution.x]
	// .y: [0,1] -> [0, g_display_resolution.y]
	return uv * g_display_resolution;
}

/**
 Converts the given position expressed in UV space to the corresponding 
 position expressed in super-sampled display space.

 @param[in]		uv
				The position expressed in UV space.
 @return		The position expressed in super-sampled display space.
 */
float2 UVtoSSDisplay(float2 uv) {
	// .x: [0,1] -> [0, g_ss_display_resolution.x]
	// .y: [0,1] -> [0, g_ss_display_resolution.y]
	return uv * g_ss_display_resolution;
}

/**
 Converts the given position expressed in UV space to the corresponding 
 position expressed in viewport space.

 @param[in]		uv
				The position expressed in UV space.
 @return		The position expressed in viewport space.
 */
float2 UVtoViewport(float2 uv) {
	// .x: [0,1] -> [0, g_viewport_resolution.x]
	// .y: [0,1] -> [0, g_viewport_resolution.y]
	return uv * g_viewport_resolution;
}

/**
 Converts the given position expressed in UV space to the corresponding 
 position expressed in super-sampled viewport space.

 @param[in]		uv
				The position expressed in UV space.
 @return		The position expressed in super-sampled viewport space.
 */
float2 UVtoSSViewport(float2 uv) {
	// .x: [0,1] -> [0, g_ss_viewport_resolution.x]
	// .y: [0,1] -> [0, g_ss_viewport_resolution.y]
	return uv * g_ss_viewport_resolution;
}

/**
 Checks whether the given position expressed in viewport space is out of 
 bounds.

 @param[in]		p_viewport
				The position expressed in viewport space.
 @return		@c true if the given position expressed in viewport space 
				is out of bounds.
 */
bool IsViewportOutOfBounds(uint2 p_viewport) {
	const  int2 p_display_s = ViewportToDisplay(p_viewport);
	const uint2 p_display   = uint2(p_display_s);

	return any(0 > p_display_s 
			   || g_display_resolution  <= p_display 
			   || g_viewport_resolution <= p_viewport);
}

/**
 Checks whether the given position expressed in viewport space is out of 
 bounds.

 @param[in]		p_viewport
				The position expressed in viewport space.
 @param[out]	p_display
				The position expressed in display space.
 @return		@c true if the given position expressed in viewport space 
				is out of bounds.
 */
bool IsViewportOutOfBounds(uint2 p_viewport, out uint2 p_display) {
	const int2 p_display_s = ViewportToDisplay(p_viewport);
	p_display = uint2(p_display_s);

	return any(0 > p_display_s 
			   || g_display_resolution  <= p_display 
			   || g_viewport_resolution <= p_viewport);
}

#endif // MAGE_HEADER_GLOBAL