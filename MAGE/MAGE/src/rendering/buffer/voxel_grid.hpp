#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class VoxelGrid final {

	public:

		explicit VoxelGrid(size_t resolution);
		explicit VoxelGrid(ID3D11Device5 *device, size_t resolution);
		VoxelGrid(const VoxelGrid &voxel_grid) = delete;
		VoxelGrid(VoxelGrid &&voxel_grid) = default;
		~VoxelGrid() = default;

		VoxelGrid &operator=(const VoxelGrid &voxel_grid) = delete;
		VoxelGrid &operator=(VoxelGrid &&voxel_grid) = delete;

	private:

		void SetupVoxelGrid(ID3D11Device5 *device);

		void SetupVoxelGridStructuredBuffer(ID3D11Device5 *device);
		void SetupVoxelGridTexture(ID3D11Device5 *device);

		size_t m_resolution;

		ComPtr< ID3D11ShaderResourceView > m_grid_srv;
		ComPtr< ID3D11UnorderedAccessView > m_grid_uav;

		ComPtr< ID3D11ShaderResourceView > m_texture_srv;
		ComPtr< ID3D11UnorderedAccessView > m_texture_uav;
	};
}