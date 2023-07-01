module;
#include <dwmapi.h>
#include "Internal.hpp"

export module Glib.Window:ABI;
import <string_view>;
import Glib.DefaultProperty;

export namespace gl::window::detail
{
	inline constexpr default_property_t<int> use_default = default_property_t{ CW_USEDEFAULT };

	[[nodiscard]]
	inline HWND__* CreateNativeWindow(const HINSTANCE& hinst
		, const std::wstring_view& class_name
		, const std::wstring_view& title
		, const unsigned long& styles
		, const unsigned long& options
		, const int& x
		, const int& y
		, const int& width
		, const int& height
		, const HWND& parent = nullptr
		, const HMENU& menu = nullptr
		, const LPVOID& uparams = nullptr)
		noexcept
	{
		HWND result = ::CreateWindowEx(options
		, class_name.data(), title.data()
		, styles, x, y, width, height
		, parent
		, menu
		, hinst, uparams);

		if (result == nullptr)
		{
			return nullptr;
		}

		BOOL value = TRUE;
#if _DEBUG
		HRESULT hr =
#endif
			::DwmSetWindowAttribute(result, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));

#if _DEBUG
		if (FAILED(hr))
		{
			::DestroyWindow(result);
			return nullptr;
		}
#endif

		return result;
	}

	inline bool DestroyNativeWindow(const HWND& hwnd) noexcept
	{
		return FALSE != ::DestroyWindow(hwnd);
	}

	inline long long DefaultWindowsProcedure(HWND__* const& hwnd, const unsigned int& msg, const unsigned long long& wparam, const long long& lparam) noexcept
	{
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
}
