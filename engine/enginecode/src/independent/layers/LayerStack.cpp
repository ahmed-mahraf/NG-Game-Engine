/** @file LayerStack.cpp
*   creates layer stack and functions to push and overlay 
*/
#include "engine_pch.h"
#include "layers/LayerStack.h"

namespace Engine
{
	//<!layerstack constructor
	LayerStack::LayerStack()
	{
	}
	//<!layerstack deconstructor
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
		{
			layer->onDetach();
			delete layer;
		}
			
	}

	//<!push layerstack function
	void LayerStack::PushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
		m_layerInsertIndex++;
	}

	//<!push overlay function
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}

	//<!erases layer
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			layer->onDetach();
			m_layers.erase(it);
			m_layerInsertIndex--;
		}
	}
	//<!inserts layer
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			overlay->onDetach();
			m_layers.erase(it);
		}
			
	}
}