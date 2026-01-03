#include "Texture.h"
#include "Sabre/Platform.h"
#include "Sabre/Debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifdef API_GL41
#include <glad/glad.h>
#endif

namespace Sabre {

	Texture::Texture(const std::filesystem::path& filepath)
	{
		stbi_set_flip_vertically_on_load(true);

		m_Data = stbi_load(filepath.string().c_str(), &m_Width, &m_Height, &m_Channels, 0);

		SABRE_ASSERT(m_Data, "Couldn't load texture! Maybe actually learn how files work?");

#ifdef API_GL41
		GLLoadTexture();
#endif
	}

	Texture::~Texture()
	{
		stbi_image_free(m_Data);
	}

	void Texture::SetActiveSlot(char slot)
	{
#ifdef API_GL41
		GLActiveSlot(slot);
#endif
	}

	void Texture::Bind()
	{
#ifdef API_GL41
		GLBind();
#endif
	}

	void Texture::Unbind()
	{
#ifdef API_GL41
		GLUnbind();
#endif
	}

	unsigned char* Texture::GetRawData()
	{
		return m_Data;
	}

#ifdef API_GL41
	void Texture::GLLoadTexture()
	{
		GLenum format = GL_RED;
		if (m_Channels == 3)
			format = GL_RGB;
		else if (m_Channels == 4)
			format = GL_RGBA;

		glGenTextures(1, &m_GLID);
		glBindTexture(GL_TEXTURE_2D, m_GLID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D,
			0,
			format,
			m_Width,
			m_Height,
			0,
			format,
			GL_UNSIGNED_BYTE,
			m_Data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::GLBind()
	{
		glBindTexture(GL_TEXTURE_2D, m_GLID);
	}

	void Texture::GLUnbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::GLActiveSlot(char slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
	}
#else
	void Texture::GLLoadTexture()
	{
	}

	void Texture::GLBind()
	{
	}

	void Texture::GLUnbind()
	{
	}

	void Texture::GLActiveSlot(char slot)
	{
	}
#endif
}