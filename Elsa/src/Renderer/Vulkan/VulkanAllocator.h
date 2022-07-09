/**
 * @file VulkanAllocator.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains functions regarding vulkan device allocations.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_VULKAN_ALLOCATOR_H
#define ELSA_VULKAN_ALLOCATOR_H

#include <Renderer/Vulkan/VulkanTypes.h>

b8 VulkanAllocatorInit(VulkanAllocator* allocator, VulkanContext* context);
void VulkanAllocatorFree(VulkanAllocator* allocator, VulkanContext* context);

#endif