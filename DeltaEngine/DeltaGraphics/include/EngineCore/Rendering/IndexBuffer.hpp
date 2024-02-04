#pragma once

#include "VertexBuffer.hpp"
#include "EngineCore/Utils.hpp"

namespace Delta
{

class IndexBuffer
{
public:
    enum class DataType
    {
        BYTE,  UNSIGNED_BYTE,
        SHORT, UNSIGNED_SHORT,
        INT,   UNSIGNED_INT,
    };

    IndexBuffer() = default;
    ~IndexBuffer() = default;
    IndexBuffer(IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&) = delete;

    template<typename Container>
    bool Init(Container&& indices, const DataType dataType = DataType::UNSIGNED_INT, const VertexBuffer::Usage usage = VertexBuffer::Usage::STATIC)
    {
        return Init(indices.data(), Utils::getSizeInBytes(indices), dataType, usage);
    }
    bool Init(const void* data, const size_t size, const DataType dataType = DataType::UNSIGNED_INT, const VertexBuffer::Usage usage = VertexBuffer::Usage::STATIC);
    void Clear();

    void Bind() const;
    static void Unbind();

    size_t GetIndicesCount() const { return m_IndicesCount; }
    DataType GetDataType() const { return m_DataType; }

private:
    unsigned int m_Id{ 0 };
    size_t m_IndicesCount{ 0 };
    DataType m_DataType;

};

} // namespace Delta
