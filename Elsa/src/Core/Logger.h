/**
 * @file Logger.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains structures and logic pertaining to the logging system.
 * @version 1.0
 * @date 2022-06-17
 */

#ifndef ELSA_LOGGER_H
#define ELSA_LOGGER_H

#include <Defines.h>

/** @brief Indicates if warning level logging is enabled. */
#define LOG_WARN_ENABLED 1
/** @brief Indicates if info level logging is enabled. */
#define LOG_INFO_ENABLED 1
/** @brief Indicates if debug level logging is enabled. */
#define LOG_DEBUG_ENABLED 1
/** @brief Indicates if trace level logging is enabled. */
#define LOG_TRACE_ENABLED 1

#if ELSA_RELEASE == 1
    #define LOG_DEBUG_ENABLED 0
    #define LOG_TRACE_ENABLED 0
#endif

/** @brief Represents levels of logging */
typedef enum LogLevel {
    /** @brief Fatal log level, should be used to stop the application when hit. */
    LOG_LEVEL_FATAL = 0,
    /** @brief Error log level, should be used to indicate critical runtime problems that cause the application to run improperly or not at all. */
    LOG_LEVEL_ERROR = 1,
    /** @brief Warning log level, should be used to indicate non-critial problems with the application that cause it to run suboptimally. */
    LOG_LEVEL_WARN = 2,
    /** @brief Info log level, should be used for non-erronuous informational purposes. */
    LOG_LEVEL_INFO = 3,
    /** @brief Debug log level, should be used for debugging purposes. */
    LOG_LEVEL_DEBUG = 4,
    /** @brief Trace log level, should be used for verbose debugging purposes. */
    LOG_LEVEL_TRACE = 5
} LogLevel;

/**
 * @brief Outputs logging at the given level.
 * @param level The log level to use.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
ELSA_API void LogOutput(LogLevel level, const char* message, ...);

/** 
 * @brief Logs a fatal-level message. Should be used to stop the application when hit.
 * @param message The message to be logged. Can be a format string for additional parameters.
 * @param ... Additional parameters to be logged.
 */
#define ELSA_FATAL(message, ...) LogOutput(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef ELSA_ERROR
/** 
 * @brief Logs an error-level message. Should be used to indicate critical runtime problems 
 * that cause the application to run improperly or not at all.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_ERROR(message, ...) LogOutput(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
/** 
 * @brief Logs a warning-level message. Should be used to indicate non-critial problems with 
 * the application that cause it to run suboptimally.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_WARN(message, ...) LogOutput(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
/** 
 * @brief Logs a warning-level message. Should be used to indicate non-critial problems with 
 * the application that cause it to run suboptimally. Does nothing when LOG_WARN_ENABLED != 1
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
/** 
 * @brief Logs an info-level message. Should be used for non-erronuous informational purposes.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_INFO(message, ...) LogOutput(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
/** 
 * @brief Logs an info-level message. Should be used for non-erronuous informational purposes.
 * Does nothing when LOG_INFO_ENABLED != 1
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
/** 
 * @brief Logs a debug-level message. Should be used for debugging purposes.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_DEBUG(message, ...) LogOutput(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
/** 
 * @brief Logs a debug-level message. Should be used for debugging purposes.
 * Does nothing when LOG_DEBUG_ENABLED != 1
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
/** 
 * @brief Logs a trace-level message. Should be used for verbose debugging purposes.
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_TRACE(message, ...) LogOutput(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
/** 
 * @brief Logs a trace-level message. Should be used for verbose debugging purposes.
 * Does nothing when LOG_TRACE_ENABLED != 1
 * @param message The message to be logged.
 * @param ... Any formatted data that should be included in the log entry.
 */
#define ELSA_TRACE(message, ...)
#endif

#endif