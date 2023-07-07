module;
#include "Internal.hpp"
#define _ATL_NO_AUTOMATIC_NAMESPACE
#include <atlimage.h>

export module Glib.Definitions;
import <filesystem>;

export namespace gl::device
{
	using FilePath = std::filesystem::path;
}

export namespace gl::device
{
	class ProcessInstance;
	class IContext;
	class DeviceContext;
	class CompatibleContext;
	class RenderingContext;
	class GlobalDeviceContext;
	class Colour;
	class IWindow;
}

export namespace gl::device::resource
{
	class Image;
	class Bitmap;
	class Palette;
	class ColorBrush;
	class Pen;
	class CompatibleBitmap;
	class Icon;
}

export namespace gl::window
{
	class Window;
	class ManagedWindow;
}

export namespace gl::device::native
{
	using WindowProcedure = long long(CALLBACK*)(HWND__*, unsigned int, unsigned long long, long long);
	using RawWindowProperty = tagWNDCLASSEXW;
	using HWND = HWND__*;
	using PaintStruct = tagPAINTSTRUCT;

	using NativeRect = tagRECT;
	using NativeContext = ::HDC__*;
	using NativeMenu = ::HMENU__*;
	using RawImage = ::ATL::CImage;
	using RawBitmap = ::HBITMAP__*;
	using RawIcon = ::HICON__*;
	using RawColorBrush = ::HBRUSH__*;
	using RawPen = ::HPEN__*;
	using RawPalette = ::HPALETTE__*;
	using RawFont = ::HFONT__*;
}
