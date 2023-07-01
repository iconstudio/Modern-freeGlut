export module Glib.Window.Property.Factory;
import <type_traits>;
import Utility.FixedString;
import Glib.Device.ProcessInstance;
import Glib.Device.Brush;
import Glib.Device.Brush.Component;
import Glib.Device.Resource.Icon;
export import Glib.Window.Property;

export namespace gl::window
{
	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, const device::ColorBrush& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = DefaultWindowProperty.style,
				.lpfnWndProc = procedure,
				.cbClsExtra = 0,
				.cbWndExtra = 0,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = background.GetHandle(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, device::ColorBrush&& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = DefaultWindowProperty.style,
				.lpfnWndProc = procedure,
				.cbClsExtra = 0,
				.cbWndExtra = 0,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = std::move(background).GetHandle(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	template<device::ColoredComponent BkColorReference>
	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = DefaultWindowProperty.style,
				.lpfnWndProc = procedure,
				.cbClsExtra = 0,
				.cbWndExtra = 0,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = device::GetComponentColouring<BkColorReference>(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, const wchar_t* const& class_name
		, device::resource::Icon&& icon = nullptr
		, device::resource::Icon&& small_icon = nullptr
		, device::resource::Icon&& cursor = nullptr
		, const wchar_t* const& menu_name = nullptr
	) noexcept
	{
		return WindowProperty
		{
			RawWindowProperty
			{
				.cbSize = sizeof(RawWindowProperty),
				.style = DefaultWindowProperty.style,
				.lpfnWndProc = procedure,
				.cbClsExtra = 0,
				.cbWndExtra = 0,
				.hInstance = hinst.myHandle,
				.hIcon = std::move(icon).GetHandle(),
				.hCursor = std::move(cursor).GetHandle(),
				.hbrBackground = device::MakeDefaultComponentColouring(),
				.lpszMenuName = menu_name,
				.lpszClassName = class_name,
				.hIconSm = std::move(small_icon).GetHandle(),
			}
		};
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, const device::ColorBrush& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(hinst, procedure, ClassName.data(), std::move(icon), std::move(small_icon), std::move(cursor), background, menu_name);
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, device::ColorBrush&& background
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(hinst, procedure, ClassName.data(), std::move(icon), std::move(small_icon), std::move(cursor), std::move(background), menu_name);
	}

	template<util::fixed_wstring ClassName, device::ColoredComponent BkColorReference>
	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, device::resource::Icon&& icon
		, device::resource::Icon&& small_icon
		, device::resource::Icon&& cursor
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty<BkColorReference>(hinst, procedure, ClassName.data(), std::move(icon), std::move(small_icon), std::move(cursor), menu_name);
	}

	template<util::fixed_wstring ClassName>
	[[nodiscard]]
	WindowProperty CreateProperty(const device::ProcessInstance& hinst
		, WindowProcedure procedure
		, device::resource::Icon&& icon = nullptr
		, device::resource::Icon&& small_icon = nullptr
		, device::resource::Icon&& cursor = nullptr
		, const wchar_t* const& menu_name = nullptr
	) noexcept(ClassName.size() <= 256)
	{
		return CreateProperty(hinst, procedure, ClassName.data(), std::move(icon), std::move(small_icon), std::move(cursor), menu_name);
	}
}
