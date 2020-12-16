/** @file Window.h
*	header file includes window event properties and attributes
*/
#pragma once
#include "engine_pch.h"

#include "events/event.h"

namespace Engine {

	struct WindowProperties
	{
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;


		WindowProperties(const std::string& title = "NG Game Engine", 
			unsigned int width = 1280, 
			unsigned int height = 720, 
			bool fullscreen = false) 
			: m_title(title), m_width(width), m_height(height) {}
	};

	/** @class Window
	*	functions for window events
	*/
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() = default;

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		//virtual void init(const WindowProperties& properties) = 0;
		//virtual void close() = 0;
		
		//<!Window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool VSync) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		static Scope<Window> create(const WindowProperties& properties = WindowProperties());
	};
}

