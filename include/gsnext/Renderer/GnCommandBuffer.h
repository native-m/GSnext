#pragma once

#include <cstdint>

class GnCommandBuffer
{
public:
    virtual ~GnCommandBuffer() { }

    virtual void Reset() = 0;
    virtual void Begin() = 0;
    virtual void BeginRenderPass() = 0;
    virtual void SetGraphicsPipeline() = 0;
    virtual void SetComputePipeline() = 0;
    virtual void SetBlendConstant() = 0;
    virtual void SetPushConstant() = 0;
    virtual void SetVertexBuffer() = 0;
    virtual void Draw() = 0;
    virtual void Dispatch() = 0;
    virtual void EndRenderPass() = 0;
    virtual void ResourceBarrier() = 0;
    virtual void End() = 0;

protected:
    GnCommandBuffer() { }
};
