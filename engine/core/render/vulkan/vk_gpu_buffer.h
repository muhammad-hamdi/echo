#pragma once

#include <engine/core/render/interface/GPUBuffer.h>
#include "vk_render_base.h"

namespace Echo
{
    class VKBuffer : public GPUBuffer
    {
    public:
        VKBuffer(GPUBufferType type, Dword usage, const Buffer& buff);
        ~VKBuffer();

        bool updateData(const Buffer& buff);
        void bindBuffer();

        // get vk buffer
        VkBuffer getVkBuffer() { return m_vkBuffer; }

    private:
        // create
        bool create(ui32 sizeInBytes);

        // clear
        void clear();

    private:
        VkBuffer        m_vkBuffer = nullptr;
        VkDeviceMemory  m_vkBufferMemory = nullptr;
    };
}
