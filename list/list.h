#pragma once

#include "list_config.h"
#include "../logs/errors_and_logs.h"

struct List {

    elem_t* data;
    int* next;
    int* prev;

    unsigned int head;
    unsigned int tail;

    size_t capacity;
    unsigned int size;

    int is_linarized;

    #ifdef LIST_DEBUG

        struct List* self_ptr;

    #endif

    #ifdef LIST_HASH
       
       int64_t base_hash;

       int64_t data_hash;
       int64_t next_hash;
       int64_t prev_hash;

    #endif
};

#ifdef LIST_LOGS

    #define list_log_report() \
            log_report()

#else

    #define list_log_report() ""

#endif

//==================================================================

#define LIST_ARGC_CHECK(argc) {                                     \
                                                                    \
    if (argc != CMND_LINE_ARGS_NUMBER) {                            \
                                                                    \
        fprintf(stderr, "Invalid number of "                        \
                        "command line arguments\n");                \
        return -1;                                                  \
    }                                                               \
}

//==================================================================

#define LIST_POINTER_CHECK(list) {                                  \
                                                                    \
    if (list == NULL) {                                             \
                                                                    \
        error_report(INV_LIST_STRUCTURE_PTR);                       \
        return -1;                                                  \
    }                                                               \
}

//==================================================================

#define list_ctor(list) \
        _list_ctor(list, LOG_ARGS)

#define list_dtor(list) \
        _list_dtor(list, LOG_ARGS)

#define list_validator(list) \
        _list_validator(list, LOG_ARGS)

#define list_dump(list, output) \
        _list_dump(list, output, LOG_ARGS)

#define list_push_front(list, value) \
       _list_push_front(list, value, LOG_ARGS)

#define list_push_back(list, value) \
       _list_push_back(list, value, LOG_ARGS)  

#define list_pop_front(list, err) \
       _list_pop_front(list, err, LOG_ARGS)  

#define list_pop_back(list, err) \
       _list_pop_back(list, err, LOG_ARGS)    

#define list_push_after_index(list, index, value) \
       _list_push_after_index(list, index, value, LOG_ARGS)

#define list_pop_by_index(list, index, err) \
       _list_pop_by_index(list, index, err, LOG_ARGS)

#define get_prev_element_index(list, index) \
       _get_prev_element_index(list, index, LOG_ARGS)

#define list_show_by_index(list, index, err) \
       _list_show_by_index(list, index, err, LOG_ARGS)

#define list_set_next_to_minus_one(list) \
       _list_set_next_to_minus_one(list, LOG_ARGS)


#define list_clear_check(list) \
       _list_clear_check(list, LOG_ARGS)

#define list_poison_check(list) \
       _list_poison_check(list, LOG_ARGS)

#define list_poisoning(list) \
       _list_poisoning(list, LOG_ARGS)

#define list_set_zero(list) \
       _list_set_zero(list, LOG_ARGS)

#define list_allocate_memory(list) \
       _list_allocate_memory(list, LOG_ARGS)

#define list_free_memory(list) \
       _list_free_memory(list, LOG_ARGS)

#define list_find_free(list) \
       _list_find_free(list, LOG_ARGS)

#define list_push_check(list, index) \
       _list_push_check(list, index, LOG_ARGS)

#define list_pop_check(list, index) \
       _list_pop_check(list, index, LOG_ARGS)

#define list_push_first(list, value, free) \
       _list_push_first(list, value, free, LOG_ARGS)

#define list_pop_last(list, err) \
       _list_pop_last(list, err,  LOG_ARGS)

#define list_out(list, output) \
       _list_out(list, output, LOG_ARGS)

#define list_resize(list) \
       _list_resize(list, LOG_ARGS)

#define list_increase(list) \
       _list_increase(list, LOG_ARGS)

#define list_decrease(list) \
       _list_decrease(list, LOG_ARGS)

#define list_save_hash(list) \
       _list_save_hash(list, LOG_ARGS)

#define list_hash_check(list) \
       _list_hash_check(list, LOG_ARGS)

#define list_draw_graph(list) \
       _list_draw_graph(list, LOG_ARGS)

#define update_list_pointers_values(list) \
       _update_list_pointers_values(list, LOG_ARGS)

#define list_pointers_values_check(list) \
       _list_pointers_values_check(list, LOG_ARGS)

//===================================================================

int _list_ctor(struct List* list, LOG_PARAMS);

int _list_dtor(struct List* list, LOG_PARAMS);

int _list_validator(struct List* list, LOG_PARAMS);

int _list_dump(struct List* list, FILE* output, LOG_PARAMS);

int _list_draw_graph(struct List* list, LOG_PARAMS);

//===================================================================

int _list_push_front(struct List* list, elem_t value, LOG_PARAMS);

int _list_push_back(struct List* list, elem_t value, LOG_PARAMS);

elem_t _list_pop_front(struct List* list, int* err, LOG_PARAMS);

elem_t _list_pop_back(struct List* list, int* err, LOG_PARAMS);

int _list_push_after_index(struct List* list, unsigned int index, 
                                       elem_t value, LOG_PARAMS);

elem_t _list_pop_by_index(struct List* list, unsigned int index,  
                                           int* err, LOG_PARAMS);

//==================================================================

// elem_t _list_show_by_index(struct Sl_lis* list, unsigned int index, 
//                                                     int* err, LOG_PARAMS);

//==================================================================

//функции для изъятия логического порядка

