/**
 * @file RendererTypes.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains type definitions regarding renderer data.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_RENDERER_TYPES_H
#define ELSA_RENDERER_TYPES_H

#include <Defines.h>

/** @brief Opaque handle representing a GPU buffer */
typedef struct Buffer Buffer;

/** @brief Opaque handle representing a GPU texture */
typedef struct Texture Texture;

/** @brief Represents the different use cases of a buffer */
typedef enum BufferUsage {
	BUFFER_USAGE_VERTEX,
	BUFFER_USAGE_INDEX,
	BUFFER_USAGE_STORAGE,
	BUFFER_USAGE_UNIFORM
} BufferUsage;

/** @brief Represents the different use cases of a texture */
typedef enum TextureUsage {
	TEXTURE_USAGE_RENDER_TARGET,
	TEXTURE_USAGE_DEPTH,
	TEXTURE_USAGE_SAMPLED,
	TEXTURE_USAGE_STORAGE
} TextureUsage;

/** @brief Represents texture formats */
typedef enum TextureFormat {
	TEXTURE_FORMAT_UNDEFINED = 0,
    TEXTURE_FORMAT_R4G4_UNORM_PACK8 = 1,
    TEXTURE_FORMAT_R4G4B4A4_UNORM_PACK16 = 2,
    TEXTURE_FORMAT_B4G4R4A4_UNORM_PACK16 = 3,
    TEXTURE_FORMAT_R5G6B5_UNORM_PACK16 = 4,
    TEXTURE_FORMAT_B5G6R5_UNORM_PACK16 = 5,
    TEXTURE_FORMAT_R5G5B5A1_UNORM_PACK16 = 6,
    TEXTURE_FORMAT_B5G5R5A1_UNORM_PACK16 = 7,
    TEXTURE_FORMAT_A1R5G5B5_UNORM_PACK16 = 8,
    TEXTURE_FORMAT_R8_UNORM = 9,
    TEXTURE_FORMAT_R8_SNORM = 10,
    TEXTURE_FORMAT_R8_USCALED = 11,
    TEXTURE_FORMAT_R8_SSCALED = 12,
    TEXTURE_FORMAT_R8_UINT = 13,
    TEXTURE_FORMAT_R8_SINT = 14,
    TEXTURE_FORMAT_R8_SRGB = 15,
    TEXTURE_FORMAT_R8G8_UNORM = 16,
    TEXTURE_FORMAT_R8G8_SNORM = 17,
    TEXTURE_FORMAT_R8G8_USCALED = 18,
    TEXTURE_FORMAT_R8G8_SSCALED = 19,
    TEXTURE_FORMAT_R8G8_UINT = 20,
    TEXTURE_FORMAT_R8G8_SINT = 21,
    TEXTURE_FORMAT_R8G8_SRGB = 22,
    TEXTURE_FORMAT_R8G8B8_UNORM = 23,
    TEXTURE_FORMAT_R8G8B8_SNORM = 24,
    TEXTURE_FORMAT_R8G8B8_USCALED = 25,
    TEXTURE_FORMAT_R8G8B8_SSCALED = 26,
    TEXTURE_FORMAT_R8G8B8_UINT = 27,
    TEXTURE_FORMAT_R8G8B8_SINT = 28,
    TEXTURE_FORMAT_R8G8B8_SRGB = 29,
    TEXTURE_FORMAT_B8G8R8_UNORM = 30,
    TEXTURE_FORMAT_B8G8R8_SNORM = 31,
    TEXTURE_FORMAT_B8G8R8_USCALED = 32,
    TEXTURE_FORMAT_B8G8R8_SSCALED = 33,
    TEXTURE_FORMAT_B8G8R8_UINT = 34,
    TEXTURE_FORMAT_B8G8R8_SINT = 35,
    TEXTURE_FORMAT_B8G8R8_SRGB = 36,
    TEXTURE_FORMAT_R8G8B8A8_UNORM = 37,
    TEXTURE_FORMAT_R8G8B8A8_SNORM = 38,
    TEXTURE_FORMAT_R8G8B8A8_USCALED = 39,
    TEXTURE_FORMAT_R8G8B8A8_SSCALED = 40,
    TEXTURE_FORMAT_R8G8B8A8_UINT = 41,
    TEXTURE_FORMAT_R8G8B8A8_SINT = 42,
    TEXTURE_FORMAT_R8G8B8A8_SRGB = 43,
    TEXTURE_FORMAT_B8G8R8A8_UNORM = 44,
    TEXTURE_FORMAT_B8G8R8A8_SNORM = 45,
    TEXTURE_FORMAT_B8G8R8A8_USCALED = 46,
    TEXTURE_FORMAT_B8G8R8A8_SSCALED = 47,
    TEXTURE_FORMAT_B8G8R8A8_UINT = 48,
    TEXTURE_FORMAT_B8G8R8A8_SINT = 49,
    TEXTURE_FORMAT_B8G8R8A8_SRGB = 50,
    TEXTURE_FORMAT_A8B8G8R8_UNORM_PACK32 = 51,
    TEXTURE_FORMAT_A8B8G8R8_SNORM_PACK32 = 52,
    TEXTURE_FORMAT_A8B8G8R8_USCALED_PACK32 = 53,
    TEXTURE_FORMAT_A8B8G8R8_SSCALED_PACK32 = 54,
    TEXTURE_FORMAT_A8B8G8R8_UINT_PACK32 = 55,
    TEXTURE_FORMAT_A8B8G8R8_SINT_PACK32 = 56,
    TEXTURE_FORMAT_A8B8G8R8_SRGB_PACK32 = 57,
    TEXTURE_FORMAT_A2R10G10B10_UNORM_PACK32 = 58,
    TEXTURE_FORMAT_A2R10G10B10_SNORM_PACK32 = 59,
    TEXTURE_FORMAT_A2R10G10B10_USCALED_PACK32 = 60,
    TEXTURE_FORMAT_A2R10G10B10_SSCALED_PACK32 = 61,
    TEXTURE_FORMAT_A2R10G10B10_UINT_PACK32 = 62,
    TEXTURE_FORMAT_A2R10G10B10_SINT_PACK32 = 63,
    TEXTURE_FORMAT_A2B10G10R10_UNORM_PACK32 = 64,
    TEXTURE_FORMAT_A2B10G10R10_SNORM_PACK32 = 65,
    TEXTURE_FORMAT_A2B10G10R10_USCALED_PACK32 = 66,
    TEXTURE_FORMAT_A2B10G10R10_SSCALED_PACK32 = 67,
    TEXTURE_FORMAT_A2B10G10R10_UINT_PACK32 = 68,
    TEXTURE_FORMAT_A2B10G10R10_SINT_PACK32 = 69,
    TEXTURE_FORMAT_R16_UNORM = 70,
    TEXTURE_FORMAT_R16_SNORM = 71,
    TEXTURE_FORMAT_R16_USCALED = 72,
    TEXTURE_FORMAT_R16_SSCALED = 73,
    TEXTURE_FORMAT_R16_UINT = 74,
    TEXTURE_FORMAT_R16_SINT = 75,
    TEXTURE_FORMAT_R16_SFLOAT = 76,
    TEXTURE_FORMAT_R16G16_UNORM = 77,
    TEXTURE_FORMAT_R16G16_SNORM = 78,
    TEXTURE_FORMAT_R16G16_USCALED = 79,
    TEXTURE_FORMAT_R16G16_SSCALED = 80,
    TEXTURE_FORMAT_R16G16_UINT = 81,
    TEXTURE_FORMAT_R16G16_SINT = 82,
    TEXTURE_FORMAT_R16G16_SFLOAT = 83,
    TEXTURE_FORMAT_R16G16B16_UNORM = 84,
    TEXTURE_FORMAT_R16G16B16_SNORM = 85,
    TEXTURE_FORMAT_R16G16B16_USCALED = 86,
    TEXTURE_FORMAT_R16G16B16_SSCALED = 87,
    TEXTURE_FORMAT_R16G16B16_UINT = 88,
    TEXTURE_FORMAT_R16G16B16_SINT = 89,
    TEXTURE_FORMAT_R16G16B16_SFLOAT = 90,
    TEXTURE_FORMAT_R16G16B16A16_UNORM = 91,
    TEXTURE_FORMAT_R16G16B16A16_SNORM = 92,
    TEXTURE_FORMAT_R16G16B16A16_USCALED = 93,
    TEXTURE_FORMAT_R16G16B16A16_SSCALED = 94,
    TEXTURE_FORMAT_R16G16B16A16_UINT = 95,
    TEXTURE_FORMAT_R16G16B16A16_SINT = 96,
    TEXTURE_FORMAT_R16G16B16A16_SFLOAT = 97,
    TEXTURE_FORMAT_R32_UINT = 98,
    TEXTURE_FORMAT_R32_SINT = 99,
    TEXTURE_FORMAT_R32_SFLOAT = 100,
    TEXTURE_FORMAT_R32G32_UINT = 101,
    TEXTURE_FORMAT_R32G32_SINT = 102,
    TEXTURE_FORMAT_R32G32_SFLOAT = 103,
    TEXTURE_FORMAT_R32G32B32_UINT = 104,
    TEXTURE_FORMAT_R32G32B32_SINT = 105,
    TEXTURE_FORMAT_R32G32B32_SFLOAT = 106,
    TEXTURE_FORMAT_R32G32B32A32_UINT = 107,
    TEXTURE_FORMAT_R32G32B32A32_SINT = 108,
    TEXTURE_FORMAT_R32G32B32A32_SFLOAT = 109,
    TEXTURE_FORMAT_R64_UINT = 110,
    TEXTURE_FORMAT_R64_SINT = 111,
    TEXTURE_FORMAT_R64_SFLOAT = 112,
    TEXTURE_FORMAT_R64G64_UINT = 113,
    TEXTURE_FORMAT_R64G64_SINT = 114,
    TEXTURE_FORMAT_R64G64_SFLOAT = 115,
    TEXTURE_FORMAT_R64G64B64_UINT = 116,
    TEXTURE_FORMAT_R64G64B64_SINT = 117,
    TEXTURE_FORMAT_R64G64B64_SFLOAT = 118,
    TEXTURE_FORMAT_R64G64B64A64_UINT = 119,
    TEXTURE_FORMAT_R64G64B64A64_SINT = 120,
    TEXTURE_FORMAT_R64G64B64A64_SFLOAT = 121,
    TEXTURE_FORMAT_B10G11R11_UFLOAT_PACK32 = 122,
    TEXTURE_FORMAT_E5B9G9R9_UFLOAT_PACK32 = 123,
    TEXTURE_FORMAT_D16_UNORM = 124,
    TEXTURE_FORMAT_X8_D24_UNORM_PACK32 = 125,
    TEXTURE_FORMAT_D32_SFLOAT = 126,
    TEXTURE_FORMAT_S8_UINT = 127,
    TEXTURE_FORMAT_D16_UNORM_S8_UINT = 128,
    TEXTURE_FORMAT_D24_UNORM_S8_UINT = 129,
    TEXTURE_FORMAT_D32_SFLOAT_S8_UINT = 130,
    TEXTURE_FORMAT_BC1_RGB_UNORM_BLOCK = 131,
    TEXTURE_FORMAT_BC1_RGB_SRGB_BLOCK = 132,
    TEXTURE_FORMAT_BC1_RGBA_UNORM_BLOCK = 133,
    TEXTURE_FORMAT_BC1_RGBA_SRGB_BLOCK = 134,
    TEXTURE_FORMAT_BC2_UNORM_BLOCK = 135,
    TEXTURE_FORMAT_BC2_SRGB_BLOCK = 136,
    TEXTURE_FORMAT_BC3_UNORM_BLOCK = 137,
    TEXTURE_FORMAT_BC3_SRGB_BLOCK = 138,
    TEXTURE_FORMAT_BC4_UNORM_BLOCK = 139,
    TEXTURE_FORMAT_BC4_SNORM_BLOCK = 140,
    TEXTURE_FORMAT_BC5_UNORM_BLOCK = 141,
    TEXTURE_FORMAT_BC5_SNORM_BLOCK = 142,
    TEXTURE_FORMAT_BC6H_UFLOAT_BLOCK = 143,
    TEXTURE_FORMAT_BC6H_SFLOAT_BLOCK = 144,
    TEXTURE_FORMAT_BC7_UNORM_BLOCK = 145,
    TEXTURE_FORMAT_BC7_SRGB_BLOCK = 146,
    TEXTURE_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = 147,
    TEXTURE_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = 148,
    TEXTURE_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = 149,
    TEXTURE_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = 150,
    TEXTURE_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = 151,
    TEXTURE_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = 152,
    TEXTURE_FORMAT_EAC_R11_UNORM_BLOCK = 153,
    TEXTURE_FORMAT_EAC_R11_SNORM_BLOCK = 154,
    TEXTURE_FORMAT_EAC_R11G11_UNORM_BLOCK = 155,
    TEXTURE_FORMAT_EAC_R11G11_SNORM_BLOCK = 156,
    TEXTURE_FORMAT_ASTC_4x4_UNORM_BLOCK = 157,
    TEXTURE_FORMAT_ASTC_4x4_SRGB_BLOCK = 158,
    TEXTURE_FORMAT_ASTC_5x4_UNORM_BLOCK = 159,
    TEXTURE_FORMAT_ASTC_5x4_SRGB_BLOCK = 160,
    TEXTURE_FORMAT_ASTC_5x5_UNORM_BLOCK = 161,
    TEXTURE_FORMAT_ASTC_5x5_SRGB_BLOCK = 162,
    TEXTURE_FORMAT_ASTC_6x5_UNORM_BLOCK = 163,
    TEXTURE_FORMAT_ASTC_6x5_SRGB_BLOCK = 164,
    TEXTURE_FORMAT_ASTC_6x6_UNORM_BLOCK = 165,
    TEXTURE_FORMAT_ASTC_6x6_SRGB_BLOCK = 166,
    TEXTURE_FORMAT_ASTC_8x5_UNORM_BLOCK = 167,
    TEXTURE_FORMAT_ASTC_8x5_SRGB_BLOCK = 168,
    TEXTURE_FORMAT_ASTC_8x6_UNORM_BLOCK = 169,
    TEXTURE_FORMAT_ASTC_8x6_SRGB_BLOCK = 170,
    TEXTURE_FORMAT_ASTC_8x8_UNORM_BLOCK = 171,
    TEXTURE_FORMAT_ASTC_8x8_SRGB_BLOCK = 172,
    TEXTURE_FORMAT_ASTC_10x5_UNORM_BLOCK = 173,
    TEXTURE_FORMAT_ASTC_10x5_SRGB_BLOCK = 174,
    TEXTURE_FORMAT_ASTC_10x6_UNORM_BLOCK = 175,
    TEXTURE_FORMAT_ASTC_10x6_SRGB_BLOCK = 176,
    TEXTURE_FORMAT_ASTC_10x8_UNORM_BLOCK = 177,
    TEXTURE_FORMAT_ASTC_10x8_SRGB_BLOCK = 178,
    TEXTURE_FORMAT_ASTC_10x10_UNORM_BLOCK = 179,
    TEXTURE_FORMAT_ASTC_10x10_SRGB_BLOCK = 180,
    TEXTURE_FORMAT_ASTC_12x10_UNORM_BLOCK = 181,
    TEXTURE_FORMAT_ASTC_12x10_SRGB_BLOCK = 182,
    TEXTURE_FORMAT_ASTC_12x12_UNORM_BLOCK = 183,
    TEXTURE_FORMAT_ASTC_12x12_SRGB_BLOCK = 184,
} TextureFormat;

/** @brief Represents the render API used in the backend. */
typedef enum RendererBackendAPI {
    /** @brief (SUPPORTED: DESKTOP) The Vulkan backend */
    RENDERER_BACKEND_API_VULKAN,
    /** @brief (UNSUPPORTED: APPLE) The Metal backend */
    RENDERER_BACKEND_API_METAL,
    /** @brief (UNSUPPORTED: WIN32) The DirectX11 backend */
    RENDERER_BACKEND_API_DIRECTX11,
    /** @brief (UNSUPPORTED: WIN32) The DirectX12 backend */
    RENDERER_BACKEND_API_DIRECTX12,
    /** @brief (UNSUPPORTED: DESKTOP) The OpenGL backend */
    RENDERER_BACKEND_API_OPENGL,
    /** @brief (UNSUPPORTED: SWITCH) The Deko3D backend */
    RENDERER_BACKEND_API_DEKO3D
} RendererBackendAPI;

/**
 * @brief A generic "interface" for the backend. The renderer backend
 * is what is responsible for making calls to the graphics API such as
 * Vulkan or Metal. Each of these should implement this interface.
 * The frontend only interacts via this structure and has no knowledge of
 * the way things actually work on the backend.
 */
typedef struct RendererBackend {
    u64 FrameNumber;
    RendererBackendAPI API;
	
    /**
     * @brief Initializes the backend.
     *
     * @param backend A pointer to the generic backend interface.
     * @returns True if initialized successfully; otherwise false.
     */
    b8 (*Init)(struct RendererBackend* backend);
	
    /**
     * @brief Shuts the renderer backend down.
     *
     * @param backend A pointer to the generic backend interface.
     */
    void (*Shutdown)(struct RendererBackend* backend);
	
    /**
     * @brief Handles window resizes.
     *
     * @param backend A pointer to the generic backend interface.
     * @param width The new window width.
     * @param height The new window height.
     */
    void (*Resized)(struct RendererBackend* backend, u16 width, u16 height);
	
	/**
* @brief Creates a GPU buffer.
* @param backend A pointer to the generic backend interface.
* @param size The size of the buffer to be created.
* @param usage The usage for the buffer.
* @returns A pointer to the created buffer if successful; otherwise NULL.
*/
	Buffer* (*BufferCreate)(struct RendererBackend* backend, u64 size, BufferUsage usage);
	
	/**
* @brief Destroys a GPU buffer.
* @param backend A pointer to the generic backend interface.
* @param buffer The buffer to destroy.
*/
	void (*BufferFree)(struct RendererBackend* backend, Buffer* buffer);
	
	/**
	 * @brief Performs setup routines required at the start of a frame.
	 * @note A false result does not necessarily indicate failure. It can also specify that
	 * the backend is simply not in a state capable of drawing a frame at the moment, and
	 * that it should be attempted again on the next loop. End frame does not need to (and
	 * should not) be called if this is the case.
	 * @param backend A pointer to the generic backend interface.
	 * @param delta_time The time in seconds since the last frame.
	 * @return True if successful; otherwise false.
	 */
	b8 (*BeginFrame)(struct RendererBackend* backend, f32 delta_time);
	
	/**
	 * @brief Performs routines required to draw a frame, such as presentation. Should only be called
	 * after a successful return of begin_frame.
	 *
	 * @param backend A pointer to the generic backend interface.
	 * @param delta_time The time in seconds since the last frame.
	 * @return True on success; otherwise false.
	 */
	b8 (*EndFrame)(struct RendererBackend* backend, f32 delta_time);
} RendererBackend;

#endif