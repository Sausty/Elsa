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

/** @brief Represents the render API used in the backend. */
typedef enum RendererBackendAPI {
    /** @brief (SUPPORTED: DESKTOP) The Vulkan backend */
    RENDERER_BACKEND_API_VULKAN,
    /** @brief (SUPPORTED: APPLE) The Metal backend */
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