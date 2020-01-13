#ifndef __MEM_UTILS_HPP
#define __MEM_UTILS_HPP
#include <stdint.h>
void* allocate_global(uint8_t offset);
void initialize_global(int size);
void deinitialize_global();
#endif