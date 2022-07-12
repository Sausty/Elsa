#include "ShaderCompiler.h"

#include <Platform/FileSystem.h>
#include <shaderc/shaderc.h>
#include <Core/Logger.h>

#include <string.h>
#include <stdlib.h>

ShaderStage GetStageFromString(const char* extension)
{
	if (!strcmp(extension, ".vert"))
		return SHADER_STAGE_VERTEX;
	if (!strcmp(extension, ".frag"))
		return SHADER_STAGE_FRAGMENT;
	if (!strcmp(extension, ".geom"))
		return SHADER_STAGE_GEOMETRY;
	if (!strcmp(extension, ".comp"))
		return SHADER_STAGE_COMPUTE;
	if (!strcmp(extension, ".tesc"))
		return SHADER_STAGE_TESSELLATION_CONTROL;
	if (!strcmp(extension, ".tese"))
		return SHADER_STAGE_TESSELLATION_EVALUATION;
	if (!strcmp(extension, ".task"))
		return SHADER_STAGE_TASK;
	if (!strcmp(extension, ".mesh"))
		return SHADER_STAGE_MESH;
	
	return SHADER_STAGE_VERTEX;
}

shaderc_shader_kind ShaderStageToShaderc(ShaderStage type)
{
	switch (type)
	{
		case SHADER_STAGE_VERTEX:
		return shaderc_vertex_shader;
		case SHADER_STAGE_GEOMETRY:
		return shaderc_geometry_shader;
		case SHADER_STAGE_FRAGMENT:
		return shaderc_fragment_shader;
		case SHADER_STAGE_COMPUTE:
		return shaderc_compute_shader;
		case SHADER_STAGE_TESSELLATION_CONTROL:
		return shaderc_tess_control_shader;
		case SHADER_STAGE_TESSELLATION_EVALUATION:
		return shaderc_tess_evaluation_shader;
		case SHADER_STAGE_TASK:
		return shaderc_task_shader;
		case SHADER_STAGE_MESH:
		return shaderc_mesh_shader;
	}
	
	return 0;
}

const char* GetFilenameExtension(const char* path)
{
	const char* dot = strrchr(path, '.');
	if (!dot || dot == path) return "";
	return dot + 1;
}

b8 ShaderCompile(const char* path, ShaderModule* out_stage)
{
	const char* extension = GetFilenameExtension(path);
	ShaderStage shader_stage = GetStageFromString(extension);
	shaderc_shader_kind shader_kind = ShaderStageToShaderc(shader_stage);
	
	shaderc_compiler_t compiler = shaderc_compiler_initialize();
	shaderc_compile_options_t options = shaderc_compile_options_initialize();
	
	shaderc_compile_options_set_source_language(options, shaderc_source_language_glsl);
	shaderc_compile_options_set_target_spirv(options, shaderc_spirv_version_1_4);
	shaderc_compile_options_set_target_env(options, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
	shaderc_compile_options_set_optimization_level(options, shaderc_optimization_level_size);
	
	FileHandle file_handle;
	u64 file_size;
	char buffer[8192];
	
	if (!FileSystemOpen(path, FILE_MODE_READ, false, &file_handle)) {
		ELSA_ERROR("Failed to open file: %s", path);
		return false;
	}
	
	if (!FileSystemReadAllText(&file_handle, buffer, &file_size)) {
		ELSA_ERROR("Failed to read file: %s", path);
		return false;
	}
	
	shaderc_compilation_result_t result = shaderc_compile_into_spv(compiler, buffer, file_size, shader_kind, "shader", "main", options);
	shaderc_compilation_status status = shaderc_result_get_compilation_status(result);
	if (status != shaderc_compilation_status_success)
	{
		ELSA_ERROR("SHADERC ERROR: %s", shaderc_result_get_error_message(result));
		return false;
	}
	
	out_stage->Stage = shader_stage;
	out_stage->ByteCode = (u8*)shaderc_result_get_bytes(result);
	out_stage->ByteCodeSize = shaderc_result_get_length(result);
	
	shaderc_compiler_release(compiler);
	
	return true;
}

void ShaderFree(ShaderModule* shader)
{
	
}