#pragma once

#include "list.h"

//===================================================================

#define list_unit_tests(list) \
       _list_unit_tests(list, LOG_ARGS)

#define list_ctor_test(list) \
       _list_ctor_test(list, LOG_ARGS)

#define list_push_back_test(list) \
       _list_push_back_test(list, LOG_ARGS)

#define list_pop_back_test(list) \
       _list_pop_back_test(list, LOG_ARGS)

#define list_push_front_test(list) \
       _list_push_front_test(list, LOG_ARGS)

#define list_pop_front_test(list) \
       _list_pop_front_test(list, LOG_ARGS)

#define list_push_after_index_test(list) \
       _list_push_after_index_test(list, LOG_ARGS)

#define list_push_before_index_test(list) \
       _list_push_before_index_test(list, LOG_ARGS)

#define list_pop_by_index_test(list) \
       _list_pop_by_index_test(list, LOG_ARGS)

#define list_push_first_test(list) \
       _list_push_first_test(list, LOG_ARGS)

#define list_pop_last_test(list) \
       _list_pop_last_test(list, LOG_ARGS)

#define list_test_init(list) \
       _list_test_init(list, LOG_ARGS)

#define list_test_stop(list, err_val) \
       _list_test_stop(list, err_val, LOG_ARGS)

//==================================================================

#define dump_if_error(err_val) {                                    \
                                                                    \
    if (err_val != 0) {                                             \
                                                                    \
        int dump_ok = list_dump(list, logs_file);                   \
        if (dump_ok == -1)                                          \
            return -1;                                              \
    }                                                               \
}

//===================================================================

#define list_error(func_error_code, err_code, err_val_ptr) {        \
                                                                    \
    error_report(func_error_code);                                  \
    error_report(err_code);                                         \
    *err_val_ptr += 1;                                              \
}

//===================================================================

int _list_test_init(struct List* list, LOG_PARAMS);

int _list_test_stop(struct List* list, int err_val, LOG_PARAMS);

int _list_ctor_test(struct List* list, LOG_PARAMS);

int _list_pop_last_test(struct List* list, LOG_PARAMS);

int _list_push_first_test(struct List* list, LOG_PARAMS);

int _list_push_back_test(struct List* list, LOG_PARAMS);

int _list_pop_back_test(struct List* list, LOG_PARAMS);

int _list_push_front_test(struct List* list, LOG_PARAMS);

int _list_pop_front_test(struct List* list, LOG_PARAMS);

int _list_push_after_index_test(struct List* list, LOG_PARAMS);

int _list_push_before_index_test(struct List* list, LOG_PARAMS);

int _list_pop_by_index_test(struct List* list, LOG_PARAMS);

int _list_unit_tests(struct List* list, LOG_PARAMS);




