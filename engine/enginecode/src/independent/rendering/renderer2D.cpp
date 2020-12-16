/** @file renderer2D.cpp
*	functions made for rendering 
*/
#include "engine_pch.h"
#include "rendering/renderer2D.h"

#include "rendering/VertexArray.h"
#include "rendering/shader.h"
#include "rendering/renderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> m_quadVA;
		Ref<Shader> m_quadShader;
		Ref<Shader> m_quadTexture;

		Ref<Texture2D> m_quadWhiteTexture;
	};

	static Renderer2DStorage* s_data;

	void Renderer2D::init()
	{
		NG_PROFILE_FUNCTION();

		s_data = new Renderer2DStorage;
		s_data->m_quadVA = VertexArray::create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> m_quadVB;
		m_quadVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));
		m_quadVB->setLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_data->m_quadVA->addVertexBuffer(m_quadVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> m_quadIB;
		m_quadIB = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_data->m_quadVA->setIndexBuffer(m_quadIB);

		s_data->m_quadWhiteTexture = Texture2D::create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_data->m_quadWhiteTexture->setData(&whiteTextureData, sizeof(uint32_t));


		s_data->m_quadShader = Shader::create("assets/shaders/FlatColour.glsl");
		s_data->m_quadTexture = Shader::create("assets/shaders/Texture.glsl");
		s_data->m_quadTexture->bind();
		s_data->m_quadTexture->setInt("u_Texture", 0);
	}

	void Renderer2D::close()
	{
		NG_PROFILE_FUNCTION();

		delete s_data;
	}

	void Renderer2D::beginScene(const OrthoCamera & camera)
	{
		NG_PROFILE_FUNCTION();

		s_data->m_quadShader->bind();
		s_data->m_quadShader->setMat4("u_ViewProjection", camera.getMVP());

		s_data->m_quadTexture->bind();
		s_data->m_quadTexture->setMat4("u_ViewProjection", camera.getMVP());
	}

	void Renderer2D::endScene()
	{
		NG_PROFILE_FUNCTION();
	}

	void Renderer2D::drawQuad(const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		NG_PROFILE_FUNCTION();

		s_data->m_quadTexture->setFloat4("u_Color", color);
		s_data->m_quadTexture->setFloat("u_TilingFactor", 1.0f);
		s_data->m_quadWhiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->m_quadTexture->setMat4("u_Transform", transform);

		s_data->m_quadVA->bind();
		RenderCommand::drawIndexed(s_data->m_quadVA);
	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		NG_PROFILE_FUNCTION();

		s_data->m_quadTexture->setFloat4("u_Color", tintColor);
		s_data->m_quadTexture->setFloat("u_TilingFactor", tilingFactor);
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->m_quadTexture->setMat4("u_Transform", transform);

		s_data->m_quadVA->bind();
		RenderCommand::drawIndexed(s_data->m_quadVA);
	}
	void Renderer2D::drawRotatedQuad(const glm::vec2 & position, const glm::vec2 & size, float rotation, const glm::vec4 & color)
	{
		drawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	void Renderer2D::drawRotatedQuad(const glm::vec3 & position, const glm::vec2 & size, float rotation, const glm::vec4 & color)
	{
		NG_PROFILE_FUNCTION();

		s_data->m_quadTexture->setFloat4("u_Color", color);
		s_data->m_quadTexture->setFloat("u_TilingFactor", 1.0f);
		s_data->m_quadWhiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.f, 0.f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->m_quadTexture->setMat4("u_Transform", transform);

		s_data->m_quadVA->bind();
		RenderCommand::drawIndexed(s_data->m_quadVA);
	}
	void Renderer2D::drawRotatedQuad(const glm::vec2 & position, const glm::vec2 & size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		drawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}
	void Renderer2D::drawRotatedQuad(const glm::vec3 & position, const glm::vec2 & size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		NG_PROFILE_FUNCTION();

		s_data->m_quadTexture->setFloat4("u_Color", tintColor);
		s_data->m_quadTexture->setFloat("u_TilingFactor", tilingFactor);
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.f, 0.f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_data->m_quadTexture->setMat4("u_Transform", transform);

		s_data->m_quadVA->bind();
		RenderCommand::drawIndexed(s_data->m_quadVA);
	}
}