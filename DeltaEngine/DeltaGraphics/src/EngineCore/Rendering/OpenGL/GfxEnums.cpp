#include "EngineCore/Rendering/GfxEnums.hpp"

#include <glad/glad.h>

namespace Delta
{

unsigned int toNativeType(DrawPrimitive drawPrimitive)
{
    switch (drawPrimitive)
    {
    case DrawPrimitive::POINTS: return GL_POINTS;
    case DrawPrimitive::LINES: return GL_LINES;
    case DrawPrimitive::LINE_LOOP: return GL_LINE_LOOP;
    case DrawPrimitive::LINE_STRIP: return GL_LINE_STRIP;
    case DrawPrimitive::TRIANGLES: return GL_TRIANGLES;
    case DrawPrimitive::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
    case DrawPrimitive::TRIANGLE_FAN: return GL_TRIANGLE_FAN;
    case DrawPrimitive::QUADS: return GL_QUADS;
    case DrawPrimitive::LINES_ADJACENCY: return GL_LINES_ADJACENCY;
    case DrawPrimitive::LINE_STRIP_ADJACENCY: return GL_LINE_STRIP_ADJACENCY;
    case DrawPrimitive::TRIANGLES_ADJACENCY: return GL_TRIANGLES_ADJACENCY;
    case DrawPrimitive::TRIANGLE_STRIP_ADJACENCY: return GL_TRIANGLE_STRIP_ADJACENCY;
    case DrawPrimitive::PATCHES: return GL_PATCHES;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(Func func)
{
    switch (func)
    {
    case Func::NEVER: return GL_NEVER;
    case Func::LESS: return GL_LESS;
    case Func::EQUAL: return GL_EQUAL;
    case Func::LEQUAL: return GL_LEQUAL;
    case Func::GREATER: return GL_GREATER;
    case Func::NOTEQUAL: return GL_NOTEQUAL;
    case Func::GEQUAL: return GL_GEQUAL;
    case Func::ALWAYS: return GL_ALWAYS;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(Face face)
{
    switch (face)
    {
    case Face::NONE: return GL_NONE;
    case Face::FRONT: return GL_FRONT;
    case Face::BACK: return GL_BACK;
    case Face::FRONT_AND_BACK: return GL_FRONT_AND_BACK;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(FrontFace frontFace)
{
    switch (frontFace)
    {
    case FrontFace::CW: return GL_CW;
    case FrontFace::CCW: return GL_CCW;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(StencilOp stencilOp)
{
    switch (stencilOp)
    {
    case StencilOp::KEEP: return GL_KEEP;
    case StencilOp::ZERO: return GL_ZERO;
    case StencilOp::REPLACE: return GL_REPLACE;
    case StencilOp::INCR: return GL_INCR;
    case StencilOp::DECR: return GL_DECR;
    case StencilOp::INVERT: return GL_INVERT;
    case StencilOp::INCR_WRAP: return GL_INCR_WRAP;
    case StencilOp::DECR_WRAP: return GL_DECR_WRAP;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(LogicOp logicOp)
{
    switch (logicOp)
    {
    case LogicOp::CLEAR: return GL_CLEAR;
    case LogicOp::AND: return GL_AND;
    case LogicOp::AND_REVERSE: return GL_AND_REVERSE;
    case LogicOp::COPY: return GL_COPY;
    case LogicOp::AND_INVERTED: return GL_AND_INVERTED;
    case LogicOp::NOOP: return GL_NOOP;
    case LogicOp::XOR: return GL_XOR;
    case LogicOp::OR: return GL_OR;
    case LogicOp::NOR: return GL_NOR;
    case LogicOp::EQUIV: return GL_EQUIV;
    case LogicOp::INVERT: return GL_INVERT;
    case LogicOp::OR_REVERSE: return GL_OR_REVERSE;
    case LogicOp::COPY_INVERTED: return GL_COPY_INVERTED;
    case LogicOp::OR_INVERTED: return GL_OR_INVERTED;
    case LogicOp::NAND: return GL_NAND;
    case LogicOp::SET: return GL_SET;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(BlendEquation blendEquation)
{
    switch (blendEquation)
    {
    case BlendEquation::ADD: return GL_FUNC_ADD;
    case BlendEquation::SUB: return GL_FUNC_SUBTRACT;
    case BlendEquation::REVERSE_SUB: return GL_FUNC_REVERSE_SUBTRACT;
    case BlendEquation::MIN: return GL_MIN;
    case BlendEquation::MAX: return GL_MAX;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(BlendFunc blendFunc)
{
    switch (blendFunc)
    {
    case BlendFunc::ZERO: return GL_ZERO;
    case BlendFunc::ONE: return GL_ONE;
    case BlendFunc::SRC_COLOR: return GL_SRC_COLOR;
    case BlendFunc::ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
    case BlendFunc::SRC_ALPHA: return GL_SRC_ALPHA;
    case BlendFunc::ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
    case BlendFunc::DST_ALPHA: return GL_DST_ALPHA;
    case BlendFunc::ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
    case BlendFunc::DST_COLOR: return GL_DST_COLOR;
    case BlendFunc::ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
    case BlendFunc::SRC_ALPHA_SATURATE: return GL_SRC_ALPHA_SATURATE;
    case BlendFunc::SRC1_COLOR: return GL_SRC1_COLOR;
    case BlendFunc::ONE_MINUS_SRC1_COLOR: return GL_ONE_MINUS_SRC1_COLOR;
    case BlendFunc::SRC1_ALPHA: return GL_SRC1_ALPHA;
    case BlendFunc::ONE_MINUS_SRC1_ALPHA: return GL_ONE_MINUS_SRC1_ALPHA;
    case BlendFunc::CONSTANT_COLOR: return GL_CONSTANT_COLOR;
    case BlendFunc::ONE_MINUS_CONSTANT_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
    case BlendFunc::CONSTANT_ALPHA: return GL_CONSTANT_ALPHA;
    case BlendFunc::ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(PolygonMode polygonMode)
{
    switch (polygonMode)
    {
    case PolygonMode::POINT: return GL_POINT;
    case PolygonMode::LINE: return GL_LINE;
    case PolygonMode::FILL: return GL_FILL;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(MagFilter magFilter)
{
    switch (magFilter)
    {
    case MagFilter::NEAREST:                return GL_NEAREST;
    case MagFilter::LINEAR:                 return GL_LINEAR;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(MinFilter minFilter)
{
    switch (minFilter)
    {
    case MinFilter::NEAREST:                return GL_NEAREST;
    case MinFilter::LINEAR:                 return GL_LINEAR;
    case MinFilter::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
    case MinFilter::LINEAR_MIPMAP_NEAREST:  return GL_LINEAR_MIPMAP_NEAREST;
    case MinFilter::NEAREST_MIPMAP_LINEAR:  return GL_NEAREST_MIPMAP_LINEAR;
    case MinFilter::LINEAR_MIPMAP_LINEAR:   return GL_LINEAR_MIPMAP_LINEAR;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(WrapMode wrapMode)
{
    switch (wrapMode)
    {
    case WrapMode::REPEAT:               return GL_REPEAT;
    case WrapMode::CLAMP_TO_EDGE:        return GL_CLAMP_TO_EDGE;
    case WrapMode::CLAMP_TO_BORDER:      return GL_CLAMP_TO_BORDER;
    case WrapMode::MIRRORED_REPEAT:      return GL_MIRRORED_REPEAT;
    case WrapMode::MIRROR_CLAMP_TO_EDGE: return GL_MIRROR_CLAMP_TO_EDGE;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(Format format)
{
    switch (format)
    {
    case Format::RED: return GL_RED;
    case Format::RG: return GL_RG;
    case Format::RGB: return GL_RGB;
    case Format::RGBA: return GL_RGBA;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(IndexBufferType indexBufferType)
{
    switch (indexBufferType)
    {
    case Delta::IndexBufferType::UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
    case Delta::IndexBufferType::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
    case Delta::IndexBufferType::UNSIGNED_INT: return GL_UNSIGNED_INT;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(BufferUsage bufferUsage)
{
    switch (bufferUsage)
    {
    case BufferUsage::STATIC: return GL_STATIC_DRAW;
    case BufferUsage::DYNAMIC: return GL_DYNAMIC_DRAW;
    case BufferUsage::STREAM: return GL_STREAM_DRAW;
    default: return GL_NONE;
    }
}

unsigned int toNativeType(ShaderType shaderType)
{
    switch (shaderType)
    {
    case ShaderType::VERTEX: return GL_VERTEX_SHADER;
    case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
    case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
    case ShaderType::TESS_EVALUATION: return GL_TESS_EVALUATION_SHADER;
    case ShaderType::TESS_CONTROL: return GL_TESS_CONTROL_SHADER;
    case ShaderType::COMPUTE: return GL_COMPUTE_SHADER;
    default: return GL_NONE;
    }
}

} // namespace Delta
