#pragma once

#include "BufferLayout.hpp"

namespace Delta
{

class VertexBuffer
{
public:
    enum class Usage
    {
        STATIC,
        DYNAMIC,
        STREAM
    };

    VertexBuffer() = default;
    ~VertexBuffer() = default;
    VertexBuffer(VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&) = delete;

    template<typename T>
    bool init(const std::vector<T>& aVertices, const BufferLayout& aLayout, const Usage aUsage = Usage::STATIC)
    {
        if (mId != 0) return false;

        size_t size = aVertices.size() * sizeof(T);
        mVerticesCount = size / aLayout.getStride();

        initImpl(aVertices.data(), size, aLayout, aUsage);
        return true;
    }
    void clear();

    void bind() const;
    static void unbind();

    const BufferLayout& getLayout() const { return mLayout; }
    int getVerticesCount() const { return mVerticesCount; }

    static unsigned int getRendererCode(Usage aUsage);

private:
    void initImpl(const void* aData, const size_t aSize, const BufferLayout& aLayout, const Usage aUsage);

    unsigned int mId{ 0 };
    BufferLayout mLayout;

    int mVerticesCount{ 0 };

};

} // namespace Delta
