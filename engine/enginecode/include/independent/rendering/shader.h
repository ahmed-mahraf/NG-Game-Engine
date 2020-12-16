#pragma once 
/** @file shader.h
* header file includes shaders
*/
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "core/base.h"

namespace Engine
{
	/**
	* @class Shader
	* Creates values for shaders
	*/

	class Shader
	{
	public:
		virtual ~Shader() = default; //<! Destructor
		
		virtual void bind() const = 0; //<! Virtual function to bind 
		virtual void unbind() const = 0; //<! Virtual function to unbind

		virtual void setInt(const std::string& name, int value) = 0;
		virtual void setFloat(const std::string& name, float value) = 0;
		virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& getName() const = 0;

		static Ref<Shader> create(const std::string& filepath); //<! Creating shader from filepath
		static Ref<Shader> create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc); //<! Creating shader from vertex and fragment source
	};

	/**
	* @class ShaderLib
	* Creates values for shader library
	*/

	class ShaderLib
	{
	public:
		void add(const std::string& name, const Ref<Shader>& shader); //<! Function to add shader name
		void add(const Ref<Shader>& shader); //<! Function to add shader

		Ref<Shader> load(const std::string& filepath); //<! Load shader via filepath
		Ref<Shader> load(const std::string& name, const std::string& filepath); //<! Load shader via name

		Ref<Shader> get(const std::string& name); //<! Load shader via name

		bool shaderExists(const std::string& name);
	private:
		std::unordered_map < std::string, Ref<Shader> > m_shaders; //<! Unordered map of shaders
	};
}