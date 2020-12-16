/**
*@file ImGuiLayer.h
*set up for imgui layer
*/
#pragma once

#include "layers/Layer.h"

#include "events/event_key.h"
#include "events/event_mouse.h"
#include "events/event_window.h"

namespace Engine 
{
	/**
	*@class ImGuiLayer
	*variables to be used in imgui layer
	*/
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;

		void start();
		void finish();
	private:
		float m_Time = 0.0f;
	};

}
