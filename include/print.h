#ifndef PRINT_H 
#define PRINT_H 

#include <stdio.h>

#define print(fmt, ...)                                               \
        do {                                                         \
                fprintf(stderr, "#%s %s: %d#\t" fmt,                 \
                       __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
        } while (0)


#endif /* PRINT_H */
