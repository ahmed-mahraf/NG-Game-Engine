#pragma once

/** @file event.h
*	header file to store event and dispatcher class
*/

#include "engine_pch.h"

#include "core/base.h"

namespace Engine 
{

	enum class EventType
	{
		None = 0,				/**< enum value None */
		WindowClose,			/**< enum value WindowClose */
		WindowResize,			/**< enum value WindowResize */
		WindowFocus,			/**< enum value WindowFocus */
		WindowLostFocus,		/**< enum value WindowLostFocus */
		WindowMoved,			/**< enum value WindowMoved */
		AppTick,				/**< enum value AppTick */
		AppUpdate,				/**< enum value AppUpdate */
		AppRender,				/**< enum value AppRender */
		KeyPressed,				/**< enum value KeyPressed */
		KeyReleased,			/**< enum value KeyReleased */
		KeyTyped,				/**< enum value KeyTyped */
		MouseButtonPressed,		/**< enum value MouseButtonPressed */
		MouseButtonReleased,	/**< enum value MouseButtonReleased */
		MouseMoved,				/**< enum value MouseMoved */
		MouseScrolled			/**< enum value MouseScrolled */
	};


	enum EventCategory
	{
		None = 0,									/**< enum value None */
		EventCategoryWindow =		BIT(0),			/**< enum value EventCategoryWindow */
		EventCategoryInput =		BIT(1),			/**< enum value EventCategoryInput */
		EventCategoryKeyboard =		BIT(2),			/**< enum value EventCategoryKeyboard */
		EventCategoryMouse =		BIT(3),			/**< enum value EventCategoryMouse */
		EventCategoryMouseButton =	BIT(4)			/**< enum value EventCategoryMouseButton */
	};


	/**
	*@class Event base class
	*/

	class Event
	{
	private:
		
	public:
		bool m_handled = false;

		virtual EventType getEventType() const = 0; //<! get the event type
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0; //<! get the event category
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) 
		{ 
			return getCategoryFlags() & category; 
		} //<! is this event in the category?
	};

	/**
	*@class EventDispatcher
	*/

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_event(event)
		{

		}

		template<typename T>
		bool dispatch(EventFn<T> func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}
	private:
		Event& m_event;	//<! internal storage of a reference to the event. Abstract event
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}