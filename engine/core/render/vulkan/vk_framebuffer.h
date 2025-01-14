#pragma once

#include "interface/FrameBuffer.h"
#include "vk_render_base.h"

namespace Echo
{
    class VKFramebuffer : public FrameBuffer
    {
    public:
        VKFramebuffer(ui32 id, ui32 width, ui32 height);
        virtual ~VKFramebuffer();

        // current frame buffer
        static VKFramebuffer* current();

        // attach render view
        virtual void attach(Attachment attachment, RenderView* renderView) override;

        // begin render
        virtual bool begin(bool isClearColor, const Color& bgColor, bool isClearDepth, float depthValue, bool isClearStencil, ui8 stencilValue) override;
        virtual bool end() override;

        // on resize
        virtual void onSize(ui32 width, ui32 height);

    public:
        // get vk viewPort
        VkViewport getVkViewport() { return m_vkViewport; }

        // get vk render pass
        VkRenderPass getVkRenderPass() { return m_vkRenderPass; }

        // get vk view port create info
        VkPipelineViewportStateCreateInfo* getVkViewportStateCreateInfo() { return &m_vkViewportStateCreateInfo; }

        // get vk command buffer
        virtual VkCommandBuffer getVkCommandbuffer() { return nullptr; }

        // get vk frame buffer
        virtual VkFramebuffer getVkFramebuffer() { return nullptr; }

        // get vk descriptor pool
        VkDescriptorPool getVkDescriptorPool() { return m_vkDescriptorPool; }

    protected:
        // clear color image
        virtual VkImage getVkColorImage() { return nullptr; }

    protected:
        // create render pass
        void createVkRenderPass();

        // create vk descriptor pool
        void createVkDescriptorPool();

    protected:
        VkRenderPass                        m_vkRenderPass = nullptr;
        VkRenderPassBeginInfo               m_vkRenderPassBeginInfo;
        vector<VkFramebuffer>::type         m_vkFramebuffers;
        VkViewport                          m_vkViewport;
        VkPipelineViewportStateCreateInfo   m_vkViewportStateCreateInfo;
        VkDescriptorPool                    m_vkDescriptorPool = nullptr;
    };

    class VKFramebufferOffscreen : public VKFramebuffer
    {
    public:
        VKFramebufferOffscreen(ui32 id, ui32 width, ui32 height);
        virtual ~VKFramebufferOffscreen();

        // begin render
        virtual bool begin(bool clearColor, const Color& backgroundColor, bool clearDepth, float depthValue, bool clearStencil, ui8 stencilValue) override;
        virtual bool end() override;

        // on resize
        virtual void onSize(ui32 width, ui32 height);

    protected:
        // create vk frame buffer
        void createVkFramebuffers();
    };

    class VKFramebufferWindow : public VKFramebuffer
    {
    public:
        VKFramebufferWindow(ui32 width, ui32 height, void* handle);
        virtual ~VKFramebufferWindow();

        // begin render
        virtual bool begin(bool clearColor, const Color& backgroundColor, bool clearDepth, float depthValue, bool clearStencil, ui8 stencilValue) override;
        virtual bool end() override;

        // on resize
        virtual void onSize(ui32 width, ui32 height);

    public:
        // get vk command buffer
        virtual VkCommandBuffer getVkCommandbuffer() { return m_vkCommandBuffers[m_imageIndex]; }

        // get vk frame buffer
        virtual VkFramebuffer getVkFramebuffer() { return m_vkFramebuffers[m_imageIndex]; }

    private:
        // recreate swap chain
        void recreateVkSwapChain();
        void destroyVkSwapChain(VkSwapchainKHR vkSwapChain);

        // create vk frame buffer
        void createVkFramebuffers();
        void destroyVkFramebuffers();

        // vk command buffer
        void createVkCommandBuffers();
        void destroyVkCommandBuffers();

        // create semaphores
        void createVkSemaphores();

        // create fences
        void createVkFences();
        void destroyVkFences();

        // create swap chain
        void createSwapChain(VkDevice vkDevice);

        // create image views
        void createVkImageViews(VkDevice vkDevice);
        void destroyVkImageViews();

        // check surface format
        VkSurfaceFormatKHR pickSurfaceSupportFormat();

        // create window surface
        void createVkSurface(void* handle);

        // clear color image
        virtual VkImage getVkColorImage() { return m_vkSwapChainImages[m_imageIndex]; }

        // submit command buffer
        void submitCommandBuffer();

        // present
        void present();

    protected:
        ui32                            m_imageIndex = 0;
        vector<VkFence>::type           m_waitFences;
        VkSemaphore                     m_vkImageAvailableSemaphore;
        VkSemaphore                     m_vkRenderFinishedSemaphore;
        VkSurfaceKHR                    m_vkWindowSurface;
        VkSwapchainKHR				    m_vkSwapChain = VK_NULL_HANDLE;
        vector<VkImage>::type           m_vkSwapChainImages;
        vector<VkImageView>::type	    m_vkSwapChainImageViews;
        vector<VkCommandBuffer>::type   m_vkCommandBuffers;
        VkQueue                         m_vkPresentQueue;
    };
}
