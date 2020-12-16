#pragma once
/**
* @file event_window.h
* @brief A Header file containing windows events for application
*/

#include "event.h"


namespace Engine
{
	/**
	* @class WindowResizeEvent
	* Event class. Provides the values for the Window Resize event.
	*/

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height) {}

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::WindowResize; }
		EventType getEventType() const override { return EventType::WindowResize; }
		virtual const char* getName() const override { return "WindowResize"; }
		int getCategoryFlags() const override { return EventCategoryWindow; }

	private:
		unsigned int m_width, m_height;
	};

	/**
	* @class WindowCloseEvent
	* Event class. Provides the values for the Window Close event.
	*/

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		static EventType getStaticType() { return EventType::WindowClose; }
		EventType getEventType() const override { return EventType::WindowClose; }
		virtual const char* getName() const override { return "WindowClose"; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/**
	* @class AppTickEvent
	* Event class. Provides the values for the App Tick event.
	*/

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		static EventType getStaticType() { return EventType::AppTick; }
		EventType getEventType() const override { return EventType::AppTick; }

		virtual const char* getName() const override { return "AppTick"; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/**
	* @class AppUpdateEvent
	* Event class. Provides the values for the App Update event.
	*/

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		static EventType getStaticType() { return EventType::AppUpdate; }
		EventType getEventType() const override { return EventType::AppUpdate; }

		virtual const char* getName() const override { return "AppUpdate"; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/**
	* @class AppRenderEvent
	* Event class. Provides the values for the App Render event.
	*/

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		static EventType getStaticType() { return EventType::AppRender; }
		EventType getEventType() const override { return EventType::AppRender; }

		virtual const char* getName() const override { return "AppRender"; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};
}
