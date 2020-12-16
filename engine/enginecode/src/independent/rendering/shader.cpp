/** @file shader.cpp
*	create vertex array and libraries for shaders
*/
#include "engine_pch.h"

#include "rendering/renderer.h"
#include "rendering/shader.h"

#include "platforms/openGL/OpenGLShader.h"


namespace Engine
{
	Ref<Shader> Shader::create(const std::string& filepath)
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef< OpenGLShader>(filepath);
		}

		GE_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;

	}
	//<!create vertex array
	Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{

		switch (Renderer::getAPI())
		{
			case RendererAPI::API::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef< OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		GE_CORE_ASSERT(false, "unknown RendererAPI");
		return nullptr;

	}

	void ShaderLib::add(const std::string & name, const Ref<Shader>& shader)
	{
		GE_CORE_ASSERT(!shaderExists(name), "Shader exists!");
		m_shaders[name] = shader;
	}

	void ShaderLib::add(const Ref<Shader>& shader)
	{
		auto& name = shader->getName();
		add(name, shader);
	}

	Ref<Shader> ShaderLib::load(const std::string & filepath)
	{
		auto shader = Shader::create(filepath);
		add(shader);
		return shader;
	}

	Ref<Shader> ShaderLib::load(const std::string & name, const std::string & filepath)
	{
		auto shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLib::get(const std::string & name)
	{
		GE_CORE_ASSERT(shaderExists(name), "Shader not found!");
		return m_shaders[name];
	}

	bool ShaderLib::shaderExists(const std::string & name)
	{
		return m_shaders.find(name) != m_shaders.end();
	}
}