/**
 * @file ShaderCompiler.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains functions to compile shader files.
 * @version 1.0
 * @date 2022-07-12
 */
#ifndef ELSA_SHADER_COMPILER_H
#define ELSA_SHADER_COMPILER_H

#include "RendererTypes.h"

/**
* @brief Compiles a shader from the given path to SPIR-V.
* @param path The path of the shader.
* @param out_stage A pointer that will hold the resulting shader module.
* @returns True on success; otherwise false.
*/
ELSA_API b8 ShaderCompile(const char* path, ShaderModule* out_stage);

/**
* @brief Frees the given shader module.
* @param shader The shader to free.
*/
ELSA_API void ShaderFree(ShaderModule* shader);

#endif
