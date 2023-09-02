#pragma once 

#ifdef __GNUC__
	#define CAS(a_ptr, a_oldVal, a_newVal) __sync_bool_compare_and_swap(a_ptr, a_oldVal, a_newVal)
	#define AtomicAdd(a_ptr,a_count) __sync_fetch_and_add (a_ptr, a_count)
	#define AtomicSub(a_ptr,a_count) __sync_fetch_and_sub (a_ptr, a_count)
    #define AtomicOr(a_ptr, a_count) __sync_fetch_and_or(a_ptr, a_count)
    #define AtomicAnd(a_ptr, a_count) __sync_fetch_and_and(type *ptr, type value);
    #define AtomicXor(a_ptr, a_count) __sync_fetch_and_xor(type *ptr, type value);
    #define AtomicNand(a_ptr, a_count) __sync_fetch_and_nand(type *ptr, type value);

	#include <sched.h> // sched_yield()

#else
#include <Windows.h>
#ifdef _WIN64
	#define CAS(a_ptr, a_oldVal, a_newVal) (a_oldVal == InterlockedCompareExchange64(a_ptr, a_newVal, a_oldVal))
	#define sched_yield()	SwitchToThread()
	#define AtomicAdd(a_ptr, num)	InterlockedIncrement64(a_ptr)
	#define AtomicSub(a_ptr, num)	InterlockedDecrement64(a_ptr)
#else
	#define CAS(a_ptr, a_oldVal, a_newVal) (a_oldVal == InterlockedCompareExchange(a_ptr, a_newVal, a_oldVal))
	#define sched_yield()	SwitchToThread()
	#define AtomicAdd(a_ptr, num)	InterlockedIncrement(a_ptr)
	#define AtomicSub(a_ptr, num)	InterlockedDecrement(a_ptr)
#endif

#endif