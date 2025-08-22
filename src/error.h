#ifndef ALY_COMPILER_ERROR_H
#define ALY_COMPILER_ERROR_H

// TODO: Add file path, byte offset, etc.
typedef struct Error {
	enum ErrorType {
		ERROR_NONE = 0,
		ERROR_ARGUMENTS,
		ERROR_TYPE,
		ERROR_GENERIC,
		ERROR_SYNTAX,
		ERROR_TODO,
		ERROR_MAX,
	} type;
	char* msg;
} Error;

void print_error(Error err);

extern Error ok;

#define ERROR_CREATE(n, t, msg)                 \
  Error (n) = { (t), (msg) }

#define ERROR_PREP(n, t, message)               \
  (n).type = (t);                               \
  (n).msg = (message);

#ifndef _MSC_VER
#define ALY_NORETURN __attribute__((noreturn))
#define ALY_FORMAT(...) __attribute__((format(__VA_ARGS__)))
#define ALY_PRETTY_FUNCTION __PRETTY_FUNCTION__
#define ALY_LIKELY(x) __builtin_expect((x), 1)
#define ALY_UNLIKELY(x) __builtin_expect((x), 0)
#define ALY_PATH_SEPARATOR "/"
#else
#define ALY_NORETURN
#define ALY_FORMAT(...)
#define ALY_PRETTY_FUNCTION __FUNCSIG__
#define ALY_LIKELY(x) (x)
#define ALY_UNLIKELY(x) (x)
#define ALY_PATH_SEPARATOR "\\"
#endif

#define ALY_VA_FIRST(x, ...) x
#define ALY_VA_REST(x, ...) __VA_ARGS__
#define ALY_VA_REST_COMMA(x, ...) __VA_OPT__(,) __VA_ARGS__

ALY_NORETURN
ALY_FORMAT(printf, 1, 2)
void panic(const char* fmt, ...);

ALY_NORETURN
ALY_FORMAT(printf, 2, 3)
void panic_with_code(int code, const char* fmt, ...);

/// Used by ALY_ASSERT(). You probably don't want to use this directly.
ALY_NORETURN
ALY_FORMAT(printf, 5, 6)
void aly_assert_impl(
	const char* file,
	const char* func,
	int line,
	const char* condition,
	const char* fmt,
	...
);

/// Usage:
///   ALY_ASSERT(condition);
///   ALY_ASSERT(condition, "message", ...);
#define ALY_ASSERT(cond, ...)                        \
  do {                                                \
    if (ALY_UNLIKELY(!(cond))) {                     \
      aly_assert_impl(                               \
        __FILE__,                                     \
        ALY_PRETTY_FUNCTION,                         \
        __LINE__ ,                                    \
        #cond,                                        \
        /* First element of __VA_ARGS__ or NULL */    \
        ALY_VA_FIRST(__VA_ARGS__ __VA_OPT__(,) NULL) \
        /* Comma + rest of __VA_ARGS__ */             \
        ALY_VA_REST_COMMA(__VA_ARGS__)               \
      );                                              \
    }                                                 \
  } while (0)
#endif // ALY_COMPILER_ERROR_H