#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\obj\obj_tokens.hpp"
#include "loaders\material_loader.hpp"
#include "mesh\vertex.hpp"
#include "utils\string\string_utils.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	OBJReader< VertexT >::OBJReader(
		ModelOutput< VertexT > &model_output,
		const MeshDescriptor< VertexT > &mesh_desc)
		: LineReader(),
		m_vertex_coordinates(), 
		m_vertex_texture_coordinates(),
		m_vertex_normal_coordinates(), 
		m_mapping(),
		m_model_output(model_output), 
		m_mesh_desc(mesh_desc) {}

	template < typename VertexT >
	OBJReader< VertexT >::OBJReader(OBJReader &&reader) = default;

	template < typename VertexT >
	OBJReader< VertexT >::~OBJReader() = default;

	template < typename VertexT >
	void OBJReader< VertexT >::Preprocess() {
		ThrowIfFailed(m_model_output.m_vertex_buffer.empty(),
			"%ls: vertex buffer must be empty.", GetFilename().c_str());
		ThrowIfFailed(m_model_output.m_index_buffer.empty(),
			"%ls: index buffer must be empty.", GetFilename().c_str());

		// Begin current group.
		m_model_output.StartModelPart(MAGE_MDL_PART_DEFAULT_CHILD);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::Postprocess() {
		// End current group.
		m_model_output.EndModelPart();
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadLine(char *line) {
		m_context = nullptr;
		const char *token 
			= strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || MAGE_OBJ_COMMENT_CHAR == token[0]) {
			return;
		}

		if (str_equals(token, MAGE_OBJ_TOKEN_VERTEX)) {
			ReadOBJVertex();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_TEXTURE)) {
			ReadOBJVertexTexture();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_NORMAL)) {
			ReadOBJVertexNormal();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_FACE)) {
			ReadOBJFace();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_MATERIAL_LIBRARY)) {
			ReadOBJMaterialLibrary();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_MATERIAL_USE)) {
			ReadOBJMaterialUse();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_GROUP)) {
			ReadOBJGroup();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_OBJECT)) {
			ReadOBJObject();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_SMOOTHING_GROUP)) {
			ReadOBJSmoothingGroup();
		}
		else {
			Warning(
				"%ls: line %u: unsupported keyword token: %s.", 
				GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJMaterialLibrary() {
		const wstring mtl_path  = mage::GetPathName(GetFilename());
		const wstring mtl_name  = str_convert(ReadString());
		const wstring mtl_fname = mage::GetFilename(mtl_path, mtl_name);

		ImportMaterialFromFile(mtl_fname, m_model_output.m_material_buffer);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJMaterialUse() {
		m_model_output.SetMaterial(ReadString());
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJGroup() {
		const string child = ReadString();
		
		if (MAGE_MDL_PART_DEFAULT_CHILD == child) {
			
			ThrowIfFailed(m_model_output.m_index_buffer.empty(),
				"%ls: line %u: default child name can only be explicitly "
				"defined before all face definitions.",
				GetFilename().c_str(), GetCurrentLineNumber());

			return;
		}

		ThrowIfFailed(!m_model_output.HasModelPart(child),
			"%ls: line %u: child name redefinition: %s.",
			GetFilename().c_str(), GetCurrentLineNumber(), child.c_str());

		const string parent = HasString() ? ReadString() : MAGE_MDL_PART_DEFAULT_PARENT;
		
		m_model_output.EndModelPart();
		m_model_output.StartModelPart(std::move(child), std::move(parent));
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJObject() {
		ReadString();
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJSmoothingGroup() {
		// Silently ignore smoothing group declarations
		ReadString();
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertex() {
		const Point3 vertex = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexCoordinates()) :
			ReadOBJVertexCoordinates();

		m_vertex_coordinates.push_back(std::move(vertex));
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertexTexture() {
		const UV texture = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexTextureCoordinates()) :
			ReadOBJVertexTextureCoordinates();

		m_vertex_texture_coordinates.push_back(std::move(texture));
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertexNormal() {
		const Normal3 normal = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexNormalCoordinates()) :
			ReadOBJVertexNormalCoordinates();
		const XMVECTOR v = XMLoadFloat3(&normal);
		const XMVECTOR normal_v = XMVector3Normalize(v);
		XMLoadFloat3(&normal);

		m_vertex_normal_coordinates.push_back(std::move(normal));
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJFace() {
		
		vector< U32 > indices;
		while (indices.size() < 3 || HasString()) {
			const XMUINT3 vertex_indices = ReadOBJVertexIndices();

			if (const auto it = m_mapping.find(vertex_indices); 
				it != m_mapping.cend()) {

				indices.push_back(it->second);
			}
			else {
				const U32 index 
					= static_cast< U32 >(m_model_output.m_vertex_buffer.size());
				indices.push_back(index);
				m_model_output.m_vertex_buffer.push_back(ConstructVertex(vertex_indices));
				m_mapping[vertex_indices] = index;
			}
		}

		if (m_mesh_desc.ClockwiseOrder()) {
			for (size_t i = 1; i < indices.size() - 1; ++i) {
				m_model_output.m_index_buffer.push_back(indices[0]);
				m_model_output.m_index_buffer.push_back(indices[i + 1]);
				m_model_output.m_index_buffer.push_back(indices[i]);
			}
		}
		else {
			for (size_t i = 1; i < indices.size() - 1; ++i) {
				m_model_output.m_index_buffer.push_back(indices[0]);
				m_model_output.m_index_buffer.push_back(indices[i]);
				m_model_output.m_index_buffer.push_back(indices[i + 1]);
			}
		}
	}

	template < typename VertexT >
	inline const Point3 OBJReader< VertexT >::ReadOBJVertexCoordinates() {
		return static_cast< Point3 >(ReadFloat3());
	}

	template < typename VertexT >
	inline const Normal3 OBJReader< VertexT >::ReadOBJVertexNormalCoordinates() {
		return static_cast< Normal3 >(ReadFloat3());
	}

	template < typename VertexT >
	inline const UV OBJReader< VertexT >::ReadOBJVertexTextureCoordinates() {
		const UV result = static_cast< UV >(ReadFloat2());
		
		if (HasF32()) {
			// Silently ignore 3D vertex texture coordinates.
			ReadF32();
		}

		return result;
	}

	template < typename VertexT >
	const XMUINT3 OBJReader< VertexT >::ReadOBJVertexIndices() {
		const char *token = ReadChars();

		U32 vertex_index = 0;
		U32 texture_index = 0;
		U32 normal_index = 0;

		if (str_contains(token, "//")) {
			// v1//vn1
			const char *index_end = strchr(token, '/');
			if (StringToU32(token, index_end, vertex_index) == TokenResult::Invalid) {
				throw FormattedException(
					"%ls: line %u: invalid vertex index value found in %s.", 
					GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
			if (StringToU32(index_end + 2, normal_index) == TokenResult::Invalid) {
				throw FormattedException(
					"%ls: line %u: invalid normal index value found in %s.", 
					GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
		}
		else if (str_contains(token, '/')) {
			// v1/vt1 or v1/vt1/vn1
			const char *index_end = strchr(token, '/');
			if (StringToU32(token, index_end, vertex_index) == TokenResult::Invalid) {
				throw FormattedException(
					"%ls: line %u: invalid vertex index value found in %s.", 
					GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
			
			if (str_contains(index_end + 1, '/')) {
				const char *texture_end = strchr(index_end + 1, '/');
				if (StringToU32(index_end + 1, texture_end, texture_index) == TokenResult::Invalid) {
					throw FormattedException(
						"%ls: line %u: invalid texture index value found in %s.", 
						GetFilename().c_str(), GetCurrentLineNumber(), token);
				}
				if (StringToU32(texture_end + 1, normal_index) == TokenResult::Invalid) {
					throw FormattedException(
						"%ls: line %u: invalid normal index value found in %s.", 
						GetFilename().c_str(), GetCurrentLineNumber(), token);
				}
			}
			else if (StringToU32(index_end + 1, texture_index) == TokenResult::Invalid) {
				throw FormattedException(
					"%ls: line %u: invalid texture index value found in %s.", 
					GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
		}
		else if (StringToU32(token, vertex_index) == TokenResult::Invalid) {
			throw FormattedException(
				"%ls: line %u: invalid vertex index value found in %s.", 
				GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		return XMUINT3(vertex_index, texture_index, normal_index);
	}

	template < typename VertexT >
	const VertexT OBJReader< VertexT >::ConstructVertex(
		const XMUINT3 &vertex_indices) {
		
		VertexT vertex;

		if constexpr(VertexT::HasPosition()) {
			if (vertex_indices.x) {
				vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
			}
		}

		if constexpr(VertexT::HasTexture()) {
			if (vertex_indices.y) {
				vertex.tex = m_vertex_texture_coordinates[vertex_indices.y - 1];
			}
		}

		if constexpr(VertexT::HasNormal()) {
			if (vertex_indices.z) {
				vertex.n = m_vertex_normal_coordinates[vertex_indices.z - 1];
			}
		}

		return vertex;
	}
}