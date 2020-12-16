/**
*@file LayerStack.h
*header file for set up of layer stack
*/
#pragma once


#include "layers/Layer.h"

#include <vector>

namespace Engine
{
	/**
	*@class LayerStack
	*variables for the creation of layers
	*/
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layerInsertIndex = 0;
	};
}