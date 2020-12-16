/** @file renderer2D.h
*	header file sets up 2d rendering 
*/
#pragma once

#include "rendering/OrthoCamera.h"

#include "Texture.h"

namespace Engine {

	/** @class Renderer2D
	* sets up variables and functions to be used by 2d renderer
	*/

	class Renderer2D
	{
	public:
		static void init(); //<! Function to call init
		static void close(); //<! Function to call close
		
		static void beginScene(const OrthoCamera& camera); //<! Function to begin the scene
		static void endScene(); //<! Function to end the scene

		//<! Primitives
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color); //<! Function to draw a vector 2 quad
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color); //<! Function to draw a vector 3 quad
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f)); //<! Function to draw a vector 3 textured quad
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f)); //<! Function to draw a vector 2 textured quad

		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	};

}