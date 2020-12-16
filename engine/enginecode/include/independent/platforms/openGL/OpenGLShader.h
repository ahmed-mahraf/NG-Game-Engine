/**
* @file OpenGLShader.h
* Creates values for open gl shaders
*/
#pragma once
#include "rendering/shader.h"

#include <string>
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Engine
{
	/**
	* @class Shader
	* Creates values for shaders
	*/

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath); //<! Constructor to check the file path
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc); //<! Constructor to check the glsl shaders

		virtual ~OpenGLShader(); //<! Destructor

		virtual void bind() const override; //<! Function to bind
		virtual void unbind() const override;//<! Function to unbind

		virtual void setInt(const std::string& name, int value) override;
		virtual void setFloat(const std::string& name, float value) override;
		virtual void setFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void setMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& getName() const override { return m_name; }

		void uploadUniformInt(const std::string& name, int values); //<! Function to upload uniform as Integer

		void uploadUniformFloat(const std::string& name, float values); //<! Function to upload uniform as a float
		void uploadUniformFloat2(const std::string& name, const glm::vec2& values); //<! Function to upload uniform as 2 floats 
		void uploadUniformFloat3(const std::string& name, const glm::vec3& values); //<! Function to upload uniform as 3 floats
		void uploadUniformFloat4(const std::string& name, const glm::vec4& values); //<! Function to upload uniform as 4 floats

		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix); //<! Function to upload uniform as 4 Matrixes
		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix); //<! Function to upload uniform as 3 Matrixes
	private:
		std::string readFile(const std::string& filepath); //<! String to read file
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source); //<! Unordered map for pre processing
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources); //<! Function to compile shader sources
	private:
		uint32_t m_rendererID; //<! Integer 32-bit for rendererID
		std::string m_name;
		int glShaderIDIndex = 0; //<! Integer for Shader ID Index
	}; 
}