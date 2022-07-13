#include "FileSystem.h"

#include <Core/Logger.h>
#include <Core/MemTracker.h>

#include <Platform/Platform.h>

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

b8 FileSystemExists(const char* path)
{
#ifdef _MSC_VER
	struct _stat buffer;
	return _stat(path, &buffer);
#else
	struct stat buffer;
	return stat(path, &buffer) == 0;
#endif
}

b8 FileSystemOpen(const char* path, FileModes mode, b8 binary, FileHandle* out_handle)
{
	out_handle->IsValid = false;
    out_handle->Handle = 0;
    const char* mode_str;
	
    if ((mode & FILE_MODE_READ) != 0 && (mode & FILE_MODE_WRITE) != 0) {
        mode_str = binary ? "w+b" : "w+";
    } else if ((mode & FILE_MODE_READ) != 0 && (mode & FILE_MODE_WRITE) == 0) {
        mode_str = binary ? "rb" : "r";
    } else if ((mode & FILE_MODE_READ) == 0 && (mode & FILE_MODE_WRITE) != 0) {
        mode_str = binary ? "wb" : "w";
    } else {
        ELSA_ERROR("Invalid mode passed while trying to open file: '%s'", path);
        return false;
    }
	
    // Attempt to open the file.
    FILE* file = fopen(path, mode_str);
    if (!file) {
        ELSA_ERROR("Error opening file: '%s'", path);
        return false;
    }
	
    out_handle->Handle = file;
    out_handle->IsValid = true;
	
    return true;
}

void FileSystemClose(FileHandle* out_handle)
{
	if (out_handle->Handle) {
        fclose((FILE*)out_handle->Handle);
        out_handle->Handle = 0;
        out_handle->IsValid = false;
    }
}

b8 FileSystemSize(FileHandle* handle, u64* out_size)
{
	if (handle->Handle) {
        fseek((FILE*)handle->Handle, 0, SEEK_END);
        *out_size = ftell((FILE*)handle->Handle);
        rewind((FILE*)handle->Handle);
        return true;
    }
    return false;
}

b8 FileSystemReadLine(FileHandle* handle, u64 max_length, char** line_buf, u64* out_line_length)
{
	if (handle->Handle && line_buf && out_line_length && max_length > 0) {
        char* buf = *line_buf;
        if (fgets(buf, max_length, (FILE*)handle->Handle) != 0) {
            *out_line_length = strlen(*line_buf);
            return true;
        }
    }
    return false;
}

b8 FileSystemWriteLine(FileHandle* handle, const char* text)
{
	if (handle->Handle) {
        i32 result = fputs(text, (FILE*)handle->Handle);
        if (result != EOF) {
            result = fputc('\n', (FILE*)handle->Handle);
        }
		
        fflush((FILE*)handle->Handle);
        return result != EOF;
    }
    return false;
}

b8 FileSystemRead(FileHandle* handle, u64 data_size, void* out_data, u64* out_bytes_read)
{
	if (handle->Handle && out_data) {
        *out_bytes_read = fread(out_data, 1, data_size, (FILE*)handle->Handle);
        if (*out_bytes_read != data_size) {
            return false;
        }
        return true;
    }
    return false;
}

u32* FileSystemReadSPIRV(FileHandle* handle, u64* out_size)
{
	long currentpos = ftell(handle->Handle);
	fseek(handle->Handle, 0, SEEK_END);
	long size = ftell(handle->Handle);
	fseek(handle->Handle, currentpos, SEEK_SET);
	
	u64 filesizepadded = (size % 4 == 0 ? size * 4 : (size + 1) * 4) / 4;
	
	u8* buffer = PlatformAlloc(filesizepadded);
	fread(buffer, size, sizeof(char), handle->Handle);
	*out_size = filesizepadded;
	return (u32*)buffer;
}

b8 FileSystemReadBytes(FileHandle* handle, u8* out_bytes, u64* out_bytes_read, b8 align)
{
	if (handle->Handle && out_bytes && out_bytes_read) {
        // File size
        u64 size = 0;
		u64 size_padded;
        if(!FileSystemSize(handle, &size)) {
            return false;
        }
		if (align) {
			size_padded = (size % 4 == 0 ? size * 4 : (size + 1) * 4) / 4;
			*out_bytes_read = size_padded;
			fread(out_bytes, 1, size, (FILE*)handle->Handle);
			return true;
		} else {
			*out_bytes_read = fread(out_bytes, 1, size, (FILE*)handle->Handle);
			return *out_bytes_read == size;
		}
    }
    return false;
}

b8 FileSystemReadAllText(FileHandle* handle, char* out_text, u64* out_bytes_read)
{
	if (handle->Handle && out_text && out_bytes_read) {
        // File size
        u64 size = 0;
        if(!FileSystemSize(handle, &size)) {
            return false;
        }
		
        *out_bytes_read = fread(out_text, 1, size, (FILE*)handle->Handle);
        return *out_bytes_read == size;
    }
    return false;
}

b8 FileSystemWrite(FileHandle* handle, u64 data_size, const void* data, u64* out_bytes_written)
{
	if (handle->Handle) {
        *out_bytes_written = fwrite(data, 1, data_size, (FILE*)handle->Handle);
        if (*out_bytes_written != data_size) {
            return false;
        }
        fflush((FILE*)handle->Handle);
        return true;
    }
    return false;
}