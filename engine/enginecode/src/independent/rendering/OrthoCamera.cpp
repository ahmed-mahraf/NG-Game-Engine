/** @file OrthoCamera.cpp
*	camera movement and other settings for ortho camera
*/
#include "engine_pch.h"
#include "rendering/OrthoCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	//<!Camera movement
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
		: m_MP(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_MV(1.0f)
	{
		NG_PROFILE_FUNCTION();

		m_MVP = m_MP * m_MV;
	}
	void OrthoCamera::setProjection(float left, float right, float bottom, float top)
	{
		NG_PROFILE_FUNCTION();

		m_MP = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_MVP = m_MP * m_MV;
	}

	void OrthoCamera::recalculateMV()
	{
		NG_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position)*
			glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

		m_MV = glm::inverse(transform);
		m_MVP = m_MP * m_MV;
	}
	
}