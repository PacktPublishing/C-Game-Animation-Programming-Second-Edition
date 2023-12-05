/* Vulkan shader storage buffer object */
#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

#include "VkRenderData.h"

class ShaderStorageBuffer {
  public:
    static bool init(VkRenderData &renderData, VkShaderStorageBufferData &SSBOData,
      std::vector<glm::mat4> matricesToUpload);
    static bool init(VkRenderData &renderData, VkShaderStorageBufferData &SSBOData,
      std::vector<glm::mat2x4> matricesToUpload);
    static void cleanup(VkRenderData &renderData, VkShaderStorageBufferData &SSBOData);
};
