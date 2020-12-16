/** @file WindowsWindow.cpp
*	initialise and create GLFW window
*/
#include "engine_pch.h"

#include "windows/WindowsWindow.h"

#include "windows/window.h"

#include "systems/MyLogger.h"

#include "events/event_key.h"
#include "events/event_mouse.h"
#include "events/event_window.h"

#include "platforms/openGL/OpenGLGraphicsContext.h"

#include <glm/gtc/matrix_transform.hpp>

#include "rendering/renderer.h"



#ifdef NG_PLATFORM_WINDOWS
#include "platforms/GLFW/GLFWCodes.h"
#endif // NG_PLATFORM_WINDOWS

namespace Engine
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		GE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::create(const WindowProperties & properties)
	{
		return createScope <WindowsWindow>(properties);
	}

	//<!initialise windows properties
	WindowsWindow::WindowsWindow(const WindowProperties & properties)
	{
		NG_PROFILE_FUNCTION();

		init(properties);
	}

	//<!desconstructor for glfw window
	WindowsWindow::~WindowsWindow()
	{
		NG_PROFILE_FUNCTION();

		close();
	}

	//<!initialise glfw window
	void WindowsWindow::init(const WindowProperties & properties)
	{
		NG_PROFILE_FUNCTION();

		m_data.m_title = properties.m_title; //!<set the title
		m_data.m_width = properties.m_width;
		m_data.m_height = properties.m_height;

		GE_CORE_INFO("Creating window {0} ({1}, {2})", properties.m_title, properties.m_width, properties.m_height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			GE_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		//<!create glfw window
		m_nativeWindow = glfwCreateWindow((int)properties.m_width, (int)properties.m_height, properties.m_title.c_str(), nullptr, nullptr);

		m_context = GraphicsContext::create(m_nativeWindow);
		m_context->init();

		glfwSetWindowUserPointer(m_nativeWindow, &m_data);
		setVSync(true);

		//<!error call back event function
		glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.m_width = width;
			data.m_height = height;

			WindowResizeEvent event(width, height);
			data.m_EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;

			data.m_EventCallback(event);
		});

		glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.m_EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.m_EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.m_EventCallback(event);
				break;
			}
			}
		});

		glfwSetCharCallback(m_nativeWindow, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.m_EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.m_EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.m_EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.m_EventCallback(event);
		});

		glfwSetCursorPosCallback(m_nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.m_EventCallback(event);
		});
	}

	//<!destroy window when window is closed
	void WindowsWindow::close()
	{
		NG_PROFILE_FUNCTION();

		glfwDestroyWindow(m_nativeWindow);

		if (!s_GLFWInitialized)
			glfwTerminate();
	}

	//<!update loop for glfw window
	void WindowsWindow::onUpdate()
	{
		NG_PROFILE_FUNCTION();

		glfwPollEvents();
		m_context->swapBuffers();
	}


	//<!set vsync
	void WindowsWindow::setVSync(bool enabled)
	{
		NG_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.m_isVSync = enabled;
	}

	bool WindowsWindow::isVSync() const
	{
		return m_data.m_isVSync;
	}
}