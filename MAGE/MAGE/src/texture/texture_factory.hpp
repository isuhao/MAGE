#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declaration.
	class Texture;

	/**
	 Creates a MAGE texture.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateMAGETexture();

	/**
	 Creates a reference texture.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateReferenceTexture();

	/**
	 Creates a black texture.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateBlackTexture();

	/**
	 Creates a white texture.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateWhiteTexture();

	/**
	 Creates a red texture.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateRedTexture();

	/**
	 Creates a green texture.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateGreenTexture();

	/**
	 Creates a blue texture.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateBlueTexture();
}