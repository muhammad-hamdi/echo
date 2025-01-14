#pragma once

#include <engine/core/util/Array.hpp>
#include "ShaderProgram.h"
#include "Texture.h"
#include "RenderState.h"
#include "ShaderProgram.h"

namespace Echo
{
	static const int MAX_TEXTURE_SAMPLER = 16;
	static const int SHADER_TEXTURE_SLOT0= 0;
	static const int SHADER_TEXTURE_SLOT1= 1;
	static const int SHADER_TEXTURE_SLOT2= 2;
	static const int SHADER_TEXTURE_SLOT3= 3;
	static const int SHADER_TEXTURE_SLOT4= 4;
	static const int SHADER_TEXTURE_SLOT5= 5;
	static const int SHADER_TEXTURE_SLOT6= 6;
	static const int SHADER_TEXTURE_SLOT7= 7;
	static const int SHADER_TEXTURE_SLOT8 = 8;
	static const int SHADER_TEXTURE_SLOT9 = 9;
	static const int SHADER_TEXTURE_SLOT10 = 10;
	static const int SHADER_TEXTURE_SLOT11 = 11;
	static const int SHADER_TEXTURE_SLOT12 = 12;
	static const int SHADER_TEXTURE_SLOT13 = 13;
	static const int SHADER_TEXTURE_SLOT14 = 14;
	static const int SHADER_TEXTURE_SLOT15 = 15;

	class Render;
	class Mesh;
	class Material;
	class Renderable
	{
		friend class Renderer;
		typedef array<Texture*, MAX_TEXTURE_SAMPLER> MaxTextureArray;
	public:
		// Param structure
		struct ShaderParam
		{
			String			name;
			ShaderParamType type;
			const void*		data;
			ui32			length;  // shader constance register num.
		};

	public:
		// identifier
		ui32 getIdentifier() const { return m_identifier; }

		// create method
		static Renderable* create(Mesh* mesh, Material* matInst, Render* node);

		// release
		void release();

		// set mesh
		Mesh* getMesh() { return m_mesh; }
		virtual void setMesh(Mesh* mesh)=0;

		// param operate
		virtual void setShaderParam(const String& name, ShaderParamType type, const void* param, size_t num=1);

		// texture
		void setTexture( ui32 stage, Texture* texture);
		Texture* getTexture(ui32 stage) const { return m_textures[stage]; }

		// submit to renderqueue
		void submitToRenderQueue();
		
		// render stage
		void setRenderStage(const String& renderStage) { m_renderStage = renderStage; }
		const String& getRenderStage(void){ return m_renderStage; }

		// blend state
		void setBlendState( BlendState* state );
		BlendState*	getBlendState() { return m_blendState; }

		// rasterizer state
		void setRasterizerState( RasterizerState* state );
		RasterizerState* getRasterizerState() { return m_rasterizerState; }

		// depth stencil state
		void setDepthStencilState(DepthStencilState* state);
		DepthStencilState* getDepthStencilState() { return m_depthStencilState; }

		// node(owner)
		void setNode( Render* node) { m_node = node; }
		Render* getNode() { return m_node; }

		// get shader
		ShaderProgram* getShader();

		// bind render state
		void bindRenderState();

	protected:
		// bind
		void bindTextures();

	protected:
		Renderable( const String& renderStage, ShaderProgram* shader, int identifier);
		virtual ~Renderable();

	public:
		ui32									m_identifier;
		Render*									m_node = nullptr;
		String									m_renderStage;
		ShaderProgramPtr						m_shaderProgram;
		map<String, ShaderParam>::type			m_shaderParams;
		Mesh*									m_mesh = nullptr;
		MaxTextureArray							m_textures;
		BlendState*								m_blendState = nullptr;
		RasterizerState*						m_rasterizerState = nullptr;
		DepthStencilState*						m_depthStencilState = nullptr;
        MultisampleState*                       m_multiSampleState = nullptr;
	};
	typedef ui32 RenderableID;
}
