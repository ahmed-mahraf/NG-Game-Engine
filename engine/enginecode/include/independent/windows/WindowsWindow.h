#pragma once
/**
* @file WindowsWindow.h
*  A Header file containing the main parameters for the camera, shapes and inputs
*/

#include "windows/window.h"
#include "rendering/graphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	/**
	* @class WindowsWindow
	* Provides the values for the GLFW window implementation
	*/

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties); //<!constructor
		virtual ~WindowsWindow(); //<! desconstructor

		void onUpdate() override; //<! update function

		inline unsigned int getWidth() const override { return m_data.m_width; } //<! get width of window
		inline unsigned int getHeight() const override { return m_data.m_height; } //<! get height of window

		//<!Window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { m_data.m_EventCallback = callback; }
		void setVSync(bool enabled) override; //<! set vsync
		bool isVSync() const override; //<! vsync

		inline virtual void* getNativeWindow() const override { return m_nativeWindow; } //<! get native window

	private:
		void init(const WindowProperties& properties); //<1 where most of the code will be implemented
		void close();//<! close the window
	private:
		GLFWwindow* m_nativeWindow; //<! glfw window pointer to native window
		Scope<GraphicsContext> m_context;

		struct WindowData
		{
			std::string m_title;
			unsigned int m_width, m_height;
			bool m_isVSync;

			EventCallbackFn m_EventCallback;
		};

		WindowData m_data;
	};


}