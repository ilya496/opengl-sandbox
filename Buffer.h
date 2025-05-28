#pragma once

#include <string>
#include <vector>
#include <memory>

enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float: return 4;
	case ShaderDataType::Float2: return 4 * 2;
	case ShaderDataType::Float3: return 4 * 3;
	case ShaderDataType::Float4: return 4 * 4;
	case ShaderDataType::Mat3: return 4 * 3 * 3;
	case ShaderDataType::Mat4: return 4 * 4 * 4;
	case ShaderDataType::Int: return 4;
	case ShaderDataType::Int2: return 4 * 2;
	case ShaderDataType::Int3: return 4 * 3;
	case ShaderDataType::Int4: return 4 * 4;
	case ShaderDataType::Bool: return 1;
	}
	return 0;
}

static uint32_t ShaderDataTypeComponentCount(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:  return 1;
	case ShaderDataType::Float2: return 2;
	case ShaderDataType::Float3: return 3;
	case ShaderDataType::Float4: return 4;
	case ShaderDataType::Mat3:   return 3 * 3;
	case ShaderDataType::Mat4:   return 4 * 4;
	case ShaderDataType::Int:    return 1;
	case ShaderDataType::Int2:   return 2;
	case ShaderDataType::Int3:   return 3;
	case ShaderDataType::Int4:   return 4;
	case ShaderDataType::Bool:   return 1;
	}
	return 0;
}

struct BufferElement
{
	std::string Name;
	ShaderDataType Type;
	uint32_t Size;
	uint32_t Offset;

	BufferElement(ShaderDataType type, const std::string& name)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0) {}
};

class BufferLayout
{
public:
	BufferLayout(const std::initializer_list<BufferElement>& elements);

	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	inline uint32_t GetStride() const { return m_Stride; }

private:
	void CalculateOffsetAndStride();

private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};

class Buffer
{
public:
	virtual ~Buffer() {}

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
};

class VertexBuffer : public Buffer
{
public:
	VertexBuffer(float* vertices, uint32_t size);
	VertexBuffer(VertexBuffer&& other) noexcept;
	VertexBuffer& operator=(VertexBuffer&& other) noexcept;
	~VertexBuffer();

	void Bind() const override;
	void Unbind() const override;

	inline const BufferLayout& GetLayout() const { return m_Layout; }
	void SetLayout(const BufferLayout& layout);

	uint32_t GetRendererID() const { return m_RendererID; }

	static std::unique_ptr<VertexBuffer> Create(float* vertices, uint32_t size);

private:
	uint32_t m_RendererID;
	BufferLayout m_Layout;
};

class IndexBuffer : public Buffer
{
public:
	IndexBuffer(uint32_t* indices, uint32_t count);
	IndexBuffer(IndexBuffer&& other) noexcept;
	IndexBuffer& operator=(IndexBuffer&& other) noexcept;
	~IndexBuffer();

	void Bind() const override;
	void Unbind() const override;

	uint32_t GetCount() const { return m_Count; }
	uint32_t GetRendererID() const { return m_RendererID; }

	static std::unique_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);

private:
	uint32_t m_RendererID;
	uint32_t m_Count;
};