#pragma once

#include "EngineCore/Rendering/GfxEnums.hpp"
#include "EngineCore/Utils.hpp"

namespace Delta
{

class IndexBuffer
{
public:
    IndexBuffer() = default;
    ~IndexBuffer() = default;
    IndexBuffer(IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&) = delete;

    template<typename Container>
    bool Init(Container&& indices, const IndexBufferType dataType = IndexBufferType::UNSIGNED_INT, const BufferUsage usage = BufferUsage::STATIC)
    {
        return Init(indices.data(), Utils::getSizeInBytes(indices), dataType, usage);
    }
    bool Init(const void* data, const size_t size, const IndexBufferType dataType = IndexBufferType::UNSIGNED_INT, const BufferUsage usage = BufferUsage::STATIC);
    void Clear();

    void Bind() const;
    static void Unbind();

    size_t GetIndicesCount() const { return m_IndicesCount; }
    IndexBufferType GetDataType() const { return m_DataType; }

private:
    unsigned int m_Id{ 0 };
    size_t m_IndicesCount{ 0 };
    IndexBufferType m_DataType;

};

} // namespace Delta
