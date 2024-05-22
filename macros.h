#ifndef MACROS_H
#define MACROS_H

#define NEW(type, ...) \
  ({ \
  type _val; \
  Init##type(&_val, __VA_ARGS__); \
  _val;})

#define DELETE(var) {Delete##typeof(var)(&var)};

#define CLEANUP(func) __attribute__((__cleanup__(func)))

#define AUTODEL(type) __attribute__((__cleanup__(Delete##type)))

#define ARRSIZE(arr) (sizeof(arr) / sizeof(*arr))

#define MIN(a, b) (a < b ? a : b)

#define MAX(a, b) (a > b ? a : b)

#endif
