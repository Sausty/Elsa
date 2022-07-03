/**
 * @file Asserts.h
 * @author Milo Heinrich (MikuoH15TH@gmail.com)
 * @brief This file contains assertion functions to be used throughout
 * the codebase.
 * @version 1.0
 * @date 2022-06-29
 */
#ifndef ELSA_ASSERTS_H
#define ELSA_ASSERTS_H

#include <Defines.h>

#define ELSA_ASSERTIONS_ENABLED

#ifdef ELSA_ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
/** @brief Causes a debug breakpoint to be hit. */
#define ELSA_DBG_BREAK() __debugbreak()
#else
/** @brief Causes a debug breakpoint to be hit. */
#define ELSA_DBG_BREAK() __builint_trap()
#endif

/**
 * @brief Reports an assertion failure. Note that this is not the assertion itself,
 * just a reporting of an assertion failure that has already occurred.
 * @param expression The expression to be reported.
 * @param message A custom message to be reported, if provided.
 * @param file The path and name of the file containing the expression.
 * @param line The line number in the file where the assertion failure occurred.
 */
ELSA_API void ReportAssertionFailure(const char* expression, const char* message, const char* file, i32 line);

/**
 * @brief Asserts the provided expression to be true, and logs a failure if not.
 * Also triggers a breakpoint if debugging.
 * @param expr The expression to be evaluated.
 */
#define ELSA_ASSERT(expr)                                                \
{                                                                    \
if (expr) {                                                      \
} else {                                                         \
ReportAssertionFailure(#expr, "", __FILE__, __LINE__);       \
ELSA_DBG_BREAK();                                            \
}                                                                \
}

/**
 * @brief Asserts the provided expression to be true, and logs a failure if not.
 * Allows the user to specify a message to accompany the failure. 
 * Also triggers a breakpoint if debugging.
 * @param expr The expression to be evaluated.
 * @param message The message to be reported along with the assertion failure.
 */
#define ELSA_ASSERT_MESSAGE(expr, message)                                        \
{                                                                             \
if (expr) {                                                               \
} else {                                                                  \
ReportAssertionFailure(#expr, message, __FILE__, __LINE__);           \
ELSA_DBG_BREAK();                                                     \
}                                                                         \
}

#else

#define ELSA_ASSERT(expr)
#define ELSA_ASSERT_MESSAGE(expr, message)

#endif

#endif
