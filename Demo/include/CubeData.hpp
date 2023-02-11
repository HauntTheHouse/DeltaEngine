#pragma once

#include <EngineCore/Rendering/OpenGL/BufferLayout.hpp>

class CubeData
{
public:
    static const std::vector<float>& getVertices() { return mVertices; }
    static const std::vector<unsigned int>& getIndices() { return mIndices; }
    static const Delta::BufferLayout& getLayout() { return mLayout; }

private:
    static const std::vector<float> mVertices;
    static const std::vector<unsigned int> mIndices;
    static const Delta::BufferLayout mLayout;

};
