#pragma once

#include "interface/mesh/Mesh.h"
#include "interface/ShaderProgram.h"
#include "mt_render_base.h"

namespace Echo
{
    class MTMapping
    {
    public:
        // Mapping Primitive Type
        static MTLPrimitiveType MapPrimitiveTopology(Mesh::TopologyType type);
        
        // Mapping vertex semantic string
        static String MapVertexSemanticString(VertexSemantic semantic);
        
        // Mapping MTLVertexFormat
        static MTLVertexFormat MapVertexFormat(PixelFormat pixelFormat);
        
        // Mapping Uniform type
        static ShaderParamType MapUniformType( MTLDataType uniformType);
    };
}
