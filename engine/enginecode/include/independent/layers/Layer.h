/**
*@file Layer.h
*header file for set up of layer
*/
#pragma once

#include "core/Timestep.h"
#include "events/event.h"

namespace Engine
{
	/**
	*@class layer
	*variables for layer cpp
	*/
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer"); //<! layer constructor
		virtual ~Layer() = default; //<! layer deconstructor

		virtual void onAttach() {} //<! on attach layer
		virtual void onDetach() {} //<! on detach layer
		virtual void onUpdate(Timestep ts) {} //<! on update layer with timestep
		virtual void onImGuiRender() {} //<! on im gui render
		virtual void onEvent(Event& event) {} //<! on event layer

		inline const std::string& getName() const { return m_debugName; } //<! return debug name
	protected:
		std::string m_debugName;
	};

}