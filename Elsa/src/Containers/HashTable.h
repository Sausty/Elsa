/**
 * @file HashTable.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains the hashtable implementation.
 * @version 1.0
 * @date 2022-06-26
 */
#ifndef ELSA_HASHTABLE_H
#define ELSA_HASHTABLE_H

#include <Defines.h>

/**
 * @brief Represents a simple hashtable. Members of this structure
 * should not be modified outside the functions associated with it.
 * 
 * For non-pointer types, table retains a copy of the value.For 
 * pointer types, make sure to use the _ptr setter and getter. Table
 * does not take ownership of pointers or associated memory allocations,
 * and should be managed externally.
 */
typedef struct HashTable {
    u64 ElementSize;
    u32 ElementCount;
    b8 IsPointerType;
    void* Memory;
} HashTable;

/**
 * @brief Creates a hashtable and stores it in out_hashtable.
 * 
 * @param element_size The size of each element in bytes.
 * @param element_count The maximum number of elements. Cannot be resized.
 * @param memory A pointer to hold a block of memory to be used. Internally allocated. Will be equal in size to element_size * element_count.
 * @param is_pointer_type Indicates if this hashtable will hold pointer types.
 * @param out_hashtable A pointer to a hashtable in which to hold relevant data.
 */
ELSA_API void HashTableCreate(u64 element_size, u32 element_count, b8 is_pointer_type, void* memory, HashTable* out_hashtable);

/**
 * @brief Destroys the provided hashtable. Does not release memory for pointer types.
 * 
 * @param table A pointer to the table to be destroyed.
 */
ELSA_API void HashTableDestroy(HashTable* table);

/**
 * @brief Stores a copy of the data in value in the provided hashtable. 
 * Only use for tables which were *NOT* created with is_pointer_type = true.
 * 
 * @param table A pointer to the table to get from. Required.
 * @param name The name of the entry to set. Required.
 * @param value The value to be set. Required.
 * @returns True, or false if a null pointer is passed.
 */
ELSA_API b8 HashTableSet(HashTable* table, const char* name, void** value);

/**
 * @brief Stores a pointer as provided in value in the hashtable.
 * Only use for tables which were created with is_pointer_type = true.
 * 
 * @param table A pointer to the table to get from. Required.
 * @param name The name of the entry to set. Required.
 * @param value A pointer value to be set. Can pass 0 to 'unset' an entry.
 * @returns True; or false if a null pointer is passed or if the entry is 0.
 */
ELSA_API b8 HashTableSetPointer(HashTable* table, const char* name, void** value);

/**
 * @brief Obtains a copy of data present in the hashtable.
 * Only use for tables which were *NOT* created with is_pointer_type = true.
 * 
 * @param table A pointer to the table to retrieved from. Required.
 * @param name The name of the entry to retrieved. Required.
 * @param value A pointer to store the retrieved value. Required.
 * @returns True; or false if a null pointer is passed.
 */
ELSA_API b8 HashTableGet(HashTable* table, const char* name, void* out_value);

/**
 * @brief Obtains a pointer to data present in the hashtable.
 * Only use for tables which were created with is_pointer_type = true.
 * 
 * @param table A pointer to the table to retrieved from. Required.
 * @param name The name of the entry to retrieved. Required.
 * @param value A pointer to store the retrieved value. Required.
 * @return True if retrieved successfully; false if a null pointer is passed or is the retrieved value is 0.
 */
ELSA_API b8 HashTableGetPointer(HashTable* table, const char* name, void** out_value);

/**
 * @brief Fills all entries in the hashtable with the given value.
 * Useful when non-existent names should return some default value.
 * Should not be used with pointer table types.
 * 
 * @param table A pointer to the table filled. Required.
 * @param value The value to be filled with. Required.
 * @return True if successful; otherwise false.
 */
ELSA_API b8 HashTableFill(HashTable* table, void* value);

#endif