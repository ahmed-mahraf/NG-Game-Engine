/** @file OrthoCamera.h
*	header file which sets up for orthographic camera
*/
#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	class OrthoCamera
	{

		/**
	* @class OrthoCamera
	* Class for camera
	*/

	public:
		OrthoCamera(float left, float right, float bottom, float top);

		void setProjection(float left, float right, float bottom, float top);

		const glm::vec3& getPosition() const { return m_position; }
		void setPosition(const glm::vec3& position) { m_position = position; recalculateMV(); }

		float getRotation() const { return m_rotation; }
		void setRotation(float rotation) { m_rotation = rotation; recalculateMV(); }

		const glm::mat4& getMP()const { return m_MP; }
		const glm::mat4& getMV() const { return m_MV; }
		const glm::mat4& getMVP() const { return m_MVP; }

	private:
		void recalculateMV();

	private:
		glm::mat4 m_MP;
		glm::mat4 m_MV;
		glm::mat4 m_MVP;

		glm::vec3 m_position = { 0.0f, 0.0f , 0.0f };
		float m_rotation = 0.0f;

	};
}
