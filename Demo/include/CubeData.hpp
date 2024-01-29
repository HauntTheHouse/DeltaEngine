#pragma once

#include <vector>
#include <EngineCore/Rendering/BufferLayout.hpp>

class CubeData
{
public:
    static const std::vector<float>& GetVertices() { return m_Vertices; }
    static const std::vector<unsigned int>& GetIndices() { return m_Indices; }
    static const Delta::BufferLayout& GetLayout() { return m_Layout; }

private:
    static const std::vector<float> m_Vertices;
    static const std::vector<unsigned int> m_Indices;
    static const Delta::BufferLayout m_Layout;

};
