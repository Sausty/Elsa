#include "VulkanRenderPipeline.h"

#include <Containers/Darray.h>
#include <Core/MemTracker.h>
#include <Core/Logger.h>
#include <Platform/Platform.h>

#include <SPIRV/spirv_reflect.h>
#include <stdlib.h>

u32 VulkanFormatSize(VkFormat format)
{
    switch (format) {
        case VK_FORMAT_UNDEFINED: return 0;
        case VK_FORMAT_R4G4_UNORM_PACK8: return 1;
        case VK_FORMAT_R4G4B4A4_UNORM_PACK16: return 2;
        case VK_FORMAT_B4G4R4A4_UNORM_PACK16: return 2;
        case VK_FORMAT_R5G6B5_UNORM_PACK16: return 2;
        case VK_FORMAT_B5G6R5_UNORM_PACK16: return 2;
        case VK_FORMAT_R5G5B5A1_UNORM_PACK16: return 2;
        case VK_FORMAT_B5G5R5A1_UNORM_PACK16: return 2;
        case VK_FORMAT_A1R5G5B5_UNORM_PACK16: return 2;
        case VK_FORMAT_R8_UNORM: return 1;
        case VK_FORMAT_R8_SNORM: return 1;
        case VK_FORMAT_R8_USCALED: return 1;
        case VK_FORMAT_R8_SSCALED: return 1;
        case VK_FORMAT_R8_UINT: return 1;
        case VK_FORMAT_R8_SINT: return 1;
        case VK_FORMAT_R8_SRGB: return 1;
        case VK_FORMAT_R8G8_UNORM: return 2;
        case VK_FORMAT_R8G8_SNORM: return 2;
        case VK_FORMAT_R8G8_USCALED: return 2;
        case VK_FORMAT_R8G8_SSCALED: return 2;
        case VK_FORMAT_R8G8_UINT: return 2;
        case VK_FORMAT_R8G8_SINT: return 2;
        case VK_FORMAT_R8G8_SRGB: return 2;
        case VK_FORMAT_R8G8B8_UNORM: return 3;
        case VK_FORMAT_R8G8B8_SNORM: return 3;
        case VK_FORMAT_R8G8B8_USCALED: return 3;
        case VK_FORMAT_R8G8B8_SSCALED: return 3;
        case VK_FORMAT_R8G8B8_UINT: return 3;
        case VK_FORMAT_R8G8B8_SINT: return 3;
        case VK_FORMAT_R8G8B8_SRGB: return 3;
        case VK_FORMAT_B8G8R8_UNORM: return 3;
        case VK_FORMAT_B8G8R8_SNORM: return 3;
        case VK_FORMAT_B8G8R8_USCALED: return 3;
        case VK_FORMAT_B8G8R8_SSCALED: return 3;
        case VK_FORMAT_B8G8R8_UINT: return 3;
        case VK_FORMAT_B8G8R8_SINT: return 3;
        case VK_FORMAT_B8G8R8_SRGB: return 3;
        case VK_FORMAT_R8G8B8A8_UNORM: return 4;
        case VK_FORMAT_R8G8B8A8_SNORM: return 4;
        case VK_FORMAT_R8G8B8A8_USCALED: return 4;
        case VK_FORMAT_R8G8B8A8_SSCALED: return 4;
        case VK_FORMAT_R8G8B8A8_UINT: return 4;
        case VK_FORMAT_R8G8B8A8_SINT: return 4;
        case VK_FORMAT_R8G8B8A8_SRGB: return 4;
        case VK_FORMAT_B8G8R8A8_UNORM: return 4;
        case VK_FORMAT_B8G8R8A8_SNORM: return 4;
        case VK_FORMAT_B8G8R8A8_USCALED: return 4;
        case VK_FORMAT_B8G8R8A8_SSCALED: return 4;
        case VK_FORMAT_B8G8R8A8_UINT: return 4;
        case VK_FORMAT_B8G8R8A8_SINT: return 4;
        case VK_FORMAT_B8G8R8A8_SRGB: return 4;
        case VK_FORMAT_A8B8G8R8_UNORM_PACK32: return 4;
        case VK_FORMAT_A8B8G8R8_SNORM_PACK32: return 4;
        case VK_FORMAT_A8B8G8R8_USCALED_PACK32: return 4;
        case VK_FORMAT_A8B8G8R8_SSCALED_PACK32: return 4;
        case VK_FORMAT_A8B8G8R8_UINT_PACK32: return 4;
        case VK_FORMAT_A8B8G8R8_SINT_PACK32: return 4;
        case VK_FORMAT_A8B8G8R8_SRGB_PACK32: return 4;
        case VK_FORMAT_A2R10G10B10_UNORM_PACK32: return 4;
        case VK_FORMAT_A2R10G10B10_SNORM_PACK32: return 4;
        case VK_FORMAT_A2R10G10B10_USCALED_PACK32: return 4;
        case VK_FORMAT_A2R10G10B10_SSCALED_PACK32: return 4;
        case VK_FORMAT_A2R10G10B10_UINT_PACK32: return 4;
        case VK_FORMAT_A2R10G10B10_SINT_PACK32: return 4;
        case VK_FORMAT_A2B10G10R10_UNORM_PACK32: return 4;
        case VK_FORMAT_A2B10G10R10_SNORM_PACK32: return 4;
        case VK_FORMAT_A2B10G10R10_USCALED_PACK32: return 4;
        case VK_FORMAT_A2B10G10R10_SSCALED_PACK32: return 4;
        case VK_FORMAT_A2B10G10R10_UINT_PACK32: return 4;
        case VK_FORMAT_A2B10G10R10_SINT_PACK32: return 4;
        case VK_FORMAT_R16_UNORM: return 2;
        case VK_FORMAT_R16_SNORM: return 2;
        case VK_FORMAT_R16_USCALED: return 2;
        case VK_FORMAT_R16_SSCALED: return 2;
        case VK_FORMAT_R16_UINT: return 2;
        case VK_FORMAT_R16_SINT: return 2;
        case VK_FORMAT_R16_SFLOAT: return 2;
        case VK_FORMAT_R16G16_UNORM: return 4;
        case VK_FORMAT_R16G16_SNORM: return 4;
        case VK_FORMAT_R16G16_USCALED: return 4;
        case VK_FORMAT_R16G16_SSCALED: return 4;
        case VK_FORMAT_R16G16_UINT: return 4;
        case VK_FORMAT_R16G16_SINT: return 4;
        case VK_FORMAT_R16G16_SFLOAT: return 4;
        case VK_FORMAT_R16G16B16_UNORM: return 6;
        case VK_FORMAT_R16G16B16_SNORM: return 6;
        case VK_FORMAT_R16G16B16_USCALED: return 6;
        case VK_FORMAT_R16G16B16_SSCALED: return 6;
        case VK_FORMAT_R16G16B16_UINT: return 6;
        case VK_FORMAT_R16G16B16_SINT: return 6;
        case VK_FORMAT_R16G16B16_SFLOAT: return 6;
        case VK_FORMAT_R16G16B16A16_UNORM: return 8;
        case VK_FORMAT_R16G16B16A16_SNORM: return 8;
        case VK_FORMAT_R16G16B16A16_USCALED: return 8;
        case VK_FORMAT_R16G16B16A16_SSCALED: return 8;
        case VK_FORMAT_R16G16B16A16_UINT: return 8;
        case VK_FORMAT_R16G16B16A16_SINT: return 8;
        case VK_FORMAT_R16G16B16A16_SFLOAT: return 8;
        case VK_FORMAT_R32_UINT: return 4;
        case VK_FORMAT_R32_SINT: return 4;
        case VK_FORMAT_R32_SFLOAT: return 4;
        case VK_FORMAT_R32G32_UINT: return 8;
        case VK_FORMAT_R32G32_SINT: return 8;
        case VK_FORMAT_R32G32_SFLOAT: return 8;
        case VK_FORMAT_R32G32B32_UINT: return 12;
        case VK_FORMAT_R32G32B32_SINT: return 12;
        case VK_FORMAT_R32G32B32_SFLOAT: return 12;
        case VK_FORMAT_R32G32B32A32_UINT: return 16;
        case VK_FORMAT_R32G32B32A32_SINT: return 16;
        case VK_FORMAT_R32G32B32A32_SFLOAT: return 16;
        case VK_FORMAT_R64_UINT: return 8;
        case VK_FORMAT_R64_SINT: return 8;
        case VK_FORMAT_R64_SFLOAT: return 8;
        case VK_FORMAT_R64G64_UINT: return 16;
        case VK_FORMAT_R64G64_SINT: return 16;
        case VK_FORMAT_R64G64_SFLOAT: return 16;
        case VK_FORMAT_R64G64B64_UINT: return 24;
        case VK_FORMAT_R64G64B64_SINT: return 24;
        case VK_FORMAT_R64G64B64_SFLOAT: return 24;
        case VK_FORMAT_R64G64B64A64_UINT: return 32;
        case VK_FORMAT_R64G64B64A64_SINT: return 32;
        case VK_FORMAT_R64G64B64A64_SFLOAT: return 32;
        case VK_FORMAT_B10G11R11_UFLOAT_PACK32: return 4;
        case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32: return 4;
    }
	
    return 0;
}

VkShaderStageFlagBits ShaderStageToVulkan(ShaderStage stage)
{
	switch (stage)
	{
		case SHADER_STAGE_VERTEX:
		return VK_SHADER_STAGE_VERTEX_BIT;
		case SHADER_STAGE_FRAGMENT:
		return VK_SHADER_STAGE_FRAGMENT_BIT;
		case SHADER_STAGE_GEOMETRY:
		return VK_SHADER_STAGE_GEOMETRY_BIT;
		case SHADER_STAGE_COMPUTE:
		return VK_SHADER_STAGE_COMPUTE_BIT;
		case SHADER_STAGE_TESSELLATION_EVALUATION:
		return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		case SHADER_STAGE_TESSELLATION_CONTROL:
		return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		case SHADER_STAGE_MESH:
		return VK_SHADER_STAGE_MESH_BIT_NV;
		case SHADER_STAGE_TASK:
		return VK_SHADER_STAGE_TASK_BIT_NV;
	}
	
	return VK_SHADER_STAGE_VERTEX_BIT;
}

VkResult MakeShaderModule(VulkanContext* ctx, VkShaderModule* out, u8* code, u64 size)
{
	VkShaderModuleCreateInfo info = {0};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.codeSize = size;
    info.pCode = (u32*)code;
	
    return vkCreateShaderModule(ctx->Device.LogicalDevice, &info, NULL, out);
}

b8 VulkanRenderPipelineCreate(VulkanContext* context, ShaderPack* pack, RenderPipeline* pipeline)
{
	VulkanRenderPipeline* backend = MemoryTrackerAlloc(sizeof(VulkanRenderPipeline), MEMORY_TAG_RENDERER);
	pipeline->Pack = pack;
	
	b8 mesh_shader_enabled = false;
	
	VkPipelineShaderStageCreateInfo* shader_stages = Darray_Reserve(VkPipelineShaderStageCreateInfo, Darray_Length(pipeline->Pack->Modules));
	for (u32 i = 0; i < Darray_Length(pipeline->Pack->Modules); i++) {
		VkPipelineShaderStageCreateInfo* pipeline_stage = &shader_stages[i];
		
		if (pipeline->Pack->Modules[i].Stage == SHADER_STAGE_MESH || pipeline->Pack->Modules[i].Stage == SHADER_STAGE_TASK)
			mesh_shader_enabled = true;
		
		pipeline_stage->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		pipeline_stage->stage = ShaderStageToVulkan(pipeline->Pack->Modules[i].Stage);
		pipeline_stage->pName = "main";
		if (MakeShaderModule(context, &pipeline_stage->module, pipeline->Pack->Modules[i].ByteCode, pipeline->Pack->Modules[i].ByteCodeSize) != VK_SUCCESS) {
			ELSA_FATAL("Failed to create shader module!");
			return false;
		}
	}
	
	VkVertexInputBindingDescription vertex_input_binding_desc = {0};
	
    VkPipelineVertexInputStateCreateInfo vertex_input_state_info = {0};
	vertex_input_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertex_input_binding_desc.binding = 0;
    vertex_input_binding_desc.stride = 0; 
    vertex_input_binding_desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	
    VkPipelineInputAssemblyStateCreateInfo input_assembly = {0};
	input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	
    VkVertexInputAttributeDescription* attribute_descriptions = NULL;
    SpvReflectInterfaceVariable** vs_input_vars = NULL;
	SpvReflectShaderModule input_layout_reflect;
	
	if (!mesh_shader_enabled)
	{
		ShaderModule* vertex_module;
		for (u32 i = 0; i < Darray_Length(pipeline->Pack->Modules); i++) {
			if (pipeline->Pack->Modules[i].Stage == SHADER_STAGE_VERTEX)
				vertex_module = &pipeline->Pack->Modules[i];
		}
		
		SpvReflectResult reflect_result = spvReflectCreateShaderModule(vertex_module->ByteCodeSize, vertex_module->ByteCode, &input_layout_reflect);
		if (reflect_result != SPV_REFLECT_RESULT_SUCCESS) {
			ELSA_FATAL("Failed to reflect input layout module!");
			return false;
		}
		
		u32 vs_input_var_count = 0;
        spvReflectEnumerateInputVariables(&input_layout_reflect, &vs_input_var_count, 0);
        vs_input_vars = calloc(vs_input_var_count, sizeof(SpvReflectInterfaceVariable*));
        spvReflectEnumerateInputVariables(&input_layout_reflect, &vs_input_var_count, vs_input_vars);
		
		attribute_descriptions = PlatformAlloc(sizeof(VkVertexInputAttributeDescription) * vs_input_var_count);
		
        for (u32 i = 0; i < vs_input_var_count; i++)
        {
            SpvReflectInterfaceVariable* var = vs_input_vars[i];
			
            VkVertexInputAttributeDescription attrib = { 0 };
			
            attrib.location = var->location;
            attrib.binding = 0;
            attrib.format = (VkFormat)var->format;
            attrib.offset = vertex_input_binding_desc.stride;
			
            attribute_descriptions[i] = attrib;
			
            vertex_input_binding_desc.stride += VulkanFormatSize(attrib.format);
        }
		
        vertex_input_state_info.vertexBindingDescriptionCount = vertex_input_binding_desc.stride == 0 ? 0 : 1;
        vertex_input_state_info.pVertexBindingDescriptions = &vertex_input_binding_desc;
        vertex_input_state_info.vertexAttributeDescriptionCount = vs_input_var_count;
        vertex_input_state_info.pVertexAttributeDescriptions = attribute_descriptions;
		
        input_assembly.topology = (VkPrimitiveTopology)pipeline->Config.Topology;;
        input_assembly.primitiveRestartEnable = VK_FALSE;
	}
	
	VkDynamicState states[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };
	
	VkPipelineDynamicStateCreateInfo dynamic_state = {0};
    dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic_state.dynamicStateCount = 2;
    dynamic_state.pDynamicStates = states;
	
	// Dynamic state
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = (f32)context->FramebufferHeight;
    viewport.width = (f32)context->FramebufferWidth;
    viewport.height = -(f32)context->FramebufferHeight;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
	
    // Scissor
    VkRect2D scissor;
    scissor.offset.x = scissor.offset.y = 0;
    scissor.extent.width = context->FramebufferWidth;
    scissor.extent.height = context->FramebufferHeight;
	
	VkPipelineViewportStateCreateInfo viewport_state = {0};
    viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports = &viewport;
    viewport_state.scissorCount = 1;
    viewport_state.pScissors = &scissor;
	
    VkPipelineRasterizationStateCreateInfo rasterizer = {0};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = (VkPolygonMode)pipeline->Config.PolyMode;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = (VkCullModeFlags)pipeline->Config.Cull;
    rasterizer.frontFace = (VkFrontFace)pipeline->Config.Face;
    rasterizer.depthBiasEnable = VK_FALSE;
	
	VkPipelineMultisampleStateCreateInfo multisampling = {0};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	
    VkPipelineColorBlendAttachmentState color_blend_attachment = {0};
    color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    color_blend_attachment.blendEnable = VK_FALSE;
	
	VkPipelineDepthStencilStateCreateInfo depth_stencil = {0};
    depth_stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depth_stencil.depthTestEnable = VK_TRUE;
    depth_stencil.depthWriteEnable = VK_TRUE;
	depth_stencil.depthCompareOp = (VkCompareOp)pipeline->Config.OP;
    depth_stencil.depthBoundsTestEnable = VK_FALSE;
    depth_stencil.minDepthBounds = 0.0f; // Optional
    depth_stencil.maxDepthBounds = 1.0f; // Optional
    depth_stencil.stencilTestEnable = VK_FALSE;
	
	VkPipelineColorBlendStateCreateInfo color_blending = {0};
    color_blending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blending.logicOpEnable = VK_FALSE;
    color_blending.logicOp = VK_LOGIC_OP_COPY;
    color_blending.attachmentCount = 1;
    color_blending.pAttachments = &color_blend_attachment;
    color_blending.blendConstants[0] = 0.0f;
    color_blending.blendConstants[1] = 0.0f;
    color_blending.blendConstants[2] = 0.0f;
    color_blending.blendConstants[3] = 0.0f;
	
	VkPipelineLayoutCreateInfo pipeline_layout_info = {0};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	
	VkResult res = vkCreatePipelineLayout(context->Device.LogicalDevice, &pipeline_layout_info, NULL, &backend->PipelineLayout);
	if (res != VK_SUCCESS) {
		ELSA_FATAL("Failed to create pipeline layout!");
		return false;
	}
	
	// TODO(milo): dynamic rendering setup
	VkGraphicsPipelineCreateInfo pipeline_info = {0};
    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.stageCount = Darray_Length(pipeline->Pack->Modules);
    pipeline_info.pStages = shader_stages;
    pipeline_info.pViewportState = &viewport_state;
    pipeline_info.pRasterizationState = &rasterizer;
    pipeline_info.pMultisampleState = &multisampling;
    pipeline_info.pColorBlendState = &color_blending;
    pipeline_info.layout = backend->PipelineLayout;
    pipeline_info.renderPass = VK_NULL_HANDLE;
    pipeline_info.pDynamicState = &dynamic_state;
    pipeline_info.pDepthStencilState = &depth_stencil;
    pipeline_info.subpass = 0;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
	if (!mesh_shader_enabled) {
		pipeline_info.pVertexInputState = &vertex_input_state_info;
        pipeline_info.pInputAssemblyState = &input_assembly;
	}
	
	res = vkCreateGraphicsPipelines(context->Device.LogicalDevice, VK_NULL_HANDLE, 1, &pipeline_info, NULL, &backend->Pipeline);
	if (res != VK_SUCCESS) {
		ELSA_FATAL("Failed to create graphics pipeline!");
		return false;
	}
	
	if (!mesh_shader_enabled)
	{
		PlatformFree(attribute_descriptions);
		PlatformFree(vs_input_vars);
		spvReflectDestroyShaderModule(&input_layout_reflect);
	}
	
	for (u32 i = 0; i < Darray_Length(pipeline->Pack->Modules); i++) {
		vkDestroyShaderModule(context->Device.LogicalDevice, shader_stages[i].module, NULL);
	}
	Darray_Destroy(shader_stages);
	
	pipeline->Internal = backend;
	
	return true;
}

void VulkanRenderPipelineDestroy(VulkanContext* context, RenderPipeline* pipeline)
{
	VulkanRenderPipeline* backend = pipeline->Internal;
	
	vkDestroyPipeline(context->Device.LogicalDevice, backend->Pipeline, NULL);
	vkDestroyPipelineLayout(context->Device.LogicalDevice, backend->PipelineLayout, NULL);
	PlatformFree(backend);
}