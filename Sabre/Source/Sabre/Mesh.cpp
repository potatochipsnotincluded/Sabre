#include "Mesh.h"

#ifdef API_GL41
#include "GL41/RendererGL41.h"
#endif

namespace Sabre {

	Mesh::Mesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<uint32_t> indices)
	{
		m_IndexCount = indices.size();
#ifdef API_GL41
		m_GLMeshData = GL41::CreateMesh(vertices, textureCoords, indices);
#endif
	}

	GLMeshData Mesh::GetGLMeshData()
	{
		return m_GLMeshData;
	}

	void Mesh::Bind()
	{
#ifdef API_GL41
		GL41::BindMesh(m_GLMeshData);
#endif
	}

	void Mesh::Unbind()
	{
#ifdef API_GL41
		GL41::UnbindMesh();
#endif
	}

	uint32_t Mesh::GetIndexCount()
	{
		return m_IndexCount;
	}

}
