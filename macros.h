#ifndef MACROS_H
#define MACROS_H

#define NEW(type, ...)                                                         \
  ({                                                                           \
    type _val;                                                                 \
    init_##type(&_val, __VA_ARGS__);                                           \
    _val;                                                                      \
  })

#define DELETE(var) {free_##typeof(var)(&var)};

#define CLEANUP(type) __attribute__((__cleanup__(free_##type)))

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(*arr))

#endif
