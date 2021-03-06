/**
 * @file Platform.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains the platform layer, or at least the interface to it.
 * Each platform should provide its own implementation of this in a .c file, and 
 * should be compiled exclusively of the rest.
 * @version 1.0
 * @date 2022-06-17
 */

#ifndef ELSA_PLATFORM_H
#define ELSA_PLATFORM_H

#include <Defines.h>
#include <ApplicationTypes.h>

struct VulkanContext;

#define PLATFORM_MAX_PATH 260

/**
 * @brief Performs startup routines within the platform layer. 
 * 
 * @param application_state The application state.
 * @return True on success; otherwise false.
 */
ELSA_API b8 PlatformInit(ApplicationState* application_state);

/**
 * @brief Shuts down the platform layer.
 */
ELSA_API void PlatformExit();

/**
 * @brief Performs any platform-specific gamepad polling.
 */
ELSA_API void PlatformUpdateGamepads();

/**
 * @brief Performs any platform-specific message pumping that is required
 * for windowing, etc.
 * 
 * @return True on success; otherwise false.
 */
ELSA_API b8 PlatformPumpMessages();

/**
 * @brief Performs a memory allocation from the host of given size.
 * 
 * @param size The size of the allocation.
 * @returns If succesful, a pointer to a block of allocated memory; otherwise 0.
 */
ELSA_API void* PlatformAlloc(u64 size);

/**
 * @brief Frees the given block.
 * 
 * @param block A pointer to the block of memory to be freed.
 */
ELSA_API void PlatformFree(void* block);

/**
 * @brief Zeroes out the provided memory block
 * 
 * @param block A pointer to the block of memory to be zeroed out.
 * @param size The size in bytes to zero out.
 */
ELSA_API void PlatformZeroMemory(void* block, u64 size);

/**
 * @brief Sets the bytes of memory located at dest to value over the given size.
 * 
 * @param dest A pointer to the destination block of memory to be set.
 * @param value The value to be set.
 * @param size The size in bytes to copy over to.
 */
ELSA_API void PlatformSetMemory(void* block, i32 value, u64 size);

/**
 * @brief Performs a copy of the memory at source to dest of the given size.
 * 
 * @param dest A pointer to the destination block of memory to copy to.
 * @param source A pointer to the source block of memory to copy from.
 * @param size The amount of memory in bytes to be copied over.
 */
ELSA_API void PlatformCopyMemory(void* dest, const void* source, u64 size);

/**
 * @brief Moves a block of memory from one location to another.
 * 
 * @param dest A pointer to the starting address of the move destination.
 * @param source A pointer to the starting address of the block of memory to be moved.
 * @param size The size of the block of memory to move, in bytes.
 */
ELSA_API void PlatformMoveMemory(void* dest, const void* source, u64 size);

/**
 * @brief Performs platform-specific printing to the console of the given 
 * message and colour code (if supported).
 * 
 * @param message The message to be printed.
 * @param colour The colour to print the text in (if supported).
 */
ELSA_API void PlatformConsoleWrite(const char* message, u8 colour);

/**
 * @brief Performs platform-specific printing to the error console of the given 
 * message and colour code (if supported).
 * 
 * @param message The message to be printed.
 * @param colour The colour to print the text in (if supported).
 */
ELSA_API void PlatformConsoleWriteError(const char* message, u8 colour);

/**
 * @brief Gets an opaque pointer of the window view. HWND for Windows, CAMetalLayer* for MacOS.
 * @returns The pointer of the window view.
 */
ELSA_API void* PlatformGetWindowView();

/**
* @brief Appends the names of all the files present in the given directory.
* @param directory The directory to scan.
* @param files_darray A pointer to the array of the filenames. Must be a darray.
*/
ELSA_API void PlatformGetDirectoryFiles(const char* directory, char*** files_darray);

/**
* @brief Returns if the given directory exists.
* @param directory The directory to check.
* @returns True if it exists; otherwise false.
*/
ELSA_API b8 PlatformDirectoryExists(const char* directory);

/**
* @brief Creates a file.
* @param path The path of the file.
*/
ELSA_API void PlatformCreateFile(const char* path);

/**
* @brief Creates a directory.
* @param path The path of the directory.
*/
ELSA_API void PlatformCreateDirectory(const char* path);

/**
 * @brief Appends the names of required extensions for this platform to
 * the names_darray, which should be created and passed in.
 * @param names_darray A pointer to the array names of required extension names. Must be a darray
 * as this function adds names to the array.
 */
ELSA_API void PlatformGetRequiredExtensionNames(const char*** names_darray);

/**
 * @brief Creates and assigns a surface to the given context.
 * 
 * @param context A pointer to the Vulkan context.
 * @returns True on success; otherwise false.
 */
ELSA_API b8 PlatformCreateVulkanSurface(struct VulkanContext* context);

#endif