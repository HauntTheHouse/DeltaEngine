#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Delta
{

class VertexArray
{
public:
    VertexArray() = default;
    ~VertexArray() = default;
    VertexArray(VertexArray&) = delete;
    VertexArray& operator=(VertexArray&) = delete;

    bool init();
    void clear();

    void addVertexBuffer(const VertexBuffer& aVertexBuffer);
    void setIndexBuffer(const IndexBuffer& aIndexBuffer);

    void bind() const;
    static void unbind();

    unsigned int getVerticesCount() const { return mVerticesCount; }
    int getIndicesCount() const { return mIndicesCount; }

private:
    unsigned int mId{ 0 };

    unsigned int mAttributesCount{ 0 };
    int mVerticesCount{ 0 };
    int mIndicesCount{ 0 };

};

} // namespace Delta
