#pragma once

#include "engine.h"
#include <chrono>

class Engine2D : public Engine::Layer
{
public:
	Engine2D();
	virtual ~Engine2D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(Engine::Timestep ts) override;
	virtual void onImGuiRender() override;
	void onEvent(Engine::Event& e) override;
private:
	Engine::OrthoCameraController m_cameraController;

	// Temp
	Engine::Ref<Engine::VertexArray> m_quadVA;
	Engine::Ref<Engine::VertexBuffer> m_quadVB;
	Engine::Ref<Engine::IndexBuffer> m_quadIB;
	Engine::Ref<Engine::Shader> m_quadShader;

	Engine::Ref<Engine::Texture2D> m_checkerboardTexture;

	struct ProfileResult
	{
		const char* name;
		float time;
	};

	std::vector<ProfileResult> m_profileResults;

	glm::vec4 m_quadColour = { 0.2f, 0.3f, 0.8f, 1.0f };

	float m_quadSizeX = -0.5f;
	float m_quadSizeY = -0.5f;

	float m_quadLocationX = 0.75f;
	float m_quadLocationY = 0.5f;
};