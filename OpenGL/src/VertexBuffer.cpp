module;
module Glib;
import <type_traits>;
import :VertexBuffer;

void
gl::VertexBuffer::Create(std::initializer_list<std::int32_t> list, buffer::BufferUsage usage)
noexcept
{
	base::Create(buffer::BufferType::Array, list.begin(), list.size(), usage);
}

void
gl::VertexBuffer::Create(std::initializer_list<std::uint32_t> list, buffer::BufferUsage usage)
noexcept
{
	base::Create(buffer::BufferType::Array, list.begin(), list.size(), usage);
}

void
gl::VertexBuffer::Create(std::initializer_list<float> list, buffer::BufferUsage usage)
noexcept
{
	base::Create(buffer::BufferType::Array, list.begin(), list.size(), usage);
}
