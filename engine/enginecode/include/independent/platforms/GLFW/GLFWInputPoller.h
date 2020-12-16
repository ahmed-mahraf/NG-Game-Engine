#pragma once
/**
* @file GLFWInputPoller.h
*  A Header file includes windows API specifics
*/

#include "events/inputPoller.h"

namespace Engine
{
	/**
	* @class GLFWInputPoller
	*  Provides the values for the polling event implementation
	*/
	class GLFWInputPoller : public InputPoller
	{
	protected:
		bool isKeyPressedImpl(int keycode) override; //<! windows API specific implementation of key press
		bool isMouseButtonPressedImpl(int button) override; //<! windows API specifc implementation of mouse button press
		std::pair<float, float> getMousePositionImpl() override; //<! windows API specifc implementaion of mouse position
		float getMouseXImpl() override; //<! windows API specific implementation of mouse x position
		float getMouseYImpl() override; //<! windows API specific implementation of mouse y position
	};
}

