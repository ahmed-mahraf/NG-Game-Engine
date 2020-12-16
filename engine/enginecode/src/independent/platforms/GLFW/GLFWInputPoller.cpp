/** @file GLFWInputPoller.cpp
*	finds states and positions of mouse using GLFW
*/
#include "engine_pch.h"
#include "core/application.h"
#include "events/inputPoller.h"
#include "platforms/GLFW/GLFWCodes.h"
#include "platforms/GLFW/GLFWInputPoller.h"
#include "windows/WindowsWindow.h"
#include <GLFW/glfw3.h>
#include "windows/window.h"

namespace Engine
{
#ifdef NG_PLATFORM_WINDOWS
	Scope<InputPoller> InputPoller::s_instance = createScope <GLFWInputPoller>();
#else 
	NG_ASSERT(0, "We only support windows");
#endif

	//<!when a key is pressed, find and return which key and state of press
	bool GLFWInputPoller::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	//<!when mouse button is pressed, return which button and state
	bool GLFWInputPoller::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	//<!uses mousex and mousey to find position of mouse on screen
	std::pair<float, float> GLFWInputPoller::getMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double x_Pos, y_Pos;
		glfwGetCursorPos(window, &x_Pos, &y_Pos);

		return { (float)x_Pos, (float)y_Pos };
	}
	//<!finds x position of mouse
	float GLFWInputPoller::getMouseXImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double x_Pos, y_Pos;
		glfwGetCursorPos(window, &x_Pos, &y_Pos);

		return (float)x_Pos;
	}
	//<!get y position of mouse
	float GLFWInputPoller::getMouseYImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::getInstance().getWindow().getNativeWindow());
		double x_Pos, y_Pos;
		glfwGetCursorPos(window, &x_Pos, &y_Pos);

		return (float)y_Pos;
	}

}