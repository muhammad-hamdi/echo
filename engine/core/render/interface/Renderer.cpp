#include "Renderer.h"
#include "FrameBuffer.h"
#include "engine/core/log/Log.h"
#include "Viewport.h"
#include "image/PixelFormat.h"
#include "Renderable.h"
#include "../metal/mt.h"
#include "../gles/GLES.h"

namespace Echo
{
	Color Renderer::BGCOLOR = Echo::Color(0.298f, 0.298f, 0.322f);	// render target clear color
	static Renderer* g_render = NULL;								// global renderer

	Renderer* Renderer::instance()
	{
		EchoAssert(g_render);
		return g_render;
	}

	bool Renderer::replaceInstance(Renderer* inst)
	{
		EchoAssert(!g_render);
		g_render = inst;

		return true;
	}

	Renderer::Renderer()
		: m_rasterizerState(NULL)
		, m_depthStencilState(NULL)
		, m_blendState(NULL)
	{
		EchoAssert(!g_render);
		g_render = this;
	}

	Renderer::~Renderer()
	{
		for (std::map<ui32, Renderable*>::iterator it = m_renderables.begin(); it != m_renderables.end(); ++it)
		{
			EchoSafeDelete(it->second, Renderable);
		}
		m_renderables.clear();
	}

	void Renderer::setRasterizerState(RasterizerState* state)
	{
		EchoAssert(state);
		if (state != m_rasterizerState)
		{
			state->active();
			m_rasterizerState = state;
		}
	}

	void Renderer::setDepthStencilState(DepthStencilState* state)
	{
		if (state && state != m_depthStencilState)
		{
			state->active();
			m_depthStencilState = state;
		}
	}

	void Renderer::setBlendState(BlendState* state)
	{
		if (state != m_blendState)
		{
			state->active();
			m_blendState = state;
		}
	}

	bool Renderer::isFullscreen() const
	{
		return m_cfg.m_isFullscreen;
	}

	RasterizerState* Renderer::getRasterizerState() const
	{
		return m_rasterizerState;
	}

	DepthStencilState* Renderer::getDepthStencilState() const
	{
		return m_depthStencilState;
	}

	BlendState* Renderer::getBlendState() const
	{
		return m_blendState;
	}

	void Renderer::project(Vector3& screenPos, const Vector3& worldPos, const Matrix4& matVP, Viewport* pViewport)
	{
		Viewport viewPort(0, 0, getWindowWidth(), getWindowHeight());
		if (!pViewport)
		{
			pViewport = &viewPort;
		}

		Vector4 vSSPos = Vector4(worldPos, 1.0);
		vSSPos = matVP.transform(vSSPos);

		Real invW = 1.0f / vSSPos.w;
		vSSPos.x *= invW;
		vSSPos.y *= invW;
		vSSPos.z *= invW;

		screenPos.x = (Real)pViewport->getLeft() + (1.0f + vSSPos.x) * (Real)pViewport->getWidth() * 0.5f;
		screenPos.y = (Real)pViewport->getTop() + (1.0f - vSSPos.y) * (Real)pViewport->getHeight() * 0.5f;
		screenPos.z = (1.0f + vSSPos.z) * 0.5f;
	}

	void Renderer::unproject(Vector3& worldPos, const Vector3& screenPos, const Matrix4& matVP, Viewport* pViewport)
	{
		Viewport viewPort(0, 0, getWindowWidth(), getWindowHeight());
		if (!pViewport)
		{
			pViewport = &viewPort;
		}

		Matrix4 matVPInv = matVP;
		matVPInv.detInverse();

		Vector4 vWSPos = Vector4(screenPos, 1.0f);
		vWSPos.x = (screenPos.x - pViewport->getLeft()) / (Real)pViewport->getWidth() * 2.0f - 1.0f;
		vWSPos.y = 1 - (screenPos.y - pViewport->getTop()) / (Real)pViewport->getHeight() * 2.0f;

		Vector4 vWorld = vWSPos * matVPInv;
		vWorld /= vWorld.w;

		worldPos = (Vector3)vWorld;
	}

	Renderable* Renderer::getRenderable(RenderableID id)
	{
		std::map<ui32, Renderable*>::iterator it = m_renderables.find(id);
		if (it != m_renderables.end())
			return it->second;

		return nullptr;
	}

	void Renderer::destroyRenderables(Renderable** renderables, int num)
	{
		for (int i = 0; i < num; i++)
		{
			Renderable* renderable = renderables[i];
			if (renderable)
			{
				std::map<ui32, Renderable*>::iterator it = m_renderables.find(renderable->getIdentifier());
				if(it != m_renderables.end())
                {
                    m_renderables.erase(it);
                    
                    EchoSafeDelete(renderable, Renderable);
                    renderables[i] = nullptr;
                }
			}
		}
	}

	void Renderer::destroyRenderables(vector<Renderable*>::type& renderables)
	{
		destroyRenderables(renderables.data(), static_cast<int>(renderables.size()));
		renderables.clear();
	}
}
