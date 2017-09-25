//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitives.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputNDCPosition VS(uint vertex_id: SV_VertexID) {
	PSInputNDCPosition output;
	output.p     = NearFullScreenTriangleNDC(vertex_id);
	output.p_ndc = output.p.xy;
	return output;
}