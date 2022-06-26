/**
 * @file VulkanDevice.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains a unified Vulkan device, which holds state and pointers
 * to both the Vulkan physical and logical devices.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_VULKAN_DEVICE_H
#define ELSA_VULKAN_DEVICE_H

#include "VulkanTypes.h"

b8 VulkanDeviceCreate(VulkanContext* context);
void VulkanDeviceDestroy(VulkanContext* context);

#endif