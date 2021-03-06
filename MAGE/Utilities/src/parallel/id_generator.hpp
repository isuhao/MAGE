#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "parallel\atomic.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of id generators.
	 */
	class IdGenerator final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the next guid.

		 @return		The next guid.
		 */
		static U64 GetNextGuid() noexcept {
			return s_guid_generator.GetNextId();
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an id generator.

		 @param[in]		first_id
						The first id of this id_generator
		 */
		constexpr explicit IdGenerator(U64 first_id = 0ull) noexcept
			: m_current_id(first_id) {}

		/**
		 Constructs an id generator from the given id generator.

		 @param[in]		generator
						A reference to the id generator to copy.
		 */
		constexpr IdGenerator(const IdGenerator& generator) = delete;

		/**
		 Constructs an id generator by moving the given id generator.

		 @param[in]		generator
						A reference to the id generator to move.
		 */
		constexpr IdGenerator(IdGenerator&& generator) = delete;

		/**
		 Destructs this id generator.
		 */
		~IdGenerator() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given id generator to this id generator.

		 @param[in]		generator
						The id generator to copy.
		 @return		A reference to the copy of the given id generator (i.e. 
						this id generator).
		 */
		IdGenerator& operator=(const IdGenerator& generator) = delete;

		/**
		 Copies the given id generator to this id generator.

		 @param[in]		generator
						The id generator to move.
		 @return		A reference to the moved id generator (i.e. this id 
						generator).
		 */
		IdGenerator& operator=(IdGenerator&& generator) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the next id of this id generator.

		 @return		The next id of this id generator.
		 */
		U64 GetNextId() noexcept {
			return m_current_id++;
		}

	private:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 The guid generator.
		 */
		static IdGenerator s_guid_generator;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current id of this id generator.
		 */
		AtomicU64 m_current_id;
	};
}