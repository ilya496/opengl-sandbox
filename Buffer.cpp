#include "Buffer.h"

#include "opengl.h"

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
	: m_Elements(elements)
{
	CalculateOffsetAndStride();
}

void BufferLayout::CalculateOffsetAndStride()
{
	uint32_t offset = 0;
	m_Stride = 0;
	for (size_t i = 0; i < m_Elements.size(); ++i) {
		m_Elements[i].Offset = offset;
		offset += m_Elements[i].Size;
		m_Stride += m_Elements[i].Size;
	}
}

VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
	: m_RendererID(0), m_Layout({})
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	: m_RendererID(other.m_RendererID), m_Layout(other.m_Layout)
{
	other.m_RendererID = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	if (this != &other)
	{
		glDeleteBuffers(1, &m_RendererID);
		m_RendererID = other.m_RendererID;
		m_Layout = other.m_Layout;
		other.m_RendererID = 0;
	}

	return *this;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetLayout(const BufferLayout& layout)
{
	m_Layout = layout;
	uint32_t index = 0;

	for (const auto& element : m_Layout.GetElements()) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			ShaderDataTypeComponentCount(element.Type),
			GL_FLOAT,
			GL_FALSE,
			m_Layout.GetStride(),
			(void*)(uintptr_t)element.Offset
		);
		index++;
	}
}

std::unique_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
	return std::make_unique<VertexBuffer>(vertices, size);
}

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
	: m_RendererID(0), m_Count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	: m_RendererID(other.m_RendererID), m_Count(other.m_Count)
{
	other.m_RendererID = 0;
	other.m_Count = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
	if (this != &other)
	{
		glDeleteBuffers(1, &m_RendererID);
		m_RendererID = other.m_RendererID;
		m_Count = other.m_Count;
		other.m_RendererID = 0;
		other.m_Count = 0;
	}
	return *this;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::unique_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	return std::make_unique<IndexBuffer>(indices, count);
}