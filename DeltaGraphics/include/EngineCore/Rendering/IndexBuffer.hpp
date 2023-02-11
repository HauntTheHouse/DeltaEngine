#pragma once

#include "VertexBuffer.hpp"

namespace Delta
{

class IndexBuffer
{
public:
    IndexBuffer() = default;
    ~IndexBuffer() = default;
    IndexBuffer(IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&) = delete;

    template<typename T>
    bool init(const std::vector<T>& aIndices, const VertexBuffer::Usage aUsage = VertexBuffer::Usage::STATIC)
    {
        if (mId != 0) return false;

        mIndicesCount = aIndices.size();

        initImpl(aIndices.data(), mIndicesCount * sizeof(T), aUsage);
        return true;
    }
    void clear();

    void bind() const;
    static void unbind();

    int getIndicesCount() const { return mIndicesCount; }

private:
    void initImpl(const void* aData, const size_t aSize, const VertexBuffer::Usage aUsage);

    unsigned int mId{ 0 };
    int mIndicesCount{ 0 };

};

} // namespace Delta
