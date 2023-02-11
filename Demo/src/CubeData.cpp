#include "CubeData.hpp"

const std::vector<float> CubeData::mVertices = {
    // front side
   -1.0f,  -1.0f,  1.0f,   0.0f, 0.0f,
   -1.0f,   1.0f,  1.0f,   0.0f, 1.0f,
    1.0f,   1.0f,  1.0f,   1.0f, 1.0f,
    1.0f,  -1.0f,  1.0f,   1.0f, 0.0f,

     // left side
    -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,   1.0f, 0.0f,

     // back side
     1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
     1.0f,  1.0f, -1.0f,   0.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,   1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,   1.0f, 0.0f,

     // right side
     1.0f, -1.0f,  1.0f,   0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,   0.0f, 1.0f,
     1.0f,  1.0f, -1.0f,   1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,   1.0f, 0.0f,

     // up side
    -1.0f,  1.0f,  1.0f,   0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,
     1.0f,  1.0f, -1.0f,   1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,   1.0f, 0.0f,

     // down side
    -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,   0.0f, 1.0f,
     1.0f, -1.0f,  1.0f,   1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,   1.0f, 0.0f
};

const std::vector<unsigned int> CubeData::mIndices = {
    0,  2,  1,
    0,  3,  2,

    4,  6,  5,
    4,  7,  6,

    8,  10, 9,
    8,  11, 10,

    12, 14, 13,
    12, 15, 14,

    16, 18, 17,
    16, 19, 18,

    20, 22, 21,
    20, 23, 22
};

const Delta::BufferLayout CubeData::mLayout = {
    Delta::ShaderData::Type::FLOAT3,
    Delta::ShaderData::Type::FLOAT2
};
