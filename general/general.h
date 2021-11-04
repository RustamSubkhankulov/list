#pragma once

#include "../logs/errors_and_logs.h"
#include "../logs/log_definitions.h"

#include "../list/list_config.h"

#ifdef GENERAL_LOGS

       #define general_log_report() \
               log_report()

#else

       #define general_log_report() ""

#endif


//===================================================================

#define my_recalloc(ptr, number, prev_number, size_of_elem) \
       _my_recalloc(ptr, number, prev_number, size_of_elem, \
                                                 LOG_ARGS)

#define clear_memory(base, num, size) \
       _clear_memory(base, num, size, LOG_ARGS)

#define is_memory_clear(base, num, size) \
       _is_memory_clear(base, num, size, LOG_ARGS)

#define get_hash(base, len) \
        get_hash_(base, len, LOG_ARGS)

//===================================================================

void* _my_recalloc(void* ptr, int number, int prev_number, size_t size_of_elem,
                                                                   LOG_PARAMS);

int _clear_memory(void* base, size_t num, size_t size, LOG_PARAMS);

int _is_memory_clear(void* base, size_t num, size_t size, LOG_PARAMS);

void ___System_Sleep(float _Duration);

int64_t get_hash_(void* void_base, unsigned int len, LOG_PARAMS);