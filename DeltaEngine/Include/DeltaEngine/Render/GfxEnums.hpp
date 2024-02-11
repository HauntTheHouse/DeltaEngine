#pragma once

namespace Delta
{

enum class DrawPrimitive
{
    POINTS,
    LINES,
    LINE_LOOP,
    LINE_STRIP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    QUADS,
    QUAD_STRIP,
    POLYGON,
    LINES_ADJACENCY,
    LINE_STRIP_ADJACENCY,
    TRIANGLES_ADJACENCY,
    TRIANGLE_STRIP_ADJACENCY,
    PATCHES,

    MAX_NUM
};
unsigned int toNativeType(DrawPrimitive drawPrimitive);

enum class Func
{
    NEVER,
    LESS,
    EQUAL,
    LEQUAL,
    GREATER,
    NOTEQUAL,
    GEQUAL,
    ALWAYS,

    MAX_NUM
};
unsigned int toNativeType(Func func);

enum class Face
{
    NONE,
    FRONT,
    BACK,
    FRONT_AND_BACK,

    MAX_NUM
};
unsigned int toNativeType(Face face);

enum class FrontFace
{
    CW,
    CCW,

    MAX_NUM
};
unsigned int toNativeType(FrontFace frontFace);

enum class StencilOp
{
    KEEP,
    ZERO,
    REPLACE,
    INCR,
    DECR,
    INVERT,
    INCR_WRAP,
    DECR_WRAP,

    MAX_NUM
};
unsigned int toNativeType(StencilOp stencilOp);

enum class LogicOp
{
    CLEAR,
    AND,
    AND_REVERSE,
    COPY,
    AND_INVERTED,
    NOOP,
    XOR,
    OR,
    NOR,
    EQUIV,
    INVERT,
    OR_REVERSE,
    COPY_INVERTED,
    OR_INVERTED,
    NAND,
    SET,

    MAX_NUM
};
unsigned int toNativeType(LogicOp logicOp);

enum class BlendEquation
{
    ADD,
    SUB,
    REVERSE_SUB,
    MIN,
    MAX,

    MAX_NUM
};
unsigned int toNativeType(BlendEquation blendEquation);

enum class BlendFunc
{
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    SRC_ALPHA_SATURATE,
    SRC1_COLOR,
    ONE_MINUS_SRC1_COLOR,
    SRC1_ALPHA,
    ONE_MINUS_SRC1_ALPHA,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA,

    MAX_NUM
};
unsigned int toNativeType(BlendFunc blendFunc);

enum class PolygonMode
{
    POINT,
    LINE,
    FILL,

    MAX_NUM
};
unsigned int toNativeType(PolygonMode polygonMode);

enum class MagFilter
{
    NEAREST,
    LINEAR,

    MAX_NUM
};
unsigned int toNativeType(MagFilter magFilter);

enum class MinFilter
{
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR,

    MAX_NUM
};
unsigned int toNativeType(MinFilter minFilter);

enum class WrapMode
{
    REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
    MIRRORED_REPEAT,
    MIRROR_CLAMP_TO_EDGE,

    MAX_NUM
};
unsigned int toNativeType(WrapMode wrapMode);

enum class Format
{
    RED, RG, RGB, RGBA,

    MAX_NUM
};
unsigned int toNativeType(Format format);

enum class IndexBufferType
{
    UNSIGNED_BYTE,
    UNSIGNED_SHORT,
    UNSIGNED_INT,

    MAX_NUM
};
unsigned int toNativeType(IndexBufferType intexBufferType);

enum class BufferUsage
{
    STATIC,
    DYNAMIC,
    STREAM,

    MAX_NUM
};
unsigned int toNativeType(BufferUsage bufferUsage);

enum class ShaderType
{
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    TESS_EVALUATION,
    TESS_CONTROL,
    COMPUTE,

    MAX_NUM
};
unsigned int toNativeType(ShaderType shaderType);

} // namespace Delta
