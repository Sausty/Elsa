#include "HashTable.h"

#include <Core/Logger.h>
#include <Platform/Platform.h>

u64 HashName(const char* name, u32 element_count) {
    // A multipler to use when generating a hash. Prime to hopefully avoid collisions.
    static const u64 multiplier = 97;

    unsigned const char* us;
    u64 hash = 0;

    for (us = (unsigned const char*)name; *us; us++) {
        hash = hash * multiplier + *us;
    }

    // Mod it against the size of the table.
    hash %= element_count;

    return hash;
}

void HashTableCreate(u64 element_size, u32 element_count, b8 is_pointer_type, void* memory, HashTable* out_hashtable)
{
    if (!memory || !out_hashtable) {
        ELSA_ERROR("HashTableCreate failed! Pointer to memory and out_hashtable are required.");
        return;
    }
    if (!element_count || !element_size) {
        ELSA_ERROR("element_size and element_count must be a positive non-zero value.");
        return;
    }

    out_hashtable->Memory = memory;
    out_hashtable->ElementCount = element_count;
    out_hashtable->ElementSize = element_size;
    out_hashtable->IsPointerType = is_pointer_type;
    PlatformZeroMemory(out_hashtable->Memory, element_size * element_count);
}

void HashTableDestroy(HashTable* table)
{
    if (table) {
        PlatformZeroMemory(table, sizeof(HashTable));
    }
}

b8 HashTableSet(HashTable* table, const char* name, void** value)
{
    if (!table || !name || !value) {
        ELSA_ERROR("HashTableSet requires table, name and value to exist.");
        return false;
    }
    if (table->IsPointerType) {
        ELSA_ERROR("HashTableSet should not be used with tables that have pointer types. Use HashTableSetPointer instead.");
        return false;
    }

    u64 hash = HashName(name, table->ElementCount);
    PlatformCopyMemory(table->Memory + (table->ElementSize * hash), value, table->ElementSize);
    return true;
}

b8 HashTableSetPointer(HashTable* table, const char* name, void** value)
{
    if (!table || !name || !value) {
        ELSA_ERROR("HashTableSetPointer requires table, name and value to exist.");
        return false;
    }
    if (!table->IsPointerType) {
        ELSA_ERROR("HashTableSetPointer should not be used with tables that do not have pointer types. Use HashTableSet instead.");
        return false;
    }

    u64 hash = HashName(name, table->ElementCount);
    ((void**)table->Memory)[hash] = value ? *value : 0;
    return true;
}

b8 HashTableGet(HashTable* table, const char* name, void* out_value)
{
    if (!table || !name || !out_value) {
        ELSA_ERROR("HashTableGet requires table, name and out_value to exist.");
        return false;
    }
    if (table->IsPointerType) {
        ELSA_ERROR("HashTableGet should not be used with tables that have pointer types. Use HashTableGetPointer instead.");
        return false;
    }

    u64 hash = HashName(name, table->ElementCount);
    PlatformCopyMemory(out_value, table->Memory + (table->ElementSize * hash), table->ElementSize);
    return true;
}

b8 HashTableGetPointer(HashTable* table, const char* name, void** out_value)
{
    if (!table || !name || !out_value) {
        ELSA_ERROR("HashTableGetPointer requires table, name and out_value to exist.");
        return false;
    }
    if (!table->IsPointerType) {
        ELSA_ERROR("HashTableGetPointer should not be used with tables that do not have pointer types. Use HashTableGet instead.");
        return false;
    }

    u64 hash = HashName(name, table->ElementCount);
    *out_value = ((void**)table->Memory)[hash];
    return out_value != 0;
}

b8 HashTableFill(HashTable* table, void* value)
{
    if (!table || !value) {
        ELSA_WARN("HashTableFill requires table and value to exist.");
        return false;
    }
    if (table->IsPointerType) {
        ELSA_ERROR("HashTableFill should not be used with tables that have pointer types.");
        return false;
    }

    for (u32 i = 0; i < table->ElementCount; ++i) {
        PlatformCopyMemory(table->Memory + (table->ElementSize * i), value, table->ElementSize);
    }

    return true;
}