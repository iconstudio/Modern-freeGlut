module;
#include "Internal.hpp"

module Glib.Device.Resource.Bitmap;
import Glib.Device.Colour;
import Glib.Device.IWindow;
import Glib.Device.Context;
import Glib.Device.CompatibleContext;
import Glib.Device.Resource.CompatibleBitmap;

gl::device::resource::Bitmap
gl::device::resource::Bitmap::Load(const FilePath& path)
noexcept
{
	//auto handle = ::LoadBitmap(nullptr, path.c_str());
}

bool
gl::device::resource::Bitmap::TryLoad(const FilePath& path, Bitmap& output)
noexcept
{
	return false;
}

gl::device::resource::Bitmap
gl::device::resource::Bitmap::Load(const int& id)
noexcept
{
	return Bitmap();
}

bool
gl::device::resource::Bitmap::TryLoad(const int& id, Bitmap& output)
noexcept
{
	return false;
}

gl::device::resource::Bitmap
gl::device::resource::Bitmap::Copy(const IContext& context)
const noexcept
{
	Bitmap result{};
	TryCopy(context, result);
	return result;
}

bool
gl::device::resource::Bitmap::TryCopy(const IContext& context, Bitmap& output)
const noexcept
{
	const native::RawBitmap& handle = GetHandle();
	if (nullptr == handle)
	{
		return false;
	}

	if (0 == cachedWidth || 0 == cachedHeight)
	{
		return false;
	}

	// Automatic Destroy
	CompatibleContext current = context.CreateCompatibleContext();
	if (nullptr == current)
	{
		return false;
	}

	// Automatic Destroy
	CompatibleBitmap bitmap = current.CreateCompatibleBitmap(cachedWidth, cachedHeight);
	if (nullptr == bitmap)
	{
		return false;
	}

	auto previous = current.Select(bitmap);

	bool result = (0 == ::BitBlt(current
		, 0, 0, cachedWidth, cachedHeight
		, context, 0, 0
		, SRCCOPY));

	current.Select(previous);

	output = Bitmap(std::move(bitmap));

	return result;
}

bool
gl::device::resource::Bitmap::Fill(const Colour& color)
noexcept
{
	GlobalDeviceContext render_context = GlobalDeviceContext();
	if (nullptr == render_context)
	{
		return false;
	}

	CompatibleContext current = render_context.CreateCompatibleContext();
	if (nullptr == current)
	{
		return false;
	}


	return false;
}

void
gl::device::resource::Bitmap::Mirror()
noexcept
{}

void
gl::device::resource::Bitmap::Flip()
noexcept
{}

void
gl::device::resource::Bitmap::Rotate(float angle)
noexcept
{}

void
gl::device::resource::Bitmap::RotateR(float angle)
noexcept
{}

void
gl::device::resource::Bitmap::RotateL(float angle)
noexcept
{}

bool
gl::device::resource::Bitmap::Destroy()
noexcept
{
	if (nullptr != GetHandle())
	{
		const bool result = 0 != Delegate(::DeleteObject);
		base::operator=(nullifier);

		return result;
	}

	return false;
}

bool
gl::device::resource::Bitmap::Draw(const IWindow& window_handle, const int& x, const int& y, const int& srcx, const int& srcy)
const noexcept
{
	GlobalDeviceContext render_context = GlobalDeviceContext();
	if (nullptr == render_context)
	{
		return false;
	}

	DeviceContext window_context = window_handle.AcquireContext();
	if (nullptr == window_context)
	{
		return false;
	}

	return Draw(render_context, window_context, x, y, srcx, srcy);
}

bool
gl::device::resource::Bitmap::Draw(const IContext& render_context, IContext& window_context, const int& x, const int& y, const int& srcx, const int& srcy)
const noexcept
{
	auto previous = window_context.Select(*this);

	const bool result = (0 == ::BitBlt(window_context
		, x, y, cachedWidth, cachedHeight
		, render_context
		, srcx, srcy, SRCCOPY));

	window_context.Select(previous);

	return result;
}

bool
gl::device::resource::Bitmap::GetPixel(const IContext& context, const int& x, const int& y, Colour& output)
const noexcept
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
gl::device::resource::Bitmap::GetWidth()
const noexcept
{
	return cachedWidth;
}

int
gl::device::resource::Bitmap::GetHeight()
const noexcept
{
	return cachedHeight;
}

gl::device::resource::Bitmap::Bitmap(const handle_type& handle)
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

gl::device::resource::Bitmap::Bitmap(handle_type&& handle)
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

gl::device::resource::Bitmap::~Bitmap()
noexcept
{
	if (shouldDestroy)
	{
		Destroy();
	}
}
