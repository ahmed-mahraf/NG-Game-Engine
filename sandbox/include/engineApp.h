#pragma once

#include <engine.h>

// ---Entry Point---------------------
#include "core/entrypoint.h"
// -----------------------------------

#include "platforms/openGL/OpenGLShader.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine2D.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer();								//!< Constructor
	~ExampleLayer() = default;					//!< Destructor

	void onUpdate(Engine::Timestep ts) override;//!< Function for Update
	void onEvent(Engine::Event&e) override;
	virtual void onImGuiRender() override;		//!< Function for imGui Renderer

private:

	Engine::ShaderLib m_shaderLibrary;
	Engine::Ref<Engine::Shader> m_shader;		//!< Ref pointer to shader
	Engine::Ref<Engine::VertexArray> m_vA;		//!< Ref pointer to vertex array
	Engine::Ref<Engine::VertexBuffer> m_vB;		//!< Ref pointer to vertex buffer
	Engine::Ref<Engine::IndexBuffer> m_iB;		//!< Ref pointer to index buffer

	Engine::Ref<Engine::Shader> m_quadShader;	//!< Ref pointer to second shader
	Engine::Ref<Engine::VertexArray> m_quadVA;	//!< Ref pointer to second vertex array
	Engine::Ref<Engine::VertexBuffer> m_quadVB;	//!< Ref pointer to second vertex buffer
	Engine::Ref<Engine::IndexBuffer> m_quadIB;	//!< Ref pointer to second index buffer

	Engine::Ref<Engine::Texture2D> m_texture, m_pacmanTexture; //!< Ref pointer to textures

	Engine::OrthoCameraController m_cameraController;
private:

	glm::vec3 m_quadColor = { 0.2f, 0.3f, 0.8f };	//!< vector 3 of quad color for imgui
};

class engineApp : public Engine::Application
{
public:
	engineApp();			//!< Constructor
	~engineApp() override;	//!< Destructor
};