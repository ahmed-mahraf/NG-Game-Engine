/** @file base.h
* contains code for bit macros and templates
*/
#pragma once

#include <memory>

#define BIT(x) (1 << x) //<! Macro for bit

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) //<! Macro for binding event 

namespace Engine
{
	template<typename T>
	using Scope = std::unique_ptr<T>; //<! Unique pointer as a scoped smart pointer
	template<typename T, typename ... Args>
	constexpr Scope<T> createScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>; //<! shared pointer as a smart referenced pointer
	template<typename T, typename ... Args>
	constexpr Ref<T> createRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}