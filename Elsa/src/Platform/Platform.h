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

#endif