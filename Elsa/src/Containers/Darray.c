#include "Darray.h"

#include <Platform/Platform.h>
#include <Core/Logger.h>

void* _Darray_Create(u64 length, u64 stride)
{
    u64 header_size = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 array_size = length * stride;
    u64* new_array = PlatformAlloc(header_size + array_size);
    PlatformSetMemory(new_array, 0, header_size + array_size);
    new_array[DARRAY_CAPACITY] = length;
    new_array[DARRAY_LENGTH] = 0;
    new_array[DARRAY_STRIDE] = stride;
    return (void*)(new_array + DARRAY_FIELD_LENGTH);
}

void _Darray_Destroy(void* array)
{
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    PlatformFree(header);
}

u64 _Darray_Field_Get(void* array, u64 field)
{
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    return header[field];
}

void _Darray_Field_Set(void* array, u64 field, u64 value)
{
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    header[field] = value;
}

void* _Darray_Resize(void* array)
{
    u64 length = Darray_Length(array);
    u64 stride = Darray_Stride(array);
    void* temp = _Darray_Create((DARRAY_RESIZE_FACTOR * Darray_Capacity(array)), stride);
    PlatformCopyMemory(temp, array, length * stride);

    _Darray_Field_Set(temp, DARRAY_LENGTH, length);
    _Darray_Destroy(array);
    return temp;
}

void* _Darray_Push(void* array, const void* value_ptr)
{
    u64 length = Darray_Length(array);
    u64 stride = Darray_Stride(array);
    if (length >= Darray_Capacity(array)) {
        array = _Darray_Resize(array);
    }

    u64 addr = (u64)array;
    addr += (length * stride);
    PlatformCopyMemory((void*)addr, value_ptr, stride);
    _Darray_Field_Set(array, DARRAY_LENGTH, length + 1);
    return array;
}

void _Darray_Pop(void* array, void* dest)
{
    u64 length = Darray_Length(array);
    u64 stride = Darray_Stride(array);
    u64 addr = (u64)array;
    addr += ((length - 1) * stride);
    PlatformCopyMemory(dest, (void*)addr, stride);
    _Darray_Field_Set(array, DARRAY_LENGTH, length - 1);
}

void* _Darray_Pop_At(void* array, u64 index, void* value_ptr)
{
    u64 length = Darray_Length(array);
    u64 stride = Darray_Stride(array);
    if (index >= length) {
        ELSA_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
        return array;
    }

    u64 addr = (u64)array;
    PlatformCopyMemory(value_ptr, (void*)(addr + (index * stride)), stride);

    if (index != length - 1) {
        PlatformCopyMemory(
            (void*)(addr + (index * stride)),
            (void*)(addr + ((index + 1) * stride)),
            stride * (length - index)
        );
    }

    _Darray_Field_Set(array, DARRAY_LENGTH, length - 1);
    return array;
}

void* _Darray_Insert_At(void* array, u64 index, void* value_ptr)
{
    u64 length = Darray_Length(array);
    u64 stride = Darray_Stride(array);
    if (index >= length) {
        ELSA_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
        return array;
    }
    if (length >= Darray_Capacity(array)) {
        array = _Darray_Resize(array);
    }

    u64 addr = (u64)array;

    if (index != length - 1) {
        PlatformCopyMemory(
            (void*)(addr + ((index + 1) * stride)),
            (void*)(addr + (index * stride)),
            stride * (length - index)
        );
    }

    PlatformCopyMemory((void*)(addr + (index * stride)), value_ptr, stride);

    _Darray_Field_Set(array, DARRAY_LENGTH, length + 1);
    return array;
}