/** @file renderer.h
*	header file for creation of renderer values
*/
#pragma once
#include "rendering/renderCommand.h"
#include "rendering/OrthoCamera.h"
#include "rendering/shader.h"

namespace Engine
{
	/** @class Renderer
	*	set up variables and functions for rendering scene
	*/
	class Renderer
	{
	public:
		static void init();
		static void close();
		static void onWindowResizeEvent(uint32_t width, uint32_t height);
		static void beginScene(OrthoCamera& cam);
		static void endScene();

		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vA, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 MVP;
		};

		static Scope<SceneData> s_sceneData;

	};


}