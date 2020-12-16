#include "Engine2D.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "platforms/openGL/OpenGLShader.h"

Engine2D::Engine2D()
	: Layer("Engine::2D"), m_cameraController(1280.0f / 720.0f)
{

}

void Engine2D::onAttach()
{
	NG_PROFILE_FUNCTION();

	m_checkerboardTexture = Engine::Texture2D::create("assets/textures/checkerboard.png");
}

void Engine2D::onDetach()
{
	NG_PROFILE_FUNCTION();
}

void Engine2D::onUpdate(Engine::Timestep ts)
{
	// Update
	NG_PROFILE_FUNCTION();

	m_cameraController.onUpdate(ts);
	
	{	// Render
		NG_PROFILE_FUNCTION("Renderer Prep");
		Engine::RenderCommand::setClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Engine::RenderCommand::clear();
	}

	{
		NG_PROFILE_FUNCTION("Renderer Draw");
		Engine::Renderer2D::beginScene(m_cameraController.getCamera());

		//<!	Draw Quad						// POSITION										// SIZE									// ROTATION (IF APPLICABLE)				// Colour OR Texture							// TINT COLOUR
		Engine::Renderer2D::drawRotatedQuad(	{ -1.0f, 0.0f },								{ 0.8f, 0.8f },							glm::radians(-45.f),					{ 0.8f, 0.2f, 0.3f, 1.0f }	);
		Engine::Renderer2D::drawQuad(			{ 0.5f, -0.5f },								{ 0.5f, 0.75f },																{ 0.2f, 0.3f, 0.8f, 1.0f }	);
		Engine::Renderer2D::drawQuad(			{ -0.5, 0.5 },									{ 0.75, -0.5 },																	m_quadColour				);
		Engine::Renderer2D::drawRotatedQuad(	{ 0.0f, 0.0f, -0.1f },							{ 10.0f, 10.0f },						glm::radians(57.f),						m_checkerboardTexture, 10.f	,					 glm::vec4(0.5f, 0.9f, 0.9f, 1.0f));
		Engine::Renderer2D::drawQuad(			{ m_quadLocationX, -m_quadLocationY },			{ m_quadSizeX, -m_quadSizeY },													m_quadColour				); // Editable via IMGui
		Engine::Renderer2D::endScene();
	}
}

void Engine2D::onImGuiRender()
{
	NG_PROFILE_FUNCTION("Engine2D::onImGuiRender");
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_quadColour));
	ImGui::SliderFloat2("Square Size", &m_quadSizeX, 0.0f, 1.0f);
	ImGui::SliderFloat2("Square Position", &m_quadLocationX, -1.0f, 1.0f);

	if (ImGui::Button("Save"))
	{
		
		Engine::Renderer2D::endScene();
	}

	ImGui::End();
}

void Engine2D::onEvent(Engine::Event & e)
{
	m_cameraController.onEvent(e);
}