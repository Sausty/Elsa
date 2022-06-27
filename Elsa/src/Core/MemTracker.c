#include "MemTracker.h"

#include <Platform/Platform.h>

typedef struct TagTracker {
	u8 Tag;
	u64 AllocationCount;
	u64 UsedMemory;
} TagTracker;

typedef struct MemTrackerInternal {
	TagTracker tags[MEMORY_TAG_MAX_TAGS];
} MemTrackerInternal;

static MemTrackerInternal mem;

b8 MemoryTrackerInit()
{
	for (i32 i = 0; i < MEMORY_TAG_MAX_TAGS; i++) {
		PlatformZeroMemory(&mem.tags[i], sizeof(TagTracker));
		
		mem.tags[i].Tag = (MemoryTag)i;
	}
	
	return true;
}

void MemoryTrackerShutdown()
{
	for (i32 i = 0; i < MEMORY_TAG_MAX_TAGS; i++) {
		PlatformZeroMemory(&mem.tags[i], sizeof(TagTracker));;
	}
}

void* MemoryTrackerAlloc(u64 size, MemoryTag tag)
{
	mem.tags[tag].AllocationCount++;
	mem.tags[tag].UsedMemory += size;
	
	return PlatformAlloc(size);
}

void MemoryTrackerFree(void* block, u64 size, MemoryTag tag)
{
	mem.tags[tag].AllocationCount--;
	mem.tags[tag].UsedMemory -= size;
	
	PlatformFree(block);
}

u64 MemoryTrackerGetAllocationCount(MemoryTag tag)
{
	return mem.tags[tag].AllocationCount;
}

u64 MemoryTrackerGetUsage(MemoryTag tag)
{
	return mem.tags[tag].UsedMemory;
}