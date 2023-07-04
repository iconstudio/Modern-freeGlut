module;
#include "Internal.hpp"
module Glib.Device.Resource.IBitmap;

gl::device::resource::IBitmap
gl::device::resource::IBitmap::Copy(const IContext& context)
const noexcept
{
	IBitmap result{};
	TryCopy(context, result);
	return result;
}

bool
gl::device::resource::IBitmap::TryCopy(const IContext& context, IBitmap& output)
const noexcept
{
	auto& handle = GetHandle();
	if (nullptr == handle)
	{
		return false;
	}

	if (0 == cachedWidth || 0 == cachedHeight)
	{
		return false;
	}

	const HDC& hdc = context.GetHandle();
	if (nullptr == hdc)
	{
		return false;
	}

	HDC memory = context.Delegate(::CreateCompatibleDC);
	if (nullptr == memory)
	{
		return false;
	}

	HBITMAP bitmap = ::CreateCompatibleBitmap(hdc, cachedWidth, cachedHeight);
	if (nullptr == bitmap)
	{
		::DeleteDC(memory);

		return false;
	}

	HGDIOBJ previous = ::SelectObject(memory, bitmap);
	if (nullptr == previous)
	{
		::DeleteObject(bitmap);
		::DeleteDC(memory);

		return false;
	}

	if (0 == ::BitBlt(memory, 0, 0, cachedWidth, cachedHeight, hdc, 0, 0, SRCCOPY))
	{
		::SelectObject(memory, previous);
		::DeleteObject(bitmap);
		::DeleteDC(memory);

		return false;
	}

	::SelectObject(memory, previous);

	output = IBitmap(bitmap);

	::DeleteDC(memory);
	return true;
}

bool
gl::device::resource::IBitmap::Destroy()
noexcept
{
	if (nullptr != GetHandle())
	{
		bool result = 0 != Delegate(::DeleteObject);
		base::operator=(nullifier);

		return result;
	}

	return false;
}

bool
gl::device::resource::IBitmap::Draw(const IWindowHandle& window_handle, const int& x, const int& y, const int& srcx, const int& srcy)
const noexcept
{
	native::NativeContext global_context = IWindowHandle{}.AcquireNativeContext();
	if (nullptr == global_context)
	{
		return false;
	}

	native::NativeContext window_context = window_handle.AcquireNativeContext();
	if (nullptr == window_context)
	{
		return false;
	}

	HGDIOBJ previous = ::SelectObject(window_context, GetHandle());

	bool result = (0 == ::BitBlt(window_context
		, x, y, cachedWidth, cachedHeight
		, global_context
		, srcx, srcy, SRCCOPY));

	::SelectObject(window_context, previous);
	window_handle.ReleaseNativeContext(window_context);
	IWindowHandle{}.ReleaseNativeContext(global_context);

	return result;
}

bool
gl::device::resource::IBitmap::Draw(const IContext& render_context, const IContext& window_context, const int& x, const int& y, const int& srcx, const int& srcy)
const noexcept
{
	native::NativeContext target = render_context.GetHandle();
	if (nullptr == target)
	{
		return false;
	}

	native::NativeContext src = window_context.GetHandle();
	if (nullptr == src)
	{
		return false;
	}

	HGDIOBJ previous = ::SelectObject(target, GetHandle());

	if (0 == ::BitBlt(target
		, x, y, cachedWidth, cachedHeight
		, src
		, srcx, srcy, SRCCOPY)
	)
	{
		::SelectObject(target, previous);

		return false;
	}

	::SelectObject(target, previous);

	return true;
}

bool
gl::device::resource::IBitmap::GetPixel(const IContext& context, const int& x, const int& y, Colour& output)
const
{
	if (RawRGB result = context.Delegate(::GetPixel, x, y); CLR_INVALID != result)
	{
		output = device::MakeColor(result);

		return true;
	}
	else
	{
		return false;
	}
}

int
gl::device::resource::IBitmap::GetWidth()
const noexcept
{
	return cachedWidth;
}

int
gl::device::resource::IBitmap::GetHeight()
const noexcept
{
	return cachedHeight;
}

gl::device::resource::IBitmap::IBitmap(const handle_type& handle)
noexcept
	: base(handle)
{
	::SIZE result{};
	if (0 != ::GetBitmapDimensionEx(handle, &result))
	{
		cachedWidth = result.cx;
		cachedHeight = result.cy;
	}
}

gl::device::resource::IBitmap::IBitmap(handle_type&& handle)
noexcept
	: base(std::move(handle))
	, shouldDestroy(true)
{
	::SIZE result{};
	if (0 != ::GetBitmapDimensionEx(GetHandle(), &result))
	{
		cachedWidth = result.cx;
		cachedHeight = result.cy;
	}
}

gl::device::resource::IBitmap::~IBitmap()
noexcept
{
	if (shouldDestroy)
	{
		Destroy();
	}
}
