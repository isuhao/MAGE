#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct TransformBuffer final {

	public:

		TransformBuffer(const Camera &camera);
		TransformBuffer(const TransformBuffer &buffer) = default;
		~TransformBuffer() = default;
		TransformBuffer &operator=(const TransformBuffer &buffer) = default;

		void SetModelToWorld(const XMMATRIX &model_to_world) const {
			m_model_to_world = XMMatrixTranspose(model_to_world);
		}

	private:

		mutable XMMATRIX m_model_to_world;
		XMMATRIX m_world_to_view;
		XMMATRIX m_world_to_view_inverse_transpose;
		XMMATRIX m_view_to_projection;
	};
}