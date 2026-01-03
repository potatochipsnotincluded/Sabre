#pragma once
#include <filesystem>

namespace Sabre {

	class Texture
	{
	public:
		Texture(const std::filesystem::path& filepath);
		~Texture();

		void SetActiveSlot(char slot);

		void Bind();
		void Unbind();

		unsigned char* GetRawData();
	private:
		unsigned char* m_Data = nullptr;
		int32_t m_Width;
		int32_t m_Height;
		int32_t m_Channels;
	private:
		void GLLoadTexture();

		void GLBind();
		void GLUnbind();
		void GLActiveSlot(char slot);
	private:
		uint32_t m_GLID; // Unused if another API
	};

}