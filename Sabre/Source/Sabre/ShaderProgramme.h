#pragma once
#include "Sabre/Data.h"
#include "Sabre/Platform.h"
#include "Sabre/Debug.h"

namespace Sabre {

	class ShaderProgramme
	{
	public:
		ShaderProgramme(const std::filesystem::path& fragPath, const std::filesystem::path& vertPath);

		void Start();
		void End();

		uint32_t GetGLID();

	private:
		void LoadShaderProgrammeGL(const std::filesystem::path& fragPath, const std::filesystem::path& vertPath);
		void StartGL();
		void EndGL();
	private:
		uint32_t m_GLID = 0;
	};

}