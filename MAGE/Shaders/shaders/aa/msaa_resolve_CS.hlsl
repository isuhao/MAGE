//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// GROUP_SIZE                               | GROUP_SIZE_2D_DEFAULT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D_MS(g_input_image_texture,   float4, SLOT_SRV_IMAGE);
TEXTURE_2D_MS(g_input_normal_texture,  float3, SLOT_SRV_NORMAL);
TEXTURE_2D_MS(g_input_depth_texture,   float,  SLOT_SRV_DEPTH);

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output_image_texture,  float4, SLOT_UAV_IMAGE);
RW_TEXTURE_2D(g_output_normal_texture, float3, SLOT_UAV_NORMAL);
RW_TEXTURE_2D(g_output_depth_texture,  float,  SLOT_UAV_DEPTH);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

#ifndef GROUP_SIZE
	#define GROUP_SIZE GROUP_SIZE_2D_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 p_display = g_viewport_top_left + thread_id.xy;
	
	[branch]
	if (any(p_display >= g_display_resolution)) {
		return;
	}

	uint2 dim;
	uint nb_samples;
	g_input_image_texture.GetDimensions(dim.x, dim.y, nb_samples);

	const float weight = 1.0f / nb_samples;

	float4 ldr        = 0.0f;
	float3 normal_sum = 0.0f;
	#ifdef DISABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
	#else  // DISABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
	#endif // DISABLE_INVERTED_Z_BUFFER

	// Resolve the (multi-sampled) radiance, normal and depth.
	for (uint i = 0u; i < nb_samples; ++i) {
		
		const float4 hdr = g_input_image_texture.sample[i][p_display];
		ldr += ToneMap_Max3(hdr, weight);

		normal_sum += g_input_normal_texture.sample[i][p_display];

		#ifdef DISABLE_INVERTED_Z_BUFFER
		depth = min(depth, g_input_depth_texture.sample[i][p_display]);
		#else  // DISABLE_INVERTED_Z_BUFFER
		depth = max(depth, g_input_depth_texture.sample[i][p_display]);
		#endif // DISABLE_INVERTED_Z_BUFFER
	}

	const float4 hdr    = InverseToneMap_Max3(ldr);
	const float3 normal = normalize(normal_sum);

	// Store the resolved radiance.
	g_output_image_texture[p_display]  = hdr;
	// Store the resolved normal.
	g_output_normal_texture[p_display] = normal;
	// Store the resolved depth.
	g_output_depth_texture[p_display]  = depth;
}