/* Vulkan renderer */
#pragma once

#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
/* Vulkan also before GLFW */
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <VkBootstrap.h>
#include <vk_mem_alloc.h>

#include "Timer.h"
#include "Renderpass.h"
#include "Pipeline.h"
#include "GltfPipeline.h"
#include "GltfSkeletonPipeline.h"
#include "GltfGPUPipeline.h"
#include "PipelineLayout.h"
#include "Framebuffer.h"
#include "CommandPool.h"
#include "CommandBuffer.h"
#include "SyncObjects.h"
#include "Texture.h"
#include "UniformBuffer.h"
#include "ShaderStorageBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "UserInterface.h"
#include "Camera.h"
#include "GltfModel.h"

#include "VkRenderData.h"

class VkRenderer {
  public:
    VkRenderer(GLFWwindow *window);

    bool init(unsigned int width, unsigned int height);
    void setSize(unsigned int width, unsigned int height);
    bool draw();
    void handleKeyEvents(int key, int scancode, int action, int mods);
    void handleMouseButtonEvents(int button, int action, int mods);
    void handleMousePositionEvents(double xPos, double yPos);

    void cleanup();

  private:
    VkRenderData mRenderData{};
    VkGltfRenderData mGltfRenderData{};

    UserInterface mUserInterface{};
    Camera mCamera{};

    std::shared_ptr<VkMesh> mSkeletonMesh = nullptr;
    unsigned int mSkeletonLineIndexCount = 0;

    std::shared_ptr<GltfModel> mGltfModel = nullptr;
    bool mModelUploadRequired = true;

    bool mMouseLock = false;
    int mMouseXPos = 0;
    int mMouseYPos = 0;

    double mLastTickTime = 0.0;

    void handleMovementKeys();
    int mCameraForward = 0;
    int mCameraStrafe = 0;
    int mCameraUpDown = 0;

    Timer mFrameTimer{};
    Timer mMatrixGenerateTimer{};
    Timer mUploadToVBOTimer{};
    Timer mUploadToUBOTimer{};
    Timer mUIGenerateTimer{};
    Timer mUIDrawTimer{};

    VkSurfaceKHR mSurface = VK_NULL_HANDLE;

    VkDeviceSize mMinUniformBufferOffsetAlignment = 0;

    std::vector<glm::mat4> mPerspViewMatrices{};

    bool deviceInit();
    bool getQueue();
    bool createDepthBuffer();
    bool createVBO();
    bool createUBO();
    bool createMatrixSSBO();
    bool createDQSSBO();
    bool createSwapchain();
    bool createRenderPass();
    bool createGltfPipelineLayout();
    bool createLinePipeline();
    bool createGltfSkeletonPipeline();
    bool createGltfGPUPipeline();
    bool createGltfGPUDQPipeline();
    bool createFramebuffer();
    bool createCommandPool();
    bool createCommandBuffer();
    bool createSyncObjects();
    bool initUserInterface();
    bool loadGltfModel();

    bool initVma();

    bool recreateSwapchain();
};
