//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ReadBinaryFile(const std::filesystem::path& path,
						UniquePtr< U8[] >& data,
						size_t& size) {

		const auto file_handle 
			= CreateUniqueHandle(CreateFile2(path.c_str(),
											 GENERIC_READ, 
											 FILE_SHARE_READ, 
											 OPEN_EXISTING, 
											 nullptr));
		
		FILE_STANDARD_INFO file_info;
		{
			const BOOL result = GetFileInformationByHandleEx(file_handle.get(), 
															 FileStandardInfo, 
															 &file_info, 
															 sizeof(file_info));
			ThrowIfFailed(result, 
						  "%ls: could not retrieve file information.", 
						  path.c_str());
			ThrowIfFailed((0 == file_info.EndOfFile.HighPart), 
						  "%ls: file too big for 32-bit allocation.", 
						  path.c_str());
		}
		
		// Allocate buffer.
		const auto nb_bytes = file_info.EndOfFile.LowPart;
		size = static_cast< size_t >(nb_bytes);
		data = MakeUnique< U8[] >(nb_bytes);
		ThrowIfFailed((nullptr != data), 
					  "%ls: file too big for allocation.", path.c_str());

		// Populate buffer.
		{
			DWORD nb_bytes_read = 0;
			const BOOL result = ReadFile(file_handle.get(), data.get(), 
										 nb_bytes, &nb_bytes_read, nullptr);
			ThrowIfFailed(result, 
						  "%ls: could not load file data.", path.c_str());
			ThrowIfFailed((nb_bytes <= nb_bytes_read), 
						  "%ls: could not load all file data.", path.c_str());
		}
	}

	//-------------------------------------------------------------------------
	// BinaryReader
	//-------------------------------------------------------------------------
	#pragma region

	BinaryReader::BinaryReader()
		: m_path(),
		m_big_endian(true),
		m_pos(nullptr), 
		m_end(nullptr), 
		m_data() {}

	BinaryReader::BinaryReader(BinaryReader&& reader) noexcept = default;

	BinaryReader::~BinaryReader() = default;

	BinaryReader& BinaryReader
		::operator=(BinaryReader&& reader) noexcept = default;

	void BinaryReader::ReadFromFile(std::filesystem::path path, 
									bool big_endian) {

		m_path       = std::move(path);
		m_big_endian = big_endian;

		size_t nb_bytes = 0u;
		ReadBinaryFile(m_path, m_data, nb_bytes);
		
		m_pos = m_data.get();
		m_end = m_data.get() + nb_bytes;
		
		ReadData();
	}
	
	void BinaryReader::ReadFromMemory(gsl::span< const U8 > input, 
									  bool big_endian) {

		m_path       = L"input string";
		m_big_endian = big_endian;
		
		m_pos = input.data();
		m_end = input.data() + input.size();

		ThrowIfFailed((m_pos <= m_end), 
					  "%ls: overflow.", GetPath().c_str());

		ReadData();
	}

	NotNull< const_zstring > BinaryReader::ReadChars(size_t size) {
		const auto old_pos = m_pos;
		const auto new_pos = m_pos + size;
		ThrowIfFailed((m_pos <= new_pos), 
					  "%ls: overflow: no chars value found.", 
					  GetPath().c_str());
		ThrowIfFailed((new_pos <= m_end), 
					  "%ls: end of file: no chars value found.", 
					  GetPath().c_str());

		m_pos = new_pos;
		return NotNull< const_zstring >(reinterpret_cast< const char* >(old_pos));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// BigEndianBinaryReader
	//-------------------------------------------------------------------------
	#pragma region

	BigEndianBinaryReader::BigEndianBinaryReader()
		: m_path(), 
		m_pos(nullptr), 
		m_end(nullptr), 
		m_data() {}

	BigEndianBinaryReader::BigEndianBinaryReader(
		BigEndianBinaryReader&& reader) noexcept = default;

	BigEndianBinaryReader::~BigEndianBinaryReader() = default;

	BigEndianBinaryReader& BigEndianBinaryReader
		::operator=(BigEndianBinaryReader&& reader) noexcept = default;

	void BigEndianBinaryReader::ReadFromFile(std::filesystem::path path) {
		m_path = std::move(path);

		size_t nb_bytes = 0u;
		ReadBinaryFile(m_path, m_data, nb_bytes);

		m_pos  = m_data.get();
		m_end  = m_data.get() + nb_bytes;
		
		ReadData();
	}
	
	void BigEndianBinaryReader::ReadFromMemory(gsl::span< const U8 > input) {
		m_path = L"input string";

		m_pos  = input.data();
		m_end  = input.data() + input.size();

		ThrowIfFailed((m_pos <= m_end), 
					  "%ls: overflow.", GetPath().c_str());

		ReadData();
	}

	#pragma endregion
}