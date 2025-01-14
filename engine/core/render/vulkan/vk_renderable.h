#pragma once

#include "engine/core/render/interface/Renderable.h"
#include "vk_render_base.h"
#include "vk_shader_program.h"

namespace Echo
{
	class VKRenderable : public Renderable
	{
	public:
		VKRenderable(const String& renderStage, ShaderProgram* shader, int identifier);
        virtual ~VKRenderable() {}

        // bind shader uniforms
        void bindShaderParams();
        void bindGeometry();

    public:
        // get vk pipeline
        VkPipeline getVkPipeline() { return m_vkPipeline; }

    private:
        // link shader and program
        virtual void setMesh(Mesh* mesh) override;

	private:
		// create vk pipeline
		void createVkPipeline();

        // build vertex input attribute
        void buildVkVertexInputAttributeDescriptions(VKShaderProgram* vkShaderProgram, const VertexElementList& vertElements, vector<VkVertexInputAttributeDescription>::type& viAttributeDescriptions);

        // get vertex attribute by semantic
        bool getVkVertexAttributeBySemantic(VertexSemantic semantic, spirv_cross::Resource& oResource);

        // get blend state create info
        const VkPipelineColorBlendStateCreateInfo* getVkColorBlendStateCreateInfo();

        // get rasterization state create info
        const VkPipelineRasterizationStateCreateInfo* getVkRasterizationStateCreateInfo();

        // get depth stencil state create info
        const VkPipelineDepthStencilStateCreateInfo* getVkDepthStencilStateCrateInfo();

        // get multisample state create creteinfo
        const VkPipelineMultisampleStateCreateInfo* getVkMultiSampleStateCreateInfo();

	private:
		VkPipeline          m_vkPipeline = nullptr;
	};
}
