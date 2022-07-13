#include "ShaderCompiler.h"

#include <Core/Logger.h>
#include <Containers/Darray.h>
#include <Platform/FileSystem.h>
#include <Platform/Platform.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <shaderc/shaderc.h>

ShaderStage GetStageFromString(const char* extension)
{
	if (strcmp(extension, "vert") == 0)
		return SHADER_STAGE_VERTEX;
	if (strcmp(extension, "frag") == 0)
		return SHADER_STAGE_FRAGMENT;
	if (strcmp(extension, "geom") == 0)
		return SHADER_STAGE_GEOMETRY;
	if (strcmp(extension, "comp") == 0)
		return SHADER_STAGE_COMPUTE;
	if (strcmp(extension, "tesc") == 0)
		return SHADER_STAGE_TESSELLATION_CONTROL;
	if (strcmp(extension, "tese") == 0)
		return SHADER_STAGE_TESSELLATION_EVALUATION;
	if (strcmp(extension, "task") == 0)
		return SHADER_STAGE_TASK;
	if (strcmp(extension, "mesh") == 0)
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
	
	FileSystemClose(&file_handle);
	shaderc_compiler_release(compiler);
	
	return true;
}

b8 ShaderPackCreate(const char* path, ShaderPack* out_pack)
{
	out_pack->Modules = Darray_Create(ShaderModule);
	
	// Whether or not the engine should compile the shaders present in the pack.
	b8 should_compile = true;
	
	// Get the binary path of the shader pack
	char bin_path[PLATFORM_MAX_PATH];
	sprintf(bin_path, "%s/bin", path);
	if (PlatformDirectoryExists(bin_path)) {
		should_compile = false;
	} else {
		PlatformCreateDirectory(bin_path);
	}
	
	if (should_compile) {
		// Get all the files in the directory
		char dir_path[PLATFORM_MAX_PATH];
		sprintf(dir_path, "%s/*", path);
		char** filenames = Darray_Create(char*);
		PlatformGetDirectoryFiles(dir_path, &filenames);
		
		for (u32 i = 0; i < Darray_Length(filenames); i++) {
			ShaderModule module;
			module.Binary = false;
			
			// Compile shader
			char shader_source_path[PLATFORM_MAX_PATH];
			sprintf(shader_source_path, "%s/%s", path, filenames[i]);
			ShaderCompile(shader_source_path, &module);
			Darray_Push(out_pack->Modules, module);
			
			// Write spir-v to file
			char shader_bin_path[PLATFORM_MAX_PATH];
			sprintf(shader_bin_path, "%s/bin/%s.spv", path, filenames[i]);
			PlatformCreateFile(shader_bin_path);
			
			FileHandle file_handle;
			u64 bytes_written;
			if (!FileSystemOpen(shader_bin_path, FILE_MODE_WRITE, true, &file_handle)) {
				ELSA_FATAL("Failed to open binary file");
				return false;
			}
			
			if (!FileSystemWrite(&file_handle, module.ByteCodeSize, module.ByteCode, &bytes_written)) {
				ELSA_FATAL("Failed to write binary file to shader pack!");
				return false;
			}
			
			// Close file
			FileSystemClose(&file_handle);
			PlatformFree(filenames[i]);
		}
	} else {
		// Get all the files in the directory
		char dir_path[PLATFORM_MAX_PATH];
		sprintf(dir_path, "%s/*", path);
		char** filenames = Darray_Create(char*);
		PlatformGetDirectoryFiles(dir_path, &filenames);
		
		
		for (u32 i = 0; i < Darray_Length(filenames); i++) {
			ShaderModule module;
			module.Binary = true;
			
			char shader_source_path[PLATFORM_MAX_PATH];
			sprintf(shader_source_path, "%s/%s", path, filenames[i]);
			const char* extension = GetFilenameExtension(shader_source_path);
			ShaderStage shader_stage = GetStageFromString(extension);
			module.Stage = shader_stage;
			
			// Read spir-v from file
			char shader_bin_path[PLATFORM_MAX_PATH];
			sprintf(shader_bin_path, "%s/bin/%s.spv", path, filenames[i]);
			FileHandle file_handle;
			if (!FileSystemOpen(shader_bin_path, FILE_MODE_READ, true, &file_handle)) {
				ELSA_FATAL("Failed to open binary file");
				return false;
			}
			
			module.ByteCode = (u8*)FileSystemReadSPIRV(&file_handle, &module.ByteCodeSize);
			
			Darray_Push(out_pack->Modules, module);
			
			// Close file
			FileSystemClose(&file_handle);
			PlatformFree(filenames[i]);
		}
	}
	
	return true;
}

void ShaderPackDestroy(ShaderPack* pack)
{
	for (u32 i = 0; i < Darray_Length(pack->Modules); i++) {
		ShaderModule* module = &pack->Modules[i];
		if (module->Binary) {
			PlatformFree(module->ByteCode);
		}
	}
	Darray_Destroy(pack->Modules);
}