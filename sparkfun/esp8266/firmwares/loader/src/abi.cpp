#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "ets_sys.h"
    #include "os_type.h"
    #include "osapi.h"
    #include "mem.h"
    #include "user_interface.h"
}

extern "C" void abort() {
    while(1) {
    }
}

void *operator new(size_t size) {
    return os_malloc(size);
}

void *operator new[](size_t size) {
    return os_malloc(size);
}

void operator delete(void * ptr) {
    os_free(ptr);
}

void operator delete[](void * ptr) {
    os_free(ptr);
}

extern "C" void __cxa_pure_virtual(void) __attribute__ ((__noreturn__));
extern "C" void __cxa_deleted_virtual(void) __attribute__ ((__noreturn__));

void __cxa_pure_virtual(void) {
    abort();
}

void __cxa_deleted_virtual(void) {
    abort();
}

namespace std {
void __throw_bad_function_call() {
    abort();
}
}
