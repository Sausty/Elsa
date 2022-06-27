/**
 * @file Event.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains all logic pertaining to the memory tracking system.
 * @version 1.0
 * @date 2022-06-27
 */
#ifndef ELSA_MEM_TRACKER_H
#define ELSA_MEM_TRACKER_H

#include <Defines.h>

/** @brief Tags to indicate the usage of memory allocations made in this system. */
typedef enum MemoryTag {
	MEMORY_TAG_UNKNOWN = 0,
	MEMORY_TAG_DARRAY = 1,
	MEMORY_TAG_RENDERER = 2,
	MEMORY_TAG_HASHTABLE = 3,
	MEMORY_TAG_APP = 4,
	MEMORY_TAG_ENGINE_GENERAL = 5,
	MEMORY_TAG_MAX_TAGS
} MemoryTag;

/** 
* @brief Initializes the memory tracker system
* @returns True on success; otherwise false.
*/
ELSA_API b8 MemoryTrackerInit();

/** @brief Shuts down the memory tracker system */
ELSA_API void MemoryTrackerShutdown();

/**
* @brief Allocates a memory block from a certain tag.
* 
* @param size The size of the block to allocate.
* @param tag The tag used for the allocation.
* @returns A pointer to the allocated block.
*/
ELSA_API void* MemoryTrackerAlloc(u64 size, MemoryTag tag);

/**
* @brief Frees a memory block from a certain tag.
*
* @param block The block of memory to free.
* @param size The size of the memory block to free.
* @param tag The tag used for the allocation.
*/
ELSA_API void MemoryTrackerFree(void* block, u64 size, MemoryTag tag);

/**
* @brief Returns the allocation count of the provided memory tag.
*
* @param tag The memory tag whose allocation count to return.
* @returns The allocation count.
*/
ELSA_API u64 MemoryTrackerGetAllocationCount(MemoryTag tag);

/**
* @brief Returns the memory usage of the provided memory tag.
*
* @param tag The mmroy tag whose memory usage to return.
* @returns The memory usage.
*/
ELSA_API u64 MemoryTrackerGetUsage(MemoryTag tag);

#endif
