#include "env_memory.hpp"
#include <stdio.h>
#include <cstdlib>


void *address = nullptr;
void initialize_global(int size) {
    address = (void*)malloc(size);
}

void deinitialize_global() {
    free(address);
}

void* allocate_global(uint8_t offset) {
    return address + offset;
}

