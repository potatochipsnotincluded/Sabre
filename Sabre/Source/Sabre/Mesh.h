#pragma once
#include "Sabre/Platform.h"

#include <vector>

namespace Sabre {

	struct GLMeshData
	{
		uint32_t VBO;
		uint32_t VAO;
		uint32_t EBO;
		uint32_t TBO;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<uint32_t> indices);
		GLMeshData GetGLMeshData();

		void Bind();
		void Unbind();

		uint32_t GetIndexCount();
	private:
		uint32_t m_IndexCount;
	private:
		GLMeshData m_GLMeshData; // Also in future provide other mesh data, eg, VKMeshData, MTLMeshData, DXMeshData
	};

}