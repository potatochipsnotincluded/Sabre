#include "ShaderProgramme.h"

#ifdef API_GL41
#include <glad/glad.h>
#endif

namespace Sabre {

	ShaderProgramme::ShaderProgramme(const std::filesystem::path& fragPath, const std::filesystem::path& vertPath)
	{
#ifdef API_GL41
		LoadShaderProgrammeGL(fragPath, vertPath);
#endif
	}

	void ShaderProgramme::Start()
	{
#ifdef API_GL41
		StartGL();
#endif
	}

	void ShaderProgramme::End()
	{
#ifdef API_GL41
		StartGL();
#endif
	}

	uint32_t ShaderProgramme::GetGLID()
	{
		return m_GLID;
	}

#ifdef API_GL41
	void ShaderProgramme::LoadShaderProgrammeGL(const std::filesystem::path& fragPath, const std::filesystem::path& vertPath)
	{
		std::string vertSource = LoadFile(vertPath);

		uint32_t vertShader = glCreateShader(GL_VERTEX_SHADER);
		const char* src = vertSource.c_str();
		glShaderSource(vertShader, 1, &src, nullptr);
		glCompileShader(vertShader);

		GLint success;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertShader, 512, nullptr, infoLog);
			SABRE_LOG(Severity::Error, "Shader error! {} Sorry, but shaders actually are used at some point, they're not a decorative artpiece.", infoLog);
		}

		std::string fragSource = LoadFile(fragPath);

		uint32_t fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* srcX = fragSource.c_str();
		glShaderSource(fragShader, 1, &srcX, nullptr);
		glCompileShader(fragShader);

		GLint successX;
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &successX);
		if (!successX)
		{
			char infoLog[512];
			glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
			SABRE_LOG(Severity::Error, "Shader error! {} Sorry, but shaders actually are used at some point, they're not a decorative artpiece.", infoLog);
		}

		m_GLID = glCreateProgram();
		glAttachShader(m_GLID, vertShader);
		glAttachShader(m_GLID, fragShader);
		glLinkProgram(m_GLID);

		int32_t successS;
		glGetProgramiv(m_GLID, GL_LINK_STATUS, &successS);
		if (!successS)
		{
			char infoLog[512];
			glGetProgramInfoLog(m_GLID, 512, nullptr, infoLog);
			SABRE_LOG(Severity::Error, "Oopsy, it looks like GL did an oopsy! Here 'tis! {}", infoLog);
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}

	void ShaderProgramme::StartGL()
	{
		glUseProgram(m_GLID);
	}

	void ShaderProgramme::EndGL()
	{
		glUseProgram(0);
	}
#else
	void ShaderProgramme::LoadShaderProgrammeGL(const std::filesystem::path& shaderPath)
	{
	}

	void ShaderProgramme::StartGL()
	{
	}

	void ShaderProgramme::EndGL()
	{
	}
#endif
}
