#pragma once
/** @file event_Key.h
*  A Header file containing the key events for the application.
*/

#include "event.h"
#include "events/event.h"


namespace Engine {

	/**
	* @class Key
	* Event class. Provides the values for the Key event.
	*/

	class KeyEvent : public Event
	{
	public:
		inline int getKeycode() const { return m_keycode; } //<! gets keycode value

		int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; } //<! gets category flags

	protected:
		KeyEvent(int keycode) 
			: m_keycode(keycode) {} //<! declares Constructor

		int m_keycode; //<! keycode int value

	};

	/**
	* @class KeyPressedEvent
	* Event class. Provides the values for the Key Pressed event.
	*/

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) 
			: KeyEvent(keycode), m_repeatCount(repeatCount) {} //<! declares Constructor
		
		inline int getRepeatCount() const { return m_repeatCount; } //<! gets repeat count value
		
		std::string toString() const override //<! gets string for event type
		{
			std::stringstream ss;
			ss << "Key Pressed Event: " << m_keycode << " (" << m_repeatCount << " times)";
			return ss.str();
		}

		static EventType getStaticType() { return EventType::KeyPressed; } //<! gets static event type
		EventType getEventType() const override { return EventType::KeyPressed; } //<! gets event type
		virtual const char* getName() const override { return "KeyPressed"; }

	private:
		int m_repeatCount; //<! repeat count int value
	};

	/**
	* @class KeyReleasedEvent
	* Event class. Provides the values for the Key Released event.
	*/
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Released Event: " << m_keycode;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::KeyReleased; } //<! gets static event type
		EventType getEventType() const override { return EventType::KeyReleased; } //<! gets event type
		virtual const char* getName() const override { return "KeyReleased"; }
	};

	/**
	* @class KeyTypedEvent
	* Event class. Provides the values for the Key Typed event.
	*/

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "Key Typed Event: " << m_keycode;
			return ss.str();
		}

		static EventType getStaticType() { return EventType::KeyTyped; } //<! gets static event type
		EventType getEventType() const override { return EventType::KeyTyped; } //<! gets event type
		virtual const char* getName() const override { return "KeyTyped"; }
	};

}





