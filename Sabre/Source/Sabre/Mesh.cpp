#include "Mesh.h"

#ifdef API_GL41
#include "GL41/RendererGL41.h"
#endif

namespace Sabre {

	Mesh::Mesh(std::vector<float> vertices, std::vector<float> textureCoords,std::vector<float> normals, std::vector<uint32_t> indices)
	{
		m_IndexCount = indices.size();
#ifdef API_GL41
		m_GLMeshData = GL41::CreateMesh(vertices, textureCoords, normals, indices);
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

	Mesh LoadMesh(const std::filesystem::path& filepath)
	{
        std::vector<float> vertices;
        std::vector<float> textureCoords;
        std::vector<float> normals;
        std::vector<uint32_t> indices;

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filepath.string(),
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_GenSmoothNormals);

        SABRE_ASSERT(scene && scene->HasMeshes(), "Failed to load model! {}", importer.GetErrorString());

        uint32_t vertexOffset = 0;

        for (unsigned int m = 0; m < scene->mNumMeshes; ++m)
        {
            aiMesh* mesh = scene->mMeshes[m];

            vertices.reserve(vertices.size() + mesh->mNumVertices * 3);
            normals.reserve(normals.size() + mesh->mNumVertices * 3);
            textureCoords.reserve(textureCoords.size() + mesh->mNumVertices * 2);

            for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
            {
                vertices.push_back(mesh->mVertices[i].x);
                vertices.push_back(mesh->mVertices[i].y);
                vertices.push_back(mesh->mVertices[i].z);

                if (mesh->HasNormals())
                {
                    normals.push_back(mesh->mNormals[i].x);
                    normals.push_back(mesh->mNormals[i].y);
                    normals.push_back(mesh->mNormals[i].z);
                }
                else
                {
                    normals.push_back(0.0f);
                    normals.push_back(0.0f);
                    normals.push_back(0.0f);
                }

                if (mesh->HasTextureCoords(0))
                {
                    textureCoords.push_back(mesh->mTextureCoords[0][i].x);
                    textureCoords.push_back(mesh->mTextureCoords[0][i].y);
                }
                else
                {
                    textureCoords.push_back(0.0f);
                    textureCoords.push_back(0.0f);
                }
            }

            for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
            {
                aiFace face = mesh->mFaces[i];
                for (unsigned int j = 0; j < face.mNumIndices; ++j)
                {
                    indices.push_back(face.mIndices[j] + vertexOffset);
                }
            }

            vertexOffset += mesh->mNumVertices;
        }

        // Ignore normals for now 'u'!
		return Mesh(vertices, textureCoords, normals, indices);
	}

}
