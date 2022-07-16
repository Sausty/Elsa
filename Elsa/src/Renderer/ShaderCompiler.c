#include "ShaderCompiler.h"
#include "RendererFrontend.h"

#include <Core/Logger.h>
#include <Containers/Darray.h>
#include <Platform/FileSystem.h>
#include <Platform/Platform.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <shaderc/shaderc.h>
#include <SPIRV/spirv_reflect.h>
#include <TOML/toml.h>

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

CullMode GetCullModeFromString(char* mode);
CompareOP GetCompareOPFromString(char* op);
FrontFace GetFrontFaceFromString(char* face);
PrimitiveTopology GetPrimitiveTopologyFromString(char* topology);
PolygonMode GetPolygonModeFromString(char* mode);

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
	shaderc_compile_options_set_optimization_level(options, shaderc_optimization_level_zero);
	
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
	out_pack->Path = path;
	
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

b8 MaterialLayoutLoad(const char* path, MaterialLayout* layout)
{
	layout->Path = path;
	
	CODE_BLOCK("Layout config")
	{
		FILE* fp = NULL;
		char errbuf[200] = {0};
		
		fp = fopen(path, "r");
		if (!fp) {
			ELSA_FATAL("Failed to load material layout file: %s", path);
			return false;
		}
		
		toml_table_t* conf = toml_parse_file(fp, errbuf, sizeof(errbuf));
		fclose(fp);
		
		if (!conf) {
			ELSA_FATAL("Failed to parse TOML material layout: %s", path);
			return false;
		}
		
		toml_table_t* shaders = toml_table_in(conf, "Shaders");
		if (!shaders) {
			ELSA_FATAL("Failed to parse shaders table from material layout: %s", path);
			return false;
		}
		
		toml_table_t* render_properties = toml_table_in(conf, "RenderProperties");
		if (!render_properties) {
			ELSA_FATAL("Failed to parse render properties table from material layout: %s", path);
			return false;
		}
		
		// Shaders
		toml_datum_t pack_directory = toml_string_in(shaders, "PackDirectory");
		ShaderPackCreate(pack_directory.u.s, &layout->Pack);
		PlatformFree(pack_directory.u.s);
		
		// Render properties
		toml_datum_t cull_mode = toml_string_in(render_properties, "CullMode");
		layout->Pipeline.Config.Cull = GetCullModeFromString(cull_mode.u.s);
		PlatformFree(cull_mode.u.s);
		
		toml_datum_t depth_op = toml_string_in(render_properties, "DepthOperation");
		layout->Pipeline.Config.OP = GetCompareOPFromString(depth_op.u.s);
		PlatformFree(depth_op.u.s);
		
		toml_datum_t front_face = toml_string_in(render_properties, "FrontFace");
		layout->Pipeline.Config.Face = GetFrontFaceFromString(front_face.u.s);
		PlatformFree(depth_op.u.s);
		
		toml_datum_t topology = toml_string_in(render_properties, "PrimitiveTopology");
		layout->Pipeline.Config.Topology = GetPrimitiveTopologyFromString(topology.u.s);
		PlatformFree(topology.u.s);
		
		toml_datum_t polygon_mode = toml_string_in(render_properties, "PolygonMode");
		layout->Pipeline.Config.PolyMode = GetPolygonModeFromString(polygon_mode.u.s);
		PlatformFree(polygon_mode.u.s);
		
		layout->Config = layout->Pipeline.Config;
		
		toml_free(conf);
	}
	
	CODE_BLOCK("Descriptor map reflection")
	{
		if (!RendererFrontendDescriptorMapCreate(&layout->Pack, &layout->DescMap)) {
			ELSA_ERROR("Failed to create material layout descriptor map!");
			return false;
		}
	}

	CODE_BLOCK("Pipeline creation")
	{
		if (!RendererFrontendRenderPipelineCreate(&layout->Pack, &layout->DescMap, &layout->Pipeline)) {
			ELSA_ERROR("Failed to create material layout render pipeline!");
			return false;
		}
	}
	
	return true;
}

void MaterialLayoutDestroy(MaterialLayout* layout)
{
	RendererFrontendDescriptorMapDestroy(&layout->DescMap);
	RendererFrontendRenderPipelineDestroy(&layout->Pipeline);
	ShaderPackDestroy(&layout->Pack);
}

CullMode GetCullModeFromString(char* mode)
{
	if (!strcmp(mode, "None"))
		return CULL_MODE_NONE;
	if (!strcmp(mode, "Front"))
		return CULL_MODE_FRONT;
	if (!strcmp(mode, "Back"))
		return CULL_MODE_BACK;
	if (!strcmp(mode, "FrontAndBack"))
		return CULL_MODE_FRONT_AND_BACK;
	
	return CULL_MODE_NONE;
}

CompareOP GetCompareOPFromString(char* op)
{
	if (!strcmp(op, "Never"))
		return COMPARE_OP_NEVER;
	if (!strcmp(op, "Less"))
		return COMPARE_OP_LESS;
	if (!strcmp(op, "Equal"))
		return COMPARE_OP_EQUAL;
	if (!strcmp(op, "LessEqual"))
		return COMPARE_OP_LESS_EQUAL;
	if (!strcmp(op, "Greater"))
		return COMPARE_OP_GREATER;
	if (!strcmp(op, "GreaterEqual"))
		return COMPARE_OP_GREATER_EQUAL;
	if (!strcmp(op, "Always"))
		return COMPARE_OP_ALWAYS;
	
	return COMPARE_OP_NEVER;
}

FrontFace GetFrontFaceFromString(char* face)
{
	if (!strcmp(face, "CW"))
		return FRONT_FACE_CW;
	if (!strcmp(face, "CCW"))
		return FRONT_FACE_CCW;
	
	return FRONT_FACE_CW;
}

PrimitiveTopology GetPrimitiveTopologyFromString(char* topology)
{
	if (!strcmp(topology, "PointList"))
		return PRIMITIVE_TOPOLOGY_POINT_LIST;
	if (!strcmp(topology, "LineList"))
		return PRIMITIVE_TOPOLOGY_LINE_LIST;
	if (!strcmp(topology, "LineStrip"))
		return PRIMITIVE_TOPOLOGY_LINE_STRIP;
	if (!strcmp(topology, "TriangeList"))
		return PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	if (!strcmp(topology, "TriangleStrip"))
		return PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
	
	return PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
}

PolygonMode GetPolygonModeFromString(char* mode)
{
	if (!strcmp(mode, "Fill"))
		return POLYGON_MODE_FILL;
	if (!strcmp(mode, "Line"))
		return POLYGON_MODE_LINE;
	if (!strcmp(mode, "Point"))
		return POLYGON_MODE_POINT;
	
	return POLYGON_MODE_FILL;
}