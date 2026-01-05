#pragma once
#include "Sabre/Platform.h"

#include <vector>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Sabre {

	struct GLMeshData
	{
		uint32_t VBO;
		uint32_t VAO;
		uint32_t EBO;
		uint32_t TBO;
		uint32_t NBO; 
	};

	class Mesh
	{
	public:
		Mesh(std::vector<float> vertices, std::vector<float> textureCoords,std::vector<float> normals, std::vector<uint32_t> indices);
		GLMeshData GetGLMeshData();

		void Bind();
		void Unbind();

		uint32_t GetIndexCount();
	private:
		uint32_t m_IndexCount;
	private:
		GLMeshData m_GLMeshData; // Also in future provide other mesh data, eg, VKMeshData, MTLMeshData, DXMeshData
	};

	Mesh LoadMesh(const std::filesystem::path& filepath);

}