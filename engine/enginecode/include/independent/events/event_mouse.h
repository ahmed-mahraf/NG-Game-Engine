#pragma once
/**
* @file event_Mouse.h
* @brief A Header file containing the mouse events for the application.
*/


#include "event.h"


namespace Engine
{
	/**
	* @class MouseMovedEvent
	* Event class. Provides the values for the mouse moved events.
	*/

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_xPos(x), m_yPos(y) {}

		inline float getX() const { return m_xPos; }
		inline float getY() const { return m_yPos; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved Event: " << m_xPos << ", " << m_yPos;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::MouseMoved; }
		EventType getEventType() const override { return EventType::MouseMoved; }
		virtual const char* getName() const override { return "MouseMoved"; }
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	private:
		float m_xPos, m_yPos;
	};

	/**
	* @class MouseScrolledEvent
	* Event class. Provides the values for the mouse scrolled events.
	*/

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x_offset, float y_offset)
			: m_xOffset(x_offset), m_yOffset(y_offset) {}

		inline float getXOffset() const { return m_xOffset; }
		inline float getYOffset() const { return m_yOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled Event: " << getXOffset() << ", " << getYOffset();
			return ss.str();
		}

		static EventType getStaticType() { return EventType::MouseScrolled; }
		EventType getEventType() const override { return EventType::MouseScrolled; }
		virtual const char* getName() const override { return "MouseScrolled"; }
		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

	private:
		float m_xOffset, m_yOffset;
	};

	/**
	* @class MouseButtonEvent
	* Event class. Provides the values for the mouse button events.
	*/

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_button; }

		int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}

		int m_button;
	};

	/**
	* @class MouseButtonPressedEvent
	* Event class. Provides the values for the mouse button pressed events.
	*/

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Pressed Event: " << m_button;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::MouseButtonPressed; }
		EventType getEventType() const override { return EventType::MouseButtonPressed; }
		virtual const char* getName() const override { return "MouseButtonPressed"; }
	};

	/**
	* @class MouseButtonReleasedEvent
	* Event class. Provides the values for the mouse button released events.
	*/
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Released Event: " << m_button;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::MouseButtonReleased; }
		EventType getEventType() const override { return EventType::MouseButtonReleased; }
		virtual const char* getName() const override { return "MouseButtonReleased"; }
	};
}
