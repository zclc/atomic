#pragma once

int atomic_add(int *ptr, int count){
    int old;
    __asm__ volatile(
        "lock; xaddl %2, %1"
        : "=a"(old)
        : "m" (*ptr), "a"(count)
        : "cc", "memory"
    );
    return old;
}

int atomic_cas(int *ptr, int expected, int new_value) {
    int result;
    asm volatile (
        "lock; cmpxchgl %2, %1" // % AT&T 格式 %1与
        : "=a" (result), "=m" (*ptr)
        : "r" (new_value), "m" (*ptr), "0" (expected)
        : "memory"
    );
    return result;
}