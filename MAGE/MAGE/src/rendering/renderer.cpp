//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\renderer.hpp"
#include "rendering\output_manager.hpp"
#include "rendering\state_manager.hpp"
#include "rendering\pass\aa_pass.hpp"
#include "rendering\pass\back_buffer_pass.hpp"
#include "rendering\pass\bounding_volume_pass.hpp"
#include "rendering\pass\deferred_pass.hpp"
#include "rendering\pass\depth_pass.hpp"
#include "rendering\pass\dof_pass.hpp"
#include "rendering\pass\forward_pass.hpp"
#include "rendering\pass\lbuffer_pass.hpp"
#include "rendering\pass\sky_pass.hpp"
#include "rendering\pass\sprite_pass.hpp"
#include "rendering\pass\voxelization_pass.hpp"
#include "rendering\pass\voxel_grid_pass.hpp"
#include "rendering\buffer\game_buffer.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//TODO
	constexpr U32 g_voxel_grid_resolution = 128u;
	constexpr F32 g_voxel_size = 0.08f;

	//-------------------------------------------------------------------------
	// Renderer::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of renderers.
	 */
	class Renderer::Impl final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a renderer.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a display_configuration is not equal to @c nullptr.
		 @pre			@a swap_chain is not equal to @c nullptr.
		 @pre			@a resource_manager is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		display_configuration
						A pointer to the display configuration.
		 @param[in]		swap_chain
						A pointer to the swap chain.
		 @param[in]		resource_manager
						A pointer to the resource manager.
		 */
		explicit Impl(ID3D11Device *device, 
					  ID3D11DeviceContext *device_context, 
					  DisplayConfiguration *display_configuration, 
					  SwapChain *swap_chain,
					  ResourceManager *resource_manager);

		/**
		 Constructs a renderer from the given renderer.

		 @param[in]		renderer
						A reference to the renderer to copy.
		 */
		Impl(const Impl &renderer) = delete;

		/**
		 Constructs a renderer by moving the given renderer.

		 @param[in]		renderer
						A reference to the renderer to move.
		 */
		Impl(Impl &&renderer) noexcept;

		/**
		 Destructs this renderer.
		 */
		~Impl();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given renderer to this renderer.

		 @param[in]		renderer
						A reference to the renderer to copy.
		 @return		A reference to the copy of the given renderer (i.e. 
						this renderer).
		 */
		Impl &operator=(const Impl &renderer) = delete;

		/**
		 Moves the given renderer to this renderer.

		 @param[in]		renderer
						A reference to the renderer to move.
		 @return		A reference to the moved renderer (i.e. this renderer).
		 */
		Impl &operator=(Impl &&renderer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the persistent state of this renderer.

		 @throws		Exception
						Failed to bind the persistent state of this renderer.
		 */
		void BindPersistentState();

		/**
		 Renders the given scene.

		 @param[in]		scene
						A reference to the scene.
		 @throws		Exception
						Failed to render the scene.
		 */
		void Render(const Scene &scene);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void UpdateBuffers(const Scene &scene) const;
		
		void Render(const Scene &scene, const Camera &camera);
		
		void XM_CALLCONV RenderForward(const Scene &scene, 
									   const Camera &camera, 
									   FXMMATRIX world_to_projection);
		
		void XM_CALLCONV RenderDeferred(const Scene &scene, 
										const Camera &camera, 
										FXMMATRIX world_to_projection);
		
		void XM_CALLCONV RenderSolid(const Scene &scene, 
									 const Camera &camera, 
									 FXMMATRIX world_to_projection);

		void XM_CALLCONV RenderFalseColor(const Scene &scene, 
										  const Camera &camera,
										  FXMMATRIX world_to_projection, 
										  FalseColor false_color);
		
		void XM_CALLCONV RenderVoxelGrid(const Scene &scene, 
										 const Camera &camera, 
										 FXMMATRIX world_to_projection);
		
		void RenderAA(const Camera &camera);
		
		void RenderPostProcessing(const Camera &camera);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the display configuration of this renderer.
		 */
		DisplayConfiguration * const m_display_configuration;

		/**
		 A pointer to the device of this renderer.
		 */
		ID3D11Device * const m_device;

		/**
		 A pointer to the device context of this renderer.
		 */
		ID3D11DeviceContext * const m_device_context;

		/**
		 A pointer to the resource manager of this renderer.
		 */
		ResourceManager * const m_resource_manager;

		/**
		 A pointer to the output manager of this rendering manager.
		 */
		UniquePtr< OutputManager > m_output_manager;

		/**
		 A pointer to the state manager of this rendering manager.
		 */
		UniquePtr< StateManager > m_state_manager;

		//---------------------------------------------------------------------
		// Member Variables: Buffers
		//---------------------------------------------------------------------

		/**
		 A pointer to the game buffer of this renderer.
		 */
		ConstantBuffer< GameBuffer > m_game_buffer;

		//---------------------------------------------------------------------
		// Member Variables: Render Passes
		//---------------------------------------------------------------------

		/**
		 A pointer to the AA pass of this renderer.
		 */
		UniquePtr< AAPass > m_aa_pass;

		/**
		 A pointer to the back buffer pass of this renderer.
		 */
		UniquePtr< BackBufferPass > m_back_buffer_pass;

		/**
		 A pointer to the bounding volume pass of this renderer.
		 */
		UniquePtr< BoundingVolumePass > m_bounding_volume_pass;

		/**
		 A pointer to the deferred pass of this renderer.
		 */
		UniquePtr< DeferredPass > m_deferred_pass;

		/**
		 A pointer to the depth pass of this renderer.
		 */
		UniquePtr< DepthPass > m_depth_pass;

		/**
		 A pointer to the depth-of-field pass of this renderer.
		 */
		UniquePtr< DOFPass > m_dof_pass;

		/**
		 A pointer to the forward pass of this renderer.
		 */
		UniquePtr< ForwardPass > m_forward_pass;

		/**
		 A pointer to the LBuffer pass of this renderer.
		 */
		UniquePtr< LBufferPass >  m_lbuffer_pass;

		/**
		 A pointer to the sky pass of this renderer.
		 */
		UniquePtr< SkyPass > m_sky_pass;

		/**
		 A pointer to the sprite pass of this renderer.
		 */
		UniquePtr< SpritePass > m_sprite_pass;

		/**
		 A pointer to the voxelization pass of this renderer.
		 */
		UniquePtr< VoxelizationPass > m_voxelization_pass;

		/**
		 A pointer to the voxel grid pass of this renderer.
		 */
		UniquePtr< VoxelGridPass > m_voxel_grid_pass;
	};

	Renderer::Impl::Impl(ID3D11Device *device, 
						 ID3D11DeviceContext *device_context, 
						 DisplayConfiguration *display_configuration, 
						 SwapChain *swap_chain, 
						 ResourceManager *resource_manager)
		: m_display_configuration(display_configuration),
		m_device(device), 
		m_device_context(device_context), 
		m_resource_manager(resource_manager),
		m_output_manager(MakeUnique< OutputManager >(device, 
													 display_configuration, 
													 swap_chain)),
		m_state_manager(MakeUnique< StateManager >(device)),
		m_game_buffer(device),
		m_aa_pass(MakeUnique< AAPass >()),
		m_back_buffer_pass(MakeUnique< BackBufferPass >()),
		m_bounding_volume_pass(MakeUnique< BoundingVolumePass >()),
		m_deferred_pass(MakeUnique< DeferredPass >()),
		m_depth_pass(MakeUnique< DepthPass >()),
		m_dof_pass(MakeUnique< DOFPass >()),
		m_forward_pass(MakeUnique< ForwardPass >()),
		m_lbuffer_pass(MakeUnique< LBufferPass >()),
		m_sky_pass(MakeUnique< SkyPass >()),
		m_sprite_pass(MakeUnique< SpritePass >()),
		m_voxelization_pass(MakeUnique< VoxelizationPass >()),
		m_voxel_grid_pass(MakeUnique< VoxelGridPass >()) {

		Assert(m_display_configuration);
		Assert(m_device);
		Assert(m_device_context);
		Assert(m_resource_manager);
	}
	
	Renderer::Impl::Impl(Impl &&scene_renderer) noexcept = default;
	
	Renderer::Impl::~Impl() = default;

	void Renderer::Impl::BindPersistentState() {
		m_state_manager->BindPersistentState(m_device_context);
		
		GameBuffer buffer;
		buffer.m_display_width                = m_display_configuration->GetDisplayWidth();
		buffer.m_display_height               = m_display_configuration->GetDisplayHeight();
		buffer.m_display_inv_width_minus1     = 1.0f / (buffer.m_display_width  - 1.0f);
		buffer.m_display_inv_height_minus1    = 1.0f / (buffer.m_display_height - 1.0f);
		
		buffer.m_ss_display_width             = m_display_configuration->GetSSDisplayWidth();
		buffer.m_ss_display_height            = m_display_configuration->GetSSDisplayHeight();
		buffer.m_ss_display_inv_width_minus1  = 1.0f / (buffer.m_ss_display_width  - 1.0f);
		buffer.m_ss_display_inv_height_minus1 = 1.0f / (buffer.m_ss_display_height - 1.0f);
		
		buffer.m_gamma                        = m_display_configuration->GetGamma();
		buffer.m_inv_gamma                    = 1.0f / buffer.m_gamma;

		//TODO
		buffer.m_voxel_grid_resolution        = g_voxel_grid_resolution;
		buffer.m_voxel_grid_inv_resolution    = 1.0f / buffer.m_voxel_grid_resolution;
		buffer.m_voxel_size                   = g_voxel_size;
		buffer.m_voxel_inv_size               = 1.0f / buffer.m_voxel_size;

		// Update the game buffer.
		m_game_buffer.UpdateData(m_device_context, buffer);
		// Bind the game buffer.
		m_game_buffer.Bind< Pipeline >(m_device_context, SLOT_CBUFFER_GAME);
	}

	void Renderer::Impl::Render(const Scene &scene) {
		// Update the buffers.
		UpdateBuffers(scene);

		// Render the scene for each camera.
		scene.ForEach< Camera >([this, &scene](const Camera &camera) {
			if (State::Active != camera.GetState()) {
				return;
			}

			// Render the scene.
			Render(scene, camera);
		});

		// Bind the maximum viewport.
		const Viewport viewport(m_display_configuration->GetDisplayWidth(),
								m_display_configuration->GetDisplayHeight());
		viewport.BindViewport(m_device_context);

		// Perform a sprite pass.
		m_sprite_pass->Render(scene);
	}

	void Renderer::Impl::UpdateBuffers(const Scene &scene) const {
		// Update the buffer of each camera.
		scene.ForEach< Camera >(
			[device_context(m_device_context)](const Camera &camera) {
				if (State::Active == camera.GetState()) {
					camera.UpdateBuffer(device_context);
				}
			}
		);

		// Update the buffer of each model.
		scene.ForEach< Model >(
			[device_context(m_device_context)](const Model &model) {
				if (State::Active == model.GetState()) {
					model.UpdateBuffer(device_context);
				}
			}
		);
	}

	void Renderer::Impl::Render(const Scene &scene, const Camera &camera) {
		// Bind the camera to the pipeline.
		camera.BindBuffer< Pipeline >(m_device_context,
									  SLOT_CBUFFER_PRIMARY_CAMERA);

		// Obtain the world-to-projection transformation matrix of the 
		// camera for view frustum culling.
		const auto &transform           = camera.GetOwner()->GetTransform();
		const auto world_to_camera      = transform.GetWorldToObjectMatrix();
		const auto camera_to_projection = camera.GetCameraToProjectionMatrix();
		const auto world_to_projection  = world_to_camera * camera_to_projection;

		const auto render_mode          = camera.GetSettings().GetRenderMode();

		m_output_manager->BindBegin(m_device_context);

		//---------------------------------------------------------------------
		// RenderMode
		//---------------------------------------------------------------------
		switch (render_mode) {

		case RenderMode::Forward: {
			RenderForward(scene, camera, world_to_projection);
			break;
		}
		
		case RenderMode::Deferred: {
			RenderDeferred(scene, camera, world_to_projection);
			break;
		}
		
		case RenderMode::Solid: {
			RenderSolid(scene, camera, world_to_projection);
			break;
		}
		
		case RenderMode::VoxelGrid: {
			RenderVoxelGrid(scene, camera, world_to_projection);
			break;
		}

		case RenderMode::FalseColor_BaseColor: {
			RenderFalseColor(scene, camera, world_to_projection, 
							 FalseColor::BaseColor);
			break;
		}
		case RenderMode::FalseColor_BaseColorCoefficient: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::BaseColorCoefficient);
			break;
		}
		case RenderMode::FalseColor_BaseColorTexture: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::BaseColorTexture);
			break;
		}
		case RenderMode::FalseColor_Material: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Material);
			break;
		}
		case RenderMode::FalseColor_MaterialCoefficient: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::MaterialCoefficient);
			break;
		}
		case RenderMode::FalseColor_MaterialTexture: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::MaterialTexture);
			break;
		}
		case RenderMode::FalseColor_Roughness: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Roughness);
			break;
		}
		case RenderMode::FalseColor_RoughnessCoefficient: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::RoughnessCoefficient);
			break;
		}
		case RenderMode::FalseColor_RoughnessTexture: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::RoughnessTexture);
			break;
		}
		case RenderMode::FalseColor_Metalness: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Metalness);
			break;
		}
		case RenderMode::FalseColor_MetalnessCoefficient: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::MetalnessCoefficient);
			break;
		}
		case RenderMode::FalseColor_MetalnessTexture: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::MetalnessTexture);
			break;
		}
		case RenderMode::FalseColor_ShadingNormal: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::ShadingNormal);
			break;
		}
		case RenderMode::FalseColor_TSNMShadingNormal: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::TSNMShadingNormal);
			break;
		}
		case RenderMode::FalseColor_Depth: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Depth);
			break;
		}
		case RenderMode::FalseColor_Distance: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::Distance);
			break;
		}
		case RenderMode::FalseColor_UV: {
			RenderFalseColor(scene, camera, world_to_projection,
							 FalseColor::UV);
			break;
		}

		default: {
			camera.BindSSViewport(m_device_context);
			m_output_manager->BindBeginForward(m_device_context);

			break;
		}

		}

		//---------------------------------------------------------------------
		// RenderLayer
		//---------------------------------------------------------------------
		const auto &settings = camera.GetSettings();
		if (settings.ContainsRenderLayer(RenderLayer::Wireframe)) {
			m_forward_pass->RenderWireframe(scene, world_to_projection);
		}
		if (settings.ContainsRenderLayer(RenderLayer::AABB)) {
			m_bounding_volume_pass->Render(scene, world_to_projection);
		}

		m_output_manager->BindEndForward(m_device_context);

		//---------------------------------------------------------------------
		// Anti-aliasing
		//---------------------------------------------------------------------
		
		RenderAA(camera);

		//---------------------------------------------------------------------
		// Post-processing
		//---------------------------------------------------------------------
		
		RenderPostProcessing(camera);

		//---------------------------------------------------------------------
		// Back Buffer
		//---------------------------------------------------------------------
		
		m_output_manager->BindEnd(m_device_context);

		// Perform a back buffer pass.
		m_back_buffer_pass->Render();
	}

	void XM_CALLCONV Renderer::Impl::RenderForward(const Scene &scene,
												   const Camera &camera,
												   FXMMATRIX world_to_projection) {
		const auto vct = false;

		//---------------------------------------------------------------------
		// LBuffer
		//---------------------------------------------------------------------
		m_lbuffer_pass->Render(scene, world_to_projection,
							   camera.GetSettings().GetFog());

		//---------------------------------------------------------------------
		// Voxelization
		//---------------------------------------------------------------------
		if (vct) {
			//TODO
			const auto r = g_voxel_grid_resolution * 0.5f * g_voxel_size;
			const auto world_to_voxel = XMMatrixOrthographicOffCenterLH(-r, r,
																		-r, r,
																		-r, r);
			m_voxelization_pass->Render(scene, world_to_voxel,
										camera.GetSettings().GetBRDF(),
										g_voxel_grid_resolution);
		}

		camera.BindSSViewport(m_device_context);
		m_output_manager->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Forward: opaque fragments
		//---------------------------------------------------------------------
		m_forward_pass->Render(scene, world_to_projection,
							   camera.GetSettings().GetBRDF(), vct);

		//---------------------------------------------------------------------
		// Sky
		//---------------------------------------------------------------------
		m_sky_pass->Render(camera.GetSettings().GetSky());

		//---------------------------------------------------------------------
		// Forward: transparent fragments
		//---------------------------------------------------------------------
		m_forward_pass->RenderTransparent(scene, world_to_projection,
										  camera.GetSettings().GetBRDF(), vct);
	}

	void XM_CALLCONV Renderer::Impl::RenderDeferred(const Scene &scene, 
													const Camera &camera, 
													FXMMATRIX world_to_projection) {
		const auto vct = false;

		//---------------------------------------------------------------------
		// LBuffer
		//---------------------------------------------------------------------
		m_lbuffer_pass->Render(scene, world_to_projection,
							   camera.GetSettings().GetFog());

		//---------------------------------------------------------------------
		// Voxelization
		//---------------------------------------------------------------------
		if (vct) {
			//TODO
			const auto r = g_voxel_grid_resolution * 0.5f * g_voxel_size;
			const auto world_to_voxel = XMMatrixOrthographicOffCenterLH(-r, r,
																		-r, r,
																		-r, r);
			m_voxelization_pass->Render(scene, world_to_voxel,
										camera.GetSettings().GetBRDF(),
										g_voxel_grid_resolution);
		}

		camera.BindSSViewport(m_device_context);
		m_output_manager->BindBeginGBuffer(m_device_context);

		//---------------------------------------------------------------------
		// GBuffer: opaque fragments
		//---------------------------------------------------------------------
		m_forward_pass->RenderGBuffer(scene, world_to_projection);

		m_output_manager->BindEndGBuffer(m_device_context);
		m_output_manager->BindBeginDeferred(m_device_context);

		//---------------------------------------------------------------------
		// Deferred: opaque fragments
		//---------------------------------------------------------------------
		if (m_display_configuration->UsesMSAA()) {
			m_deferred_pass->Render(camera.GetSettings().GetBRDF(), vct);
		}
		else {
			m_deferred_pass->Dispatch(camera.GetSSViewport(), 
									  camera.GetSettings().GetBRDF(), vct);
		}

		m_output_manager->BindEndDeferred(m_device_context);
		m_output_manager->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Forward: emissive fragments.
		//---------------------------------------------------------------------
		m_forward_pass->RenderEmissive(scene, world_to_projection);

		//---------------------------------------------------------------------
		// Perform a sky pass.
		//---------------------------------------------------------------------
		m_sky_pass->Render(camera.GetSettings().GetSky());

		//---------------------------------------------------------------------
		// Forward: transparent fragments
		//---------------------------------------------------------------------
		m_forward_pass->RenderTransparent(scene, world_to_projection, 
										  camera.GetSettings().GetBRDF(), vct);
	}

	void XM_CALLCONV Renderer::Impl::RenderSolid(const Scene &scene, 
												 const Camera &camera, 
												 FXMMATRIX world_to_projection) {

		//---------------------------------------------------------------------
		// LBuffer
		//---------------------------------------------------------------------
		m_lbuffer_pass->Render(scene, world_to_projection,
							   camera.GetSettings().GetFog());

		camera.BindSSViewport(m_device_context);
		m_output_manager->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Forward
		//---------------------------------------------------------------------
		m_forward_pass->RenderSolid(scene, world_to_projection);
	}

	void XM_CALLCONV Renderer::Impl::RenderFalseColor(const Scene &scene, 
													  const Camera &camera, 
													  FXMMATRIX world_to_projection, 
													  FalseColor false_color) {
		
		camera.BindSSViewport(m_device_context);
		m_output_manager->BindBeginForward(m_device_context);

		//---------------------------------------------------------------------
		// Forward
		//---------------------------------------------------------------------
		m_forward_pass->RenderFalseColor(scene, world_to_projection, false_color);
	}

	void XM_CALLCONV Renderer::Impl::RenderVoxelGrid(const Scene &scene, 
													 const Camera &camera, 
													 FXMMATRIX world_to_projection) {

		//---------------------------------------------------------------------
		// LBuffer
		//---------------------------------------------------------------------
		m_lbuffer_pass->Render(scene, world_to_projection,
							   camera.GetSettings().GetFog());

		//---------------------------------------------------------------------
		// Voxelization
		//---------------------------------------------------------------------
		//TODO
		const auto r = g_voxel_grid_resolution * 0.5f * g_voxel_size;
		const auto world_to_voxel = XMMatrixOrthographicOffCenterLH(-r, r, 
																	-r, r, 
																	-r, r);
		m_voxelization_pass->Render(scene, world_to_voxel, 
									camera.GetSettings().GetBRDF(), 
									g_voxel_grid_resolution);

	
		camera.BindSSViewport(m_device_context);
		m_output_manager->BindBeginForward(m_device_context);
		
		//---------------------------------------------------------------------
		// Voxel Grid
		//---------------------------------------------------------------------
		m_voxel_grid_pass->Render(g_voxel_grid_resolution);
	}

	void Renderer::Impl::RenderPostProcessing(const Camera &camera) {
		camera.BindViewport(m_device_context);
		m_output_manager->BindBeginPostProcessing(m_device_context);

		//---------------------------------------------------------------------
		// Depth-of-field
		//---------------------------------------------------------------------
		if (camera.GetLens().HasFiniteAperture()) {
			m_output_manager->BindPingPong(m_device_context);

			// Perform a depth-of-field pass.
			m_dof_pass->Dispatch(camera.GetViewport());
		}
	}

	void Renderer::Impl::RenderAA(const Camera &camera) {
		const auto desc     = m_display_configuration->GetAADescriptor();
		const auto viewport = camera.GetSSViewport();

		switch (desc) {

		case AADescriptor::FXAA: {
			m_output_manager->BindBeginResolve(m_device_context);

			//-----------------------------------------------------------------
			// AA pre-processing
			//-----------------------------------------------------------------
			m_aa_pass->DispatchPreprocess(viewport, AADescriptor::FXAA);

			m_output_manager->BindEndResolve(m_device_context);
			m_output_manager->BindPingPong(m_device_context);

			//-----------------------------------------------------------------
			// FXAA
			//-----------------------------------------------------------------
			m_aa_pass->Dispatch(viewport, AADescriptor::FXAA);

			break;
		}

		case AADescriptor::MSAA_2x:
		case AADescriptor::MSAA_4x:
		case AADescriptor::MSAA_8x:
		case AADescriptor::SSAA_2x:
		case AADescriptor::SSAA_3x:
		case AADescriptor::SSAA_4x: {
			m_output_manager->BindBeginResolve(m_device_context);

			//-----------------------------------------------------------------
			// MSAA/SSAA
			//-----------------------------------------------------------------
			m_aa_pass->Dispatch(viewport, desc);

			m_output_manager->BindEndResolve(m_device_context);
			break;
		}

		}
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Renderer
	//-------------------------------------------------------------------------
	#pragma region

	Renderer::Renderer(ID3D11Device *device,
					   ID3D11DeviceContext *device_context,
					   DisplayConfiguration *display_configuration,
					   SwapChain *swap_chain,
					   ResourceManager *resource_manager)
		: m_impl(MakeUnique< Impl >(device,
									device_context,
									display_configuration,
									swap_chain,
									resource_manager)) {}

	Renderer::Renderer(Renderer &&renderer) noexcept = default;

	Renderer::~Renderer() = default;

	void Renderer::BindPersistentState() {
		m_impl->BindPersistentState();
	}

	void Renderer::Render(const Scene &scene) {
		m_impl->Render(scene);
	}

	#pragma endregion
}