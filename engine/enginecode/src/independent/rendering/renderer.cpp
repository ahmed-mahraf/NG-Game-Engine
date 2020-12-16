/** @file renderAPI.cpp
*	initialise renderer and functions for scene settings and commands 
*/

#include "engine_pch.h"
#include "rendering/renderer.h"

#include "platforms/openGL/OpenGLShader.h"
#include "rendering/renderer2D.h"

namespace Engine
{
	void Renderer::init()
	{
		NG_PROFILE_FUNCTION();

		RenderCommand::init();
		Renderer2D::init();
	}

	void Renderer::close()
	{
		Renderer2D::close();
	}

	Scope<Renderer::SceneData> Renderer::s_sceneData = createScope<Renderer::SceneData>();

	void Renderer::onWindowResizeEvent(uint32_t width, uint32_t height)
	{
		RenderCommand::setViewport(0, 0, width, height);
	}

	//<!start render scene using camera projection matric
	void Renderer::beginScene(OrthoCamera& camera)
	{
		s_sceneData->MVP = camera.getMVP();
	}
	//<!end render scene
	void Renderer::endScene()
	{

	}
	//<!submit render scene
	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vA, const glm::mat4& transform)
	{
		shader->bind();
		shader->setMat4("u_ViewProjection", s_sceneData->MVP);
		shader->setMat4("u_Transform", transform);

		vA->bind();
		RenderCommand::drawIndexed(vA);
	}
}