#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"
#include "camera\perspective_camera.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of omni lights.
	 */
	class OmniLight final : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an omni light.

		 @param[in]		intensity
						The RGB intensity.
		 */
		explicit OmniLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));
		
		/**
		 Constructs an omni light from the given omni light.

		 @param[in]		light
						A reference to the omni light to copy.
		 */
		OmniLight(const OmniLight &light);

		/**
		 Constructs an omni light by moving the given omni light.

		 @param[in]		light
						A reference to the omni light to move.
		 */
		OmniLight(OmniLight &&light);

		/**
		 Destructs this omni light.
		 */
		virtual ~OmniLight();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given omni light to this omni light.

		 @param[in]		light
						A reference to the omni light to copy.
		 @return		A reference to the copy of the given omni light
						(i.e. this omni light).
		 */
		OmniLight &operator=(const OmniLight &light);

		/**
		 Moves the given omni light to this omni light.

		 @param[in]		light
						A reference to the omni light to move.
		 @return		A reference to the moved omni light
						(i.e. this omni light).
		 */
		OmniLight &operator=(OmniLight &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this omni light.

		 @return		A pointer to the clone of this omni light.
		 */
		UniquePtr< OmniLight > Clone() const {
			return static_pointer_cast< OmniLight >(CloneImplementation());
		}
		
		/**
		 Returns the distance at which intensity falloff starts of this omni light.

		 @return		The distance at which intensity falloff starts of this omni light.
		 */
		float GetStartDistanceFalloff() const noexcept {
			return m_distance_falloff_start;
		}

		/**
		 Sets the distance at which intensity falloff starts of this omni light
		 to the given value.

		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 */
		void SetStartDistanceFalloff(float distance_falloff_start) noexcept {
			m_distance_falloff_start = distance_falloff_start;
		}

		/**
		 Returns the distance at which intensity falloff ends of this omni light.

		 @return		The distance at which intensity falloff ends of this omni light.
		 */
		float GetEndDistanceFalloff() const noexcept {
			return m_distance_falloff_end;
		}

		/**
		 Sets the distance at which intensity falloff ends of this omni light
		 to the given value.

		 @pre			@a distance_falloff_end > 0.
		 @param[in]		distance_falloff_end
						The distance at which intensity falloff ends.
		 */
		void SetEndDistanceFalloff(float distance_falloff_end) noexcept {
			Assert(distance_falloff_end);
			m_distance_falloff_end = distance_falloff_end;
			
			// Update the light camera.
			m_light_camera.SetFarZ(GetEndDistanceFalloff());
			
			// Update the bounding volumes.
			UpdateBoundingVolumes();
		}

		/**
		 Sets the distance at which intensity falloff starts and ends of this omni light
		 to the given values.

		 @pre			@a distance_falloff_end > 0.
		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 @param[in]		distance_falloff_end
						The distance at which intensity falloff ends.
		 */
		void SetDistanceFalloff(float distance_falloff_start, float distance_falloff_end) noexcept {
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
		}

		/**
		 Returns the distance range where intensity falloff occurs of this omni light.

		 @return		The distance range where intensity falloff occurs of this omni light.
						@a GetEndDistanceFalloff() - @a GetStartDistanceFalloff()
		 */
		float GetRangeDistanceFalloff() const noexcept {
			return m_distance_falloff_end - m_distance_falloff_start;
		}

		/**
		 Sets the distance at which intensity falloff starts and the distance range 
		 where intensity falloff occurs of this omni light to the given values.

		 @pre			@a distance_falloff_start + @a distance_falloff_range > 0.
		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 @param[in]		distance_falloff_range
						The distance range where intensity falloff occurs.
		 */
		void SetRangeDistanceFalloff(float distance_falloff_start, float distance_falloff_range) noexcept {
			SetDistanceFalloff(distance_falloff_start, distance_falloff_start + distance_falloff_range);
		}

		/**
		 Checks whether shadows should be used for this omni light.

		 @return		@c true if shadows should be used for this
						omni light. @c false otherwise.
		 */
		bool UseShadows() const noexcept {
			return m_shadows;
		}

		/**
		 Enables shadows for this omni light.
		 */
		void EnableShadows() noexcept {
			SetShadows(true);
		}

		/**
		 Dissables shadows for this omni light.
		 */
		void DissableShadows() noexcept {
			SetShadows(false);
		}

		/**
		 Toggles shadows for this omni light.
		 */
		void ToggleShadows() noexcept {
			SetShadows(!m_shadows);
		}

		/**
		 Sets shadows for this omni light to the given value.

		 @param[in]		@c true if shadows should be used for
						this omni light. @c false otherwise.
		 */
		void SetShadows(bool shadows) noexcept {
			m_shadows = shadows;
		}

		/**
		 Returns the (forward) light camera of this omni light.

		 @return		A reference to the (forward) light camera
						of this omni light.
		 */
		const PerspectiveCamera &GetLightCamera() const noexcept {
			return m_light_camera;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this omni light.

		 @return		A pointer to the clone of this omni light.
		 */
		virtual UniquePtr< Light > CloneImplementation() const override;

		/**
		 Updates the light camera of this omni light.
		 */
		void UpdateLightCamera() noexcept;

		/**
		 Updates the bounding volumes of this omni light.
		 */
		void UpdateBoundingVolumes() noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The start of the distance falloff of this omni light.
		 */
		float m_distance_falloff_start;

		/**
		 The end of the distance falloff of this omni light.
		 */
		float m_distance_falloff_end;

		/**
		 A flag indicating whether shadows should be calculated
		 or not for this omni light.
		 */
		bool m_shadows;

		/**
		 The (forward) light camera of this omni light.
		 */
		PerspectiveCamera m_light_camera;
	};
}