#pragma once

#include "engine/core/render/interface/ShaderProgram.h"
#include "mt_render_base.h"

namespace Echo
{
    /**
     * https://developer.apple.com/library/archive/documentation/Miscellaneous/Conceptual/MetalProgrammingGuide/Prog-Func/Prog-Func.html
     */
	class MTShaderProgram : public ShaderProgram
	{
    public:
        // is valid
        bool isValid() { return m_isValid; }

        // get mtl function
        id<MTLFunction> getMetalVertexFunction() { return m_metalVertexShader; }
        id<MTLFunction> getMetalFragmentFunction() { return m_metalFragmentShader; }

        // bind
        virtual void bindUniforms() override;

    public:
        // parse uniforms
        void parseUniforms(MTLRenderPipelineReflection* reflection);

    private:
        // create shader library
        virtual bool createShaderProgram(const String& vsContent, const String& psContent) override;

        // add uniform
        void addUniform(MTLArgument* arg, ShaderType shaderType);

        // alloc uniform bytes
        void allocUniformBytes();

    private:
        bool                m_isValid = false;
        id<MTLLibrary>      m_metalVertexLibrary = nullptr;
        id<MTLLibrary>      m_metalFragmentLibrary = nullptr;
        id<MTLFunction>     m_metalVertexShader = nullptr;
        id<MTLFunction>     m_metalFragmentShader = nullptr;
        vector<Byte>::type  m_vertexShaderUniformBytes;
        vector<Byte>::type  m_fragmentShaderUniformBytes;
	};
}
