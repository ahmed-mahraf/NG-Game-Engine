/** @file OpenGLShader.cpp
*	identifies vertex and fragment shaders and load from file and creation of shaders
*/
#include "engine_pch.h"
#include "platforms/openGL/OpenGLShader.h"

#include "rendering/renderer.h"
#include <fstream>

#include <glad/glad.h> 
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		GE_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		NG_PROFILE_FUNCTION();

		std::string source = readFile(filepath);
		auto shaderSources = preProcess(source);
		compile(shaderSources);

		//<! Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_name(name)
	{
		NG_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_VERTEX_SHADER] = fragmentSrc;
		compile(sources);
	}

	//<!deconstructor for shader
	OpenGLShader::~OpenGLShader()
	{
		NG_PROFILE_FUNCTION();

		glDeleteProgram(m_rendererID);
	}

	std::string OpenGLShader::readFile(const std::string& filepath)
	{
		NG_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				GE_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			GE_CORE_ERROR("Can't open file", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& source)
	{
		NG_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		//<! looks for keyword type to look for fragment and vertex
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		//<! start of shader type declaration
		while (pos != std::string::npos)
		{
			//<!find first instance of new line and finds position
			size_t eol = source.find_first_of("\r\n", pos);
			GE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			//<!word type (4chars) + 1 reads the fragment or vertex
			size_t begin = pos + typeTokenLength + 1;
			//<!go to the end of the line
			std::string type = source.substr(begin, eol - begin);
			GE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type")

			//<!find next line
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			//<!find next type identifier
			pos = source.find(typeToken, nextLinePos);
			//<! converts string to shader type
			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	//<! compile shader using whatever type is found using unordered_map
	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		NG_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		std::array<GLenum, 2> glShaderIDs;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			//<!Compile the shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				//<!The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				//<!delete the shader 
				glDeleteShader(shader);

				GE_CORE_ERROR("{0}", infoLog.data());
				GE_CORE_ASSERT(false, "Shader compilation failure");
				return;
			}

			//<!attach the shader
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}
		

		//<!Link our program
		glLinkProgram(program);

		//<!Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			//<!The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			//<! We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
			{
				glDetachShader(program, id);
				glDeleteShader(id);
			}

			GE_CORE_ERROR("{0}", infoLog.data());
			//GE_CORE_ASSERT(false, "shader link failure");
			return;
		}

		//<!Always detach shaders after a successful link.
		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
		}

		//<! Now time to link them together into a program.
		m_rendererID = program;
	}

	//<!bind shader
	void OpenGLShader::bind() const
	{
		NG_PROFILE_FUNCTION();

		glUseProgram(m_rendererID);
	}
	//<!unbind shader
	void OpenGLShader::unbind() const
	{
		NG_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	//<!set Int location and values
	void OpenGLShader::setInt(const std::string& name, int value)
	{
		NG_PROFILE_FUNCTION();

		uploadUniformInt(name, value);
	}

	void OpenGLShader::setFloat(const std::string & name, float value)
	{
		NG_PROFILE_FUNCTION();

		uploadUniformFloat(name, value);
	}

	//<!set Float3 location and values
	void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value)
	{
		NG_PROFILE_FUNCTION();

		uploadUniformFloat3(name, value);
	}

	//<!set Float4 location and values
	void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value)
	{
		NG_PROFILE_FUNCTION();

		uploadUniformFloat4(name, value);
	}

	//<!set Matrix4 location and values
	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value)
	{
		NG_PROFILE_FUNCTION();

		uploadUniformMat4(name, value);
	}

	//<!get and upload uniformfInt location and values
	void OpenGLShader::uploadUniformInt(const std::string& name, int values)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1i(location, values);
	}

	//<!get and upload uniformfloat location and values
	void OpenGLShader::uploadUniformFloat(const std::string& name, float values)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1f(location, values);
	}
	//<!get and upload uniformfloat 2 location and values
	void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}
	//<!get and upload uniformfloat 3 location and values
	void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);

	}
	//<!get and upload uniformfloat 4 location and values
	void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}


	//<!get and upload uniformmat3 location and matrix
	void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	//<!get and upload uniformmat4 location and matrix
	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}