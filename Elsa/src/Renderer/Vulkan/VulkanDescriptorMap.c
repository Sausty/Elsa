#include "VulkanDescriptorMap.h"

#include <Containers/Darray.h>
#include <Core/MemTracker.h>
#include <Core/Logger.h>

VkShaderStageFlagBits GetShaderStageFlagBits(ShaderStage stage)
{
	switch (stage)
	{
		case SHADER_STAGE_VERTEX:
		return VK_SHADER_STAGE_VERTEX_BIT;
		case SHADER_STAGE_TESSELLATION_EVALUATION:
		return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		case SHADER_STAGE_TESSELLATION_CONTROL:
		return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		case SHADER_STAGE_GEOMETRY:
		return VK_SHADER_STAGE_GEOMETRY_BIT;
		case SHADER_STAGE_COMPUTE:
		return VK_SHADER_STAGE_COMPUTE_BIT;
		case SHADER_STAGE_FRAGMENT:
		return VK_SHADER_STAGE_FRAGMENT_BIT;
		case SHADER_STAGE_MESH:
		return VK_SHADER_STAGE_MESH_BIT_NV;
		case SHADER_STAGE_TASK:
		return VK_SHADER_STAGE_TASK_BIT_NV;
	}

	return VK_SHADER_STAGE_ALL_GRAPHICS;
}

b8 VulkanDescriptorMapCreate(VulkanContext* context, DescriptorMap* map)
{
	VulkanDescriptorMap* backend = MemoryTrackerAlloc(sizeof(VulkanDescriptorMap), MEMORY_TAG_RENDERER);
	backend->SubmapCount = map->SubmapCount;

	// ALL SHADER STAGES
	for (u32 i = 0; i < map->SubmapCount; i++) {
		backend->Submaps[i].LayoutCount = map->Submaps[i].LayoutCount;
		// ALL DESCRIPTOR SET LAYOUTS
		for (u32 j = 0; j < map->Submaps[i].LayoutCount; j++) { 
			backend->Submaps[i].Layouts[j].BindingCount = map->Submaps[i].Layouts[j].DescriptorCount;

			VulkanDescriptorSetLayout* layout = &backend->Submaps[i].Layouts[j];
			layout->Bindings = Darray_Reserve(VkDescriptorSetLayoutBinding, map->Submaps[i].Layouts[i].DescriptorCount);

			// ALL DESCRIPTORS
			for (u32 l = 0; l < map->Submaps[i].Layouts[j].DescriptorCount; l++) { 
				DescriptorInfo* descriptor = &map->Submaps[i].Layouts[j].Descriptors[l];

				VkDescriptorSetLayoutBinding binding = {0};
				binding.stageFlags = GetShaderStageFlagBits(map->Submaps[i].Stage);
				binding.binding = descriptor->Binding;
				binding.descriptorCount = descriptor->Count;
				binding.descriptorType = (VkDescriptorType)descriptor->Type;
				binding.pImmutableSamplers = NULL;
				Darray_Push(layout->Bindings, binding);
			}

			// Populate create info
			layout->CreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layout->CreateInfo.bindingCount = Darray_Length(layout->Bindings);
			layout->CreateInfo.pBindings = layout->Bindings;
			layout->CreateInfo.flags = 0;
			layout->CreateInfo.pNext = NULL;

			// Create
			if (vkCreateDescriptorSetLayout(context->Device.LogicalDevice, &layout->CreateInfo, NULL, &layout->Layout) != VK_SUCCESS) {
				ELSA_ERROR("Failed to create descriptor set layout.");
				return false;
			}
		}
	} 
	
	map->Internal = backend;

	return true;
}

void VulkanDescriptorMapDestroy(VulkanContext* context, DescriptorMap* map)
{
	VulkanDescriptorMap* backend = map->Internal;

	for (u32 i = 0; i < backend->SubmapCount; i++) {
		for (u32 j = 0; j < backend->Submaps[i].LayoutCount; j++) {
			vkDestroyDescriptorSetLayout(context->Device.LogicalDevice, backend->Submaps[i].Layouts[j].Layout, NULL);
			Darray_Destroy(backend->Submaps[i].Layouts[j].Bindings);
		}
	}

	MemoryTrackerFree(backend, sizeof(VulkanDescriptorMap), MEMORY_TAG_RENDERER);
}