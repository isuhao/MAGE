#ifndef MAGE_HEADER_HLSL
#define MAGE_HEADER_HLSL

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// DISABLE_INVERTED_Z_BUFFER             | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------

#define TRANSPARENCY_SHADOW_THRESHOLD 0.75f
#define TRANSPARENCY_SKIP_THRESHOLD   0.00392157f // ~  1/255
#define TRANSPARENCY_THRESHOLD        0.95686275f // ~244/255

#ifdef DISABLE_INVERTED_Z_BUFFER
	#define Z_NEAR 0.0f
	#define Z_FAR  1.0f
#else  // DISABLE_INVERTED_Z_BUFFER
	#define Z_FAR  0.0f
	#define Z_NEAR 1.0f
#endif // DISABLE_INVERTED_Z_BUFFER

//-----------------------------------------------------------------------------
// Engine Includes: Thread Configurations
//-----------------------------------------------------------------------------

#define MAGE_NVIDIA_WARP_SIZE   32
#define MAGE_AMD_WAFEFRONT_SIZE 64
#define GROUP_SIZE_2D_DEFAULT   16  // 16^2 = 256, 256/64 = 4
#define GROUP_SIZE_3D_DEFAULT    8  //  8^3 = 512, 512/64 = 8

#define GROUP_SIZE_MSAA_2X      16	// [numthreads( 2, 16, 16)] =  512
#define GROUP_SIZE_MSAA_4X      16	// [numthreads( 4, 16, 16)] = 1024
#define GROUP_SIZE_MSAA_8X       8	// [numthreads( 8,  8,  8)] =  512
#define GROUP_SIZE_SSAA_2X      16	// [numthreads( 4, 16, 16)] = 1024
#define GROUP_SIZE_SSAA_3X       8	// [numthreads( 9,  8,  8)] =  576
#define GROUP_SIZE_SSAA_4X       8	// [numthreads(16,  8,  8)] = 1024

//-----------------------------------------------------------------------------
// Engine Includes: Samplers
//-----------------------------------------------------------------------------

#define SLOT_SAMPLER_VARIABLE_0                    0
#define SLOT_SAMPLER_VARIABLE_1                    1
#define SLOT_SAMPLER_VARIABLE_2                    2
#define SLOT_SAMPLER_VARIABLE_3                    3

#define SLOT_SAMPLER_POINT_WRAP                    4
#define SLOT_SAMPLER_POINT_CLAMP                   5
#define SLOT_SAMPLER_POINT_MIRROR                  6
#define SLOT_SAMPLER_LINEAR_WRAP                   7
#define SLOT_SAMPLER_LINEAR_CLAMP                  8
#define SLOT_SAMPLER_LINEAR_MIRROR                 9
#define SLOT_SAMPLER_ANISOTROPIC_WRAP             10
#define SLOT_SAMPLER_ANISOTROPIC_CLAMP            11
#define SLOT_SAMPLER_ANISOTROPIC_MIRROR           12
#define SLOT_SAMPLER_PCF                          13

//-----------------------------------------------------------------------------
// Engine Includes: Constant Buffers 
//-----------------------------------------------------------------------------

#define SLOT_CBUFFER_GAME                          0
#define SLOT_CBUFFER_PRIMARY_CAMERA                1
#define SLOT_CBUFFER_COLOR                         2
#define SLOT_CBUFFER_LIGHTING                      2
#define SLOT_CBUFFER_MODEL                         3
#define SLOT_CBUFFER_SECONDARY_CAMERA              4

//-----------------------------------------------------------------------------
// Engine Includes: Light and Shadow Map SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_LIGHT_INDEX_LIST                  0
// Lights
#define SLOT_SRV_DIRECTIONAL_LIGHTS                1
#define SLOT_SRV_OMNI_LIGHTS                       2
#define SLOT_SRV_SPOT_LIGHTS                       3
#define SLOT_SRV_SHADOW_MAPPED_DIRECTIONAL_LIGHTS  4
#define SLOT_SRV_SHADOW_MAPPED_OMNI_LIGHTS         5
#define SLOT_SRV_SHADOW_MAPPED_SPOT_LIGHTS         6
// Shadow (Cube) Maps
#define SLOT_SRV_DIRECTIONAL_SHADOW_MAPS           7
#define SLOT_SRV_OMNI_SHADOW_MAPS                  8
#define SLOT_SRV_SPOT_SHADOW_MAPS                  9

//-----------------------------------------------------------------------------
// Engine Includes: Voxelization
//-----------------------------------------------------------------------------

#define SLOT_SRV_VOXEL_TEXTURE                    10

//-----------------------------------------------------------------------------
// Engine Includes: GBuffer SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_BASE_COLOR                       11
#define SLOT_SRV_MATERIAL                         12
#define SLOT_SRV_NORMAL                           13
#define SLOT_SRV_DEPTH                            14

//-----------------------------------------------------------------------------
// Engine Includes: General SRVs
//-----------------------------------------------------------------------------

#define SLOT_SRV_IMAGE                            SLOT_SRV_BASE_COLOR
#define SLOT_SRV_SPRITE                           SLOT_SRV_BASE_COLOR
#define SLOT_SRV_TEXTURE                          SLOT_SRV_BASE_COLOR

//-----------------------------------------------------------------------------
// Engine Includes: General UAVs
//-----------------------------------------------------------------------------

#define SLOT_UAV_IMAGE                             0
#define SLOT_UAV_NORMAL                            1
#define SLOT_UAV_DEPTH                             2

#define SLOT_UAV_VOXEL_BUFFER                      1
#define SLOT_UAV_VOXEL_TEXTURE                     2

#endif // MAGE_HEADER_HLSL