#pragma once
/**
* @file inputPoller.h
* @brief A Header file includes windows API specifics
*/

namespace Engine
{

	/**
	* @class InputPoller
	* Provides the values for the polling events
	*/

	class InputPoller
	{
	protected:
		InputPoller() = default;
	public:
		InputPoller(const InputPoller&) = delete;
		InputPoller& operator=(const InputPoller&) = delete;
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); } //<! is the key with this keycode pressed

		inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); } //<! is this mouse button pressed
		inline static std::pair<float, float> getMousePosition() { return s_instance->getMousePositionImpl(); } //<! get current position of the mouse
		inline static float getMouseX() { return s_instance->getMouseXImpl(); } //<! get the current x position of the mouse
		inline static float getMouseY() { return s_instance->getMouseYImpl(); } //<! get the current y position of the mouse
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0; //<! windows API specific implementation of key press

		virtual bool isMouseButtonPressedImpl(int button) = 0; //<! windows API specifc implementation of mouse button press
		virtual std::pair<float, float> getMousePositionImpl() = 0; //<! windows API specifc implementaion of mouse position
		virtual float getMouseXImpl() = 0; //<! windows API specific implementation of mouse x position
		virtual float getMouseYImpl() = 0; //<! windows API specific implementation of mouse y position
	private:
		static Scope<InputPoller> s_instance; //<! single instance pointer - singleton, however only internal implementation
	};
}