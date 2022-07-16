/**
 * @file VulkanDescriptorMap.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains functions regarding the vulkan backend for descriptor maps.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_VULKAN_DESCRIPTOR_MAP_H
#define ELSA_VULKAN_DESCRIPTOR_MAP_H

#include "VulkanTypes.h"

b8 VulkanDescriptorMapCreate(VulkanContext* context, DescriptorMap* map);
void VulkanDescriptorMapDestroy(VulkanContext* context, DescriptorMap* map);

#endif
