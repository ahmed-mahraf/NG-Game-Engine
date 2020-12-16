/** @file application.cpp
*	Fundemental class of the engine. A singleton which runs the game loop infinitely.
*/

#include "engine_pch.h"
#include "core/application.h"

#include "rendering/renderer.h"

#include "events/inputPoller.h"

#include <GLFW/glfw3.h>

namespace Engine {

	//<! declare instance
	Application* Application::s_instance = nullptr; 

	Application::Application()
	{
		NG_PROFILE_FUNCTION();

		//<! set instance
		GE_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;

		//<!create window
		m_window = Window::create();

		//<! set event callback for events
		m_window->setEventCallback(GE_BIND_EVENT_FN(Application::onEvent));

		//<! Activates the renderer
		Renderer::init();
		
		//<! Create new imgui layer
		m_ImGuiLayer = new ImGuiLayer();
		//<! uses layer to create game overlay
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		NG_PROFILE_FUNCTION();

		Renderer::close();
	}

	//<! push and attach layer to layerstack
	void Application::PushLayer(Layer* layer)
	{
		NG_PROFILE_FUNCTION();

		m_layerStack.PushLayer(layer);
		layer->onAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		NG_PROFILE_FUNCTION();

		m_layerStack.PushOverlay(layer);
		layer->onAttach();
	}

	//<! dispatch and handle events
	void Application::onEvent(Event &e)
	{
		NG_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::onWindowsCloseEvent));
		dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(Application::onWindowResizeEvent));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			
			(*--it)->onEvent(e);
			if (e.m_handled)
				break;
		}
	}

	//<! main run loop
	void Application::run()
	{
		NG_PROFILE_FUNCTION();

		while (m_running)
		{
			NG_PROFILE_SCOPE("Run Loop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_minimized)
			{
				{
					NG_PROFILE_SCOPE("Layerstack onUpdate");

					for (Layer* layer : m_layerStack)
						layer->onUpdate(timestep);
				}

				//<! Run IMGui
				m_ImGuiLayer->start();
				{
					NG_PROFILE_SCOPE("Layerstack onImGuiRender");

					for (Layer* layer : m_layerStack)
						layer->onImGuiRender();
				}

				//<! End imgui and update window
				m_ImGuiLayer->finish();
			}

			m_window->onUpdate();
		}
	}

	//<! on the event that the window is closed
	bool Application::onWindowsCloseEvent(WindowCloseEvent& e)
	{
		GE_CORE_INFO("Application closing...");
		m_running = false;
		return true;
	}

	bool Application::onWindowResizeEvent(WindowResizeEvent& e)
	{
		NG_PROFILE_FUNCTION();

		if (e.getWidth() == 0 || e.getHeight() == 0)
		{
			m_minimized = true;
			return false;
		}

		m_minimized = false;
		Renderer::onWindowResizeEvent(e.getWidth(), e.getHeight());

		return false;
	}

}