/** @file application.h
*	header file includes events
*/
#pragma once

#include "core/base.h"

#include "windows/window.h"
#include "layers/LayerStack.h"
#include "events/event.h"
#include "events/event_window.h"

#include "core/Timestep.h"

#include "ImGui/ImGuiLayer.h"


namespace Engine {

	/**
	*@class Application
	*Fundemental class of the engine. A singleton which runs the game loop infinitely.
	*/

	class Application
	{
	public:
		Application(); //<! Constructor
		virtual ~Application(); //<! Deconstructor

		void run(); //<! Main loop

		void onEvent(Event& e); //<! called when an event happens

		void PushLayer(Layer* layer); //<! Push Layer Function
		void PushOverlay(Layer* layer); //<! Push Overlay Function

		inline Window& getWindow() { return *m_window; } //<! Window getter from singleton pattern 
		inline static Application& getInstance() { return *s_instance; } //<! Instance getter from singleton pattern

	private:
		bool onWindowsCloseEvent(WindowCloseEvent& e); //<! onclose event
		bool onWindowResizeEvent(WindowResizeEvent& e); //<! onclose event
	private:
		Scope<Window> m_window; //<! Scope pointer to GLFW windows
		ImGuiLayer* m_ImGuiLayer; //<! ImGuiLayer 

		bool m_running = true; //<! m_running is true
		bool m_minimized = false;

		LayerStack m_layerStack; //<! Layer Stack
		float m_LastFrameTime = 0.0f; //<! A float to show Last Frame Time
	private:
		static Application* s_instance; //<! Singleton instance of the application
	};

	Application* startApplication(); //<! Function definition which provides an entry hook

}