#include "Logger.h"

#include <Platform/Platform.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void LogOutput(LogLevel level, const char* message, ...)
{
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};
    b8 is_error = level < LOG_LEVEL_WARN;

    char out_message[32000];
    PlatformZeroMemory(out_message, sizeof(out_message));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[32000];
    sprintf(out_message2, "%s%s\n", level_strings[level], out_message);

    if (!is_error)
        PlatformConsoleWrite(out_message2, level);
    else
        PlatformConsoleWriteError(out_message2, level);
}