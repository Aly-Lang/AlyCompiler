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

#define ERROR_CREATE(n, t, msg)   \
	Error (n) = { (t), (msg) } 

#define ERROR_PREP(n, t, message)   \
	(n).type = (t);                  \
	(n).msg = (message);


#ifndef _MSC_VER
#define ALY_NORETURN __attribute__((noreturn))
#define ALY_FORMAT(...) __attribute__((format(__VA_ARGS__)))
#else
#define ALY_NORETURN
#endif


ALY_NORETURN
ALY_FORMAT(printf, 1, 2)
void panic(const char* fmt, ...);

ALY_NORETURN
ALY_FORMAT(printf, 2, 3)
void panic_with_code(int code, const char* fmt, ...);

#endif // ALY_COMPILER_ERROR_H