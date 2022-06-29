/**
 * @file Platform.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains structures and functions for interacting with
 * the file system.
 * @version 1.0
 * @date 2022-06-29
 */
#ifndef ELSA_FILESYSTEM_H
#define ELSA_FILESYSTEM_H

#include <Defines.h>

/** @brief Holds a handle to a file. */
typedef struct FileHandle {
	/** @brief Opaque handle to internal file handle. */
	void* Handle;
	/** @brief Indicates if this handle is valid. */
	b8 IsValid;
} FileHandle;

/** @brief File open modes. Can be combined. */
typedef enum FileModes {
	/** Read mode */
	FILE_MODE_READ = 0x1,
	/** Write mode */
	FILE_MODE_WRITE = 0x2
} FileModes;

/**
 * @brief Checks if a file with the given path exists.
 * @param path The path of the file to be checked.
 * @returns True if exists; otherwise false.
 */
ELSA_API b8 FileSystemExists(const char* path);

/** 
 * @brief Attempt to open file located at path.
 * @param path The path of the file to be opened.
 * @param mode Mode flags for the file when opened (read/write). See file_modes enum in filesystem.h.
 * @param binary Indicates if the file should be opened in binary mode.
 * @param out_handle A pointer to a file_handle structure which holds the handle information.
 * @returns True if opened successfully; otherwise false.
 */
ELSA_API b8 FileSystemOpen(const char* path, FileModes mode, b8 binary, FileHandle* out_handle);

/** 
 * @brief Closes the provided handle to a file.
 * @param handle A pointer to a file_handle structure which holds the handle to be closed.
 */
ELSA_API void FileSystemClose(FileHandle* out_handle);

/**
 * @brief Attempts to read the size of the file to which handle is attached.
 * 
 * @param handle The file handle.
 * @param out_size A pointer to hold the file size.
 * @return True on success; otherwise false. 
 */
ELSA_API b8 FileSystemSize(FileHandle* handle, u64* out_size);

/** 
 * @brief Reads up to a newline or EOF.
 * @param handle A pointer to a file_handle structure.
 * @param max_length The maximum length to be read from the line.
 * @param line_buf A pointer to a character array populated by this method. Must already be allocated.
 * @param out_line_length A pointer to hold the line length read from the file.
 * @returns True if successful; otherwise false.
 */
ELSA_API b8 FileSystemReadLine(FileHandle* handle, u64 max_length, char** line_buf, u64* out_line_length);

/** 
 * @brief Writes text to the provided file, appending a '\n' afterward.
 * @param handle A pointer to a file_handle structure.
 * @param text The text to be written.
 * @returns True if successful; otherwise false.
 */
ELSA_API b8 FileSystemWriteLine(FileHandle* handle, const char* text);

/** 
 * @brief Reads up to data_size bytes of data into out_bytes_read. 
 * Allocates *out_data, which must be freed by the caller.
 * @param handle A pointer to a file_handle structure.
 * @param data_size The number of bytes to read.
 * @param out_data A pointer to a block of memory to be populated by this method.
 * @param out_bytes_read A pointer to a number which will be populated with the number of bytes actually read from the file.
 * @returns True if successful; otherwise false.
 */
ELSA_API b8 FileSystemRead(FileHandle* handle, u64 data_size, void* out_data, u64* out_bytes_read);

/** 
 * @brief Reads all bytes of data into out_bytes. 
 * @param handle A pointer to a file_handle structure.
 * @param out_bytes A byte array which will be populated by this method.
 * @param out_bytes_read A pointer to a number which will be populated with the number of bytes actually read from the file.
 * @returns True if successful; otherwise false.
 */
ELSA_API b8 FileSystemReadBytes(FileHandle* handle, u8* out_bytes, u64* out_bytes_read);

/** 
 * @brief Reads all characters of data into out_text. 
 * @param handle A pointer to a file_handle structure.
 * @param out_text A character array which will be populated by this method.
 * @param out_bytes_read A pointer to a number which will be populated with the number of bytes actually read from the file.
 * @returns True if successful; otherwise false.
 */
ELSA_API b8 FileSystemReadAllText(FileHandle* handle, char* out_text, u64* out_bytes_read);

/** 
 * @brief Writes provided data to the file.
 * @param handle A pointer to a file_handle structure.
 * @param data_size The size of the data in bytes.
 * @param data The data to be written.
 * @param out_bytes_written A pointer to a number which will be populated with the number of bytes actually written to the file.
 * @returns True if successful; otherwise false.
 */
ELSA_API b8 FileSystemWrite(FileHandle* handle, u64 data_size, const void* data, u64* out_bytes_written);

#endif
