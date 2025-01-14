#include "mt_mapping.h"
#include "engine/core/log/Log.h"

namespace Echo
{
    MTLPrimitiveType MTMapping::MapPrimitiveTopology(Mesh::TopologyType type)
    {
        switch(type)
        {
            case Mesh::TT_POINTLIST:        return MTLPrimitiveTypePoint;
            case Mesh::TT_LINELIST:         return MTLPrimitiveTypeLine;
            case Mesh::TT_LINESTRIP:        return MTLPrimitiveTypeLineStrip;
            case Mesh::TT_TRIANGLELIST:     return MTLPrimitiveTypeTriangle;
            case Mesh::TT_TRIANGLESTRIP:    return MTLPrimitiveTypeTriangleStrip;
            default:                        return MTLPrimitiveTypeTriangle;
        }
    }
    
    String MTMapping::MapVertexSemanticString(VertexSemantic semantic)
    {
        switch(semantic)
        {
            case VS_POSITION:            return "a_Position";
            case VS_BLENDINDICES:        return "a_Joint";
            case VS_BLENDWEIGHTS:        return "a_Weight";
            case VS_COLOR:               return "a_Color";
            case VS_NORMAL:              return "a_Normal";
            case VS_TEXCOORD0:           return "a_UV";
            case VS_TEXCOORD1:           return "a_UV1";
            case VS_TANGENT:             return "a_Tangent";
            case VS_BINORMAL:            return "a_Binormal";
            default:                     return "";
        }
    }
    
    MTLVertexFormat MTMapping::MapVertexFormat(PixelFormat pixelFormat)
    {
        switch (pixelFormat)
        {
            case PF_RG32_FLOAT:     return MTLVertexFormatFloat2;
            case PF_RGBA8_UNORM:    return MTLVertexFormatUChar4Normalized;
            case PF_RGBA8_SNORM:    return MTLVertexFormatChar4Normalized;
            case PF_RGB32_FLOAT:    return MTLVertexFormatFloat3;
            case PF_RGBA32_FLOAT:   return MTLVertexFormatFloat4;
            default:  EchoLogError("MapingVertexFormat failed");  return MTLVertexFormatInvalid;
        }
    }
    
    ShaderParamType MTMapping::MapUniformType(MTLDataType uniformType)
    {
        switch( uniformType)
        {
            case MTLDataTypeFloat:          return SPT_FLOAT;
            case MTLDataTypeFloat2:         return SPT_VEC2;
            case MTLDataTypeFloat3:         return SPT_VEC3;
            case MTLDataTypeFloat4:         return SPT_VEC4;
            case MTLDataTypeInt:            return SPT_INT;
            case MTLDataTypeFloat4x4:       return SPT_MAT4;
            case MTLDataTypeTexture:        return SPT_TEXTURE;
            case MTLDataTypeSampler:        return SPT_TEXTURE;
            default:                        return SPT_UNKNOWN;
        }
    }
}
