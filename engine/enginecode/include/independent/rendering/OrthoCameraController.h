/** @file OrthoCameraController.h
*	header file which sets up values for controlling camera
*/
#pragma once

#include "rendering/OrthoCamera.h"
#include "core/Timestep.h"

#include "events/event_window.h"
#include "events/event_mouse.h"

namespace Engine {

	/** @class OrthoCameraController
	*	set values to be used to control the orthographic camera
	*/
	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthoCamera& getCamera() { return m_camera; }
		float getZoomLevel() const { return m_zoomLevel; }
		void setZoomLevel(float level) { m_zoomLevel = level; }
		const OrthoCamera& getCamera() const { return m_camera; }
	private:
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_aspectRatio;
		float m_zoomLevel = 1.0f;
		OrthoCamera m_camera;

		bool m_rotation;

		glm::vec3 m_cameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_cameraRotation = 0.0f; //!< In degrees, in the anti-clockwise direction
		float m_cameraTranslationSpeed = 5.0f, 
			m_cameraRotationSpeed = 180.0f;
	};

}