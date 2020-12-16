/** @file OrthoCameraController.cpp
*	key presses for control over ortho camera
*/
#include "engine_pch.h"
#include "rendering/OrthoCameraController.h"

#include "platforms/GLFW/GLFWInputPoller.h"
#include "platforms/GLFW/GLFWCodes.h"

namespace Engine {

	OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotation)
		: m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel), m_rotation(rotation)
	{

	}

	void OrthoCameraController::onUpdate(Timestep ts)
	{
		NG_PROFILE_FUNCTION();

		if (GLFWInputPoller::isKeyPressed(NG_KEY_A))
		{
			m_cameraPosition.x -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y -= sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
			
		else if (GLFWInputPoller::isKeyPressed(NG_KEY_D))
		{
			m_cameraPosition.x += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y += sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}

		if (GLFWInputPoller::isKeyPressed(NG_KEY_W))
		{
			m_cameraPosition.x += -sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
		else if (GLFWInputPoller::isKeyPressed(NG_KEY_S))
		{
			m_cameraPosition.x -= -sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
			m_cameraPosition.y -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
		}
			

		if (m_rotation)
		{
			if (GLFWInputPoller::isKeyPressed(NG_KEY_Q))
				m_cameraRotation += m_cameraRotationSpeed * ts;
			if (GLFWInputPoller::isKeyPressed(NG_KEY_E))
				m_cameraRotation -= m_cameraRotationSpeed * ts;

			if (m_cameraRotation > 180.0f)
			{
				m_cameraRotation -= 360.0f;
			}
			else if (m_cameraRotation <= -180.0f)
			{
				m_cameraRotation += 360.0f;
			}

			m_camera.setRotation(m_cameraRotation);
		}

		m_camera.setPosition(m_cameraPosition);

		m_cameraTranslationSpeed = m_zoomLevel;
	}

	void OrthoCameraController::onEvent(Event& e)
	{
		NG_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(GE_BIND_EVENT_FN(OrthoCameraController::onMouseScrolledEvent));
		dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(OrthoCameraController::onWindowResizeEvent));
	}

	bool OrthoCameraController::onMouseScrolledEvent(MouseScrolledEvent& e)
	{
		NG_PROFILE_FUNCTION();

		m_zoomLevel -= e.getYOffset() * 0.25f;
		m_zoomLevel = std::max(m_zoomLevel, 0.25f);
		m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}

	bool OrthoCameraController::onWindowResizeEvent(WindowResizeEvent& e)
	{
		NG_PROFILE_FUNCTION();

		m_aspectRatio = (float)e.getWidth() / (float)e.getHeight();
		m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
		return false;
	}

}