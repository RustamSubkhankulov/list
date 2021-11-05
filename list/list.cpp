#include <stdlib.h>

#include "list.h"
#include "../general/general.h"

static int graph_counter = 0;

//===================================================================

int _list_draw_graph(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    FILE* graph = fopen("list_graph.txt", "wb");

    fprintf(graph, "digraph G{\n");
    fprintf(graph, "rankdir=LR;\n");

    fprintf(graph, "{\n");
    fprintf(graph, "edge[color=white]\n");
    fprintf(graph, "node[shape=\"record\", style=\"rounded\"]\n");

    for (unsigned int counter = 0; counter < list->capacity; counter++) {

        fprintf(graph, "ELEMENT%u [label = \" index = %u | { data = " ELEM_SPEC " | <f0> next = %d } \" ];\n", counter, counter, list->data[counter], list->next[counter]);
        fprintf(graph, "ELEMENT%u -> ELEMENT%u\n", counter, counter + 1);
    }

    for (unsigned counter = 0; counter < list->size; counter++)  {

        if (list->next[counter] != -1 && list->next[counter] != 0) {

            fprintf(graph, "ELEMENT%u:<f0> -> ELEMENT%d [color = \"black\"]\n", counter, list->next[counter]);
        }
    }
    
    fprintf(graph, "{ rank = same;");

    for (unsigned counter = 0; counter < list->capacity; counter++) {
        
        fprintf(graph, " \" ELEMENT%u \"; ");
        fprintf(graph, "}\n");
    }

    fprintf(graph, "}\n");

    fprintf(graph, "\n}\n");

    system("dot list_graph.txt -Tpng -o list_graph.png");

    fclose(graph);

    graph_counter++;

    return 0;
}

//===================================================================

#ifdef LIST_HASH

static int _list_save_hash(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list->base_hash = get_hash(list, sizeof(List) 
                                 - 3 * sizeof(int64_t));

    list->data_hash =
           get_hash(list->data, sizeof(elem_t) * list->capacity);

    list->next_hash = 
           get_hash(list->next, sizeof(int) * list->capacity);

    return 0;
}

#endif

//===================================================================

#ifdef LIST_HASH

static int _list_hash_check(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int64_t base_hash = get_hash(list, sizeof(List) 
                                 - 3 * sizeof(int64_t));

    int64_t data_hash =
           get_hash(list->data, sizeof(elem_t) * list->capacity);

    int64_t next_hash = 
           get_hash(list->next, sizeof(int) * list->capacity);

    if (list->base_hash != base_hash) {

        error_report(LIST_INV_BASE_HASH);
        return 0;
    }
    
    if (list->data_hash != data_hash) {

        error_report(LIST_INV_DATA_HASH);
        return 0;
    }
    
    if (list->next_hash != next_hash) {

        error_report(LIST_INV_NEXT_HASH);
        return 0;
    }

    return 1;
}

#endif

//===================================================================

// static int _list_decrease(struct List* list, LOG_PARAMS) {

//     list_log_report();
//     LIST_POINTER_CHECK(list);

    // size_t prev_capacity = list->capacity;
    // list->capacity /= 2;
    
    // if (list->capacity < List_capacity)
    //     list->capacity = List_capacity;

    // void* new_data = my_recalloc(list->data, 
    //                              list->capacity, 
    //                              prev_capacity, 
    //                              sizeof(elem_t));
    // if (new_data == NULL) {

    //     error_report(CANNOT_ALLOCATE_MEM);
    //     return -1;
    // }

    // else 
    //     list->data = (elem_t*)new_data;

//     void* new_next = my_recalloc(list->next,
//                                  list->capacity,
//                                  prev_capacity,
//                                  sizeof(int));

//     if (new_next == NULL) {

//         error_report(CANNOT_ALLOCATE_MEM);
//         return -1;
//     }

//     int is_ok = list_validator(list);
//     if (is_ok == 0)
//         return -1;

//     return 0;
// }

//===================================================================

// static int _list_increase(struct List* list, LOG_PARAMS) {

//     list_log_report();
//     LIST_POINTER_CHECK(list);

//     size_t prev_capacity = list->capacity;
//     list->capacity *= 2;
    
//     if (list->capacity > List_capacity)
//         list->capacity = List_capacity;

//     void* new_data = my_recalloc(list->data, 
//                                  list->capacity, 
//                                  prev_capacity, 
//                                  sizeof(elem_t));

    // if (new_data == NULL) {

    //     error_report(CANNOT_ALLOCATE_MEM);
    //     return -1;
    // }

    // else 
    //     list->data = (elem_t*)new_data;

    // void* new_next = my_recalloc(list->next,
    //                              list->capacity,
    //                              prev_capacity,
    //                              sizeof(int));

    // if (new_next == NULL) {

    //     error_report(CANNOT_ALLOCATE_MEM);
    //     return -1;
    // }

//     int is_ok = list_validator(list);
//     if (is_ok == 0)
//         return -1;

//     return 0;
// }

//===================================================================

// static int _list_resize(struct List* list, LOG_PARAMS) {

//     list_log_report();
//     LIST_POINTER_CHECK(list);

//     if (list->size + 1 == list->capacity) {

//         int ret = list_increase(list);
//         if (ret == -1)
//             return -1;
//     }

//     if (list->size < (list->capacity / 4)
//      && list->capacity > List_capacity) {

//         int ret = list_decrease(list);
//         if (ret == -1)
//             return -1;
//     }

//     int is_ok = list_validator(list);
//     if (is_ok == 0)
//         return -1;

//     return 0;
// }  

//===================================================================

static int _list_clear_check(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_list_clear = is_memory_clear((void*)list, 
                                        sizeof(struct List), 
                                        sizeof(char));
                                    
    return is_list_clear;
}

//===================================================================

static int _list_poison_check(struct List* list, LOG_PARAMS) {
    
    list_log_report();
    LIST_POINTER_CHECK(list);

    for (long unsigned counter = 0; counter < sizeof(List); counter++) {

        if (*((unsigned char*)list + counter) != POISON_VALUE)
            return 0;
    }

    return 1;
}

//===================================================================

static int _list_poisoning(struct List* list, LOG_PARAMS) {
    
    list_log_report();
    LIST_POINTER_CHECK(list);

    for (long unsigned counter = 0; counter < sizeof(List); counter++) {

        *((char*)list + counter) = (char)POISON_VALUE;
    }

    return 0;
}

//===================================================================

static int _list_set_zero(struct List* list, LOG_PARAMS) {
    
    list_log_report();
    LIST_POINTER_CHECK(list);

    int clear_return = clear_memory((void*)list, 
                                    sizeof(List), 
                                    sizeof(char));

    if (clear_return == -1)
        return -1;

    return 0;
}

//===================================================================

static int _list_allocate_memory(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    elem_t* temp_data = (elem_t*)calloc(list->capacity, 
                                        sizeof(elem_t));

    if (temp_data == NULL)
        error_report(CANNOT_ALLOCATE_MEM);
    else 
        list->data = temp_data;

    int* next_temp = (int*)calloc(list->capacity, sizeof(int));

    if (next_temp == NULL)
        error_report(CANNOT_ALLOCATE_MEM);
    else    
        list->next = next_temp;

    return 0;
    
}

//===================================================================

static int _list_free_memory(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    if (list->data == NULL) {

        error_report(LIST_DATA_IS_NULL);
        return -1;
    }

    else
        free(list->data);

    if (list->next == NULL) {

        error_report(LIST_NEXT_IS_NULL);
        return -1;
    }
    
    else
        free(list->next);

    return 0;
}

//===================================================================

int _list_dtor(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_ok = list_validator(list);
    if(is_ok == 0)
        return -1;

    if (list->data == NULL) {

        error_report(LIST_DATA_IS_NULL);
        return -1;
    }

    if (list->next == NULL) {

        error_report(LIST_NEXT_IS_NULL);
        return -1;
    }

    int ret = list_free_memory(list);

    if (ret == -1)
        return -1;

    list_poisoning(list);

    return 0;
}

//===================================================================

static int _list_set_next_to_minus_one(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    for (long unsigned counter = 1;  counter < list->capacity; counter++) {

        list->next[counter] = -1;
    }

    list->next[0] = 0;
    
    return 0;
}

//===================================================================

int _list_ctor(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_poison = list_poison_check(list);
    int is_clear = list_clear_check(list);

    if (is_clear == 0 && is_poison == 0)
        error_report(LIST_UNPREPARED);

    if (is_poison == 1) {

        int ret = list_set_zero(list);

        if (ret == -1)
            return -1;
    }
    
    list->head = 0;
    list->tail = 0;

    if (List_capacity < list->capacity) {

        error_report(LIST_INV_MAX_CAPACITY);
        return -1;
    }

    list->capacity = List_capacity;
    list->size = 0;
    
    int ret = list_allocate_memory(list);
    if (ret == -1)
        return -1;

    list_set_next_to_minus_one(list);
    
    ret =  list_save_hash(list);
    if (ret == -1)
        return -1;

    int is_ok = list_validator(list);
    if(is_ok == 0)
        return -1;

    return 0;
}

//===================================================================

int _list_validator(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int err_val = 0;

    if (list_hash_check(list) == 0) {

        err_val++;
    }

    if  (list->data == NULL) {

        error_report(LIST_DATA_IS_NULL);
        err_val++;
    }

    if (list->next == NULL) {

        error_report(LIST_NEXT_IS_NULL);
        err_val++;
    }

    if (list->head > list->capacity) {

        error_report(LIST_INV_HEAD);
        err_val++;
    }

    if (list->tail > list->capacity) {

        error_report(LIST_INV_HEAD);
        err_val++;
    }

    if (list->head == list->tail && list->size > 1) {

        error_report(TAIL_EQUAL_HEAD);
        err_val++;
    }
    
    if (list->head == 0 && list->size != 0) {

        error_report(LIST_INV_HEAD);
        err_val++;
    }

    if (list->tail == 0 && list->size != 0) {

        error_report(LIST_INV_TAIL);
        err_val++;
    }

    if (list->next[list->tail] != 0) {

        error_report(TAIL_NEXT_IS_NOT_ZERO);
        err_val++;
    }

    if (list->size > list->capacity) {

        error_report(INV_LIST_SIZE);
        err_val++;
    }

    if (list->size > list->capacity) {

        error_report(SIZE_MORE_THAN_CAP);
        err_val++;
    }

    #ifdef LIST_DEBUG

        if (list != NULL) {
            int ret = list_dump(list, logs_file);
            
            if (ret == -1)
                return -1;
        }

    #endif

    if (err_val != 0) {

        fflush(logs_file);
        return 0;
    }

    return 1;
}

//===================================================================

static int _list_out(struct List* list, FILE* output, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    if (output == NULL) {

        error_report(INV_FILE_PTR);
        return -1;
    }

    if (list->data == NULL || list->next == NULL)
        return -1;

    fprintf(output, "_________");

    for (unsigned counter  = 0; counter < list->capacity; counter ++) {

        fprintf(output, "______");
    }
    fprintf(output, "\n");

    fprintf(output, "|       ");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|     ");
    }
    fprintf(output, "|\n");

    fprintf(output, "| Index ");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|%3u  ", counter);
    }
    fprintf(output, "|\n");

    fprintf(output, "|_______");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|_____");
    }
    fprintf(output, "|\n");

//=========================================================


    fprintf(output, "|       ");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|     ");
    }
    fprintf(output, "|\n");

    fprintf(output, "| Data  ");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|%3d  ", list->data[counter]);
    }
    fprintf(output, "|\n");

    fprintf(output, "|_______");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|_____");
    }
    fprintf(output, "|\n");    

//=========================================================

    fprintf(output, "|       ");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|     ");
    }
    fprintf(output, "|\n");

    fprintf(output, "| Next  ");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|%3d  ", list->next[counter]);
    }
    fprintf(output, "|\n");
    
    fprintf(output, "|_______");

    for (unsigned counter = 0; counter < list->capacity; counter++) {

        fprintf(output, "|_____");
    }
    fprintf(output, "|\n\n");

    return 0;
}

//===================================================================

int _list_dump(struct List* list, FILE* output, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    if (output == NULL) {
       
        error_report(INV_FILE_PTR);
        return -1;
    }

    fprintf(output, "Singly linked list structure. Type: %s. Address: <%p>\n", 
                                                          TYPE_NAME, list);

    fprintf(output, "List capacity : %lu\n", list->capacity);

    fprintf(output, "List size: %u\n", list->size);

    fprintf(output, "Data array address: <%p>\n", list->data);

    if (list->data == NULL)
        fprintf(output, "ERROR: NULL data array\n");

    fprintf(output, "Next element indexes array address: <%p>\n", list->next);
        
    if (list->next == NULL)    
        fprintf(output, "ERROR: NULL next index array\n");

    fprintf(output, "Head element: %u\n", list->head);

    if (list->head > list->capacity || (list->head == 0 && list->size != 0))
        fprintf(output, "ERROR: invalid head element\n");

    fprintf(output, "Tail element: %u\n", list->tail);

    if (list->tail > list->capacity || (list->tail == 0 && list->size != 0))

        fprintf(output, "ERROR: invalid tail element\n");

    if (list->head == list->tail && list->size > 1)
        fprintf(output, "ERROR: Tail equal to head while "
                                "size is mote than one\n");

    fprintf(output, "\n");


    int ret = list_out(list, output);
    if (ret == -1)            
        return -1;

    return 0;
}

//===================================================================

static int _list_push_first(struct List* list, elem_t value, int free, 
                                                           LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_ok = list_validator(list);
    if (is_ok == 0)
        return -1;

    if (list->head != 0 || list->tail != 0 || list->size != 0) {

        error_report(PUSH_FIRST_FALSE_CALL);
        return -1;
    }

    list->data[free] = value;
    list->next[free] = 0;

    list->head = (unsigned)free;
    list->tail = (unsigned)free;

    list->size++;
    
    int ret = list_save_hash(list);
    if (ret == -1)
        return -1;

    is_ok = list_validator(list);
    if (is_ok == 0)
        return -1;

    return 0;
}

//===================================================================

static elem_t _list_pop_last(struct List* list, int* err, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    if (list->head != list->tail || list->size != 1) {

        error_report(POP_LAST_FALSE_CALL);
        
        *err = -1;
        return -1;
    }

    int is_ok = list_validator(list);
    if (is_ok == 0) {

        *err = -1;
        return -1;
    }

    unsigned int last = list->tail;

    list->next[last] = -1;
    
    elem_t value = list->data[last];
    int ret = clear_memory(&list->data[last], 1, sizeof(elem_t));
    
    if (ret != 1) {

        *err = -1;
        return -1;
    }

    list->head = 0;
    list->tail = 0;

    list->size--;

    ret = list_save_hash(list);
    if (ret == -1)
        return -1;

    is_ok = list_validator(list);
    if (is_ok == 0) {

        *err = -1;
        return -1;
    }

    return value;
}

//===================================================================

static int _list_find_free(struct  List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    if (list->size == List_capacity) {

        error_report(LIST_OVERFLOW);
        return -1;
    }

    for (long unsigned counter = 0; counter < list->capacity; counter++) {

        if (list->next[counter] == -1)
            return (int)counter;
    }

    error_report(LIST_OVERFLOW);

    return -1;
}

//===================================================================

static int _list_push_check(struct List* list, unsigned int index,  
                                                       LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    if (index == 0 && list->size != 0) {

        error_report(LIST_PUSH_BY_ZERO);
        return 0;
    }

    if (index > (unsigned)list->capacity) {

        error_report(LIST_INVALID_INDEX);
        return 0;
    }

    if (list->next[index] == -1) {

        error_report(LIST_EMPTY_INDEX);
        return 0;
    }

    if (list->size == List_capacity - 1) {

        error_report(LIST_OVERFLOW);
        return 0;
    }

    return 1;
}

//===================================================================

int _list_push_after_index(struct List* list, unsigned int index, 
                                        elem_t value, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_ok = list_validator(list);
    if (is_ok == 0)
        return -1;

    is_ok = list_push_check(list, index);
    if (is_ok == 0)
        return -1;

    int free = list_find_free(list);

    if (free == -1)
        return -1;

    if (list->head == 0 && list->tail == 0 && list->size == 0) {

        int ret = list_push_first(list, value, free);
        if (ret == -1)
            return -1;

        return free;
    }

    list->data[free] = value;

    list->next[free] = list->next[index];
    list->next[index] = free;

    if (list->next[free] == 0) 
        list->tail = (unsigned)free;

    list->size++;

    int ret = list_save_hash(list);
    if (ret == -1)
        return -1;

    is_ok = list_validator(list);
    if (is_ok == 0)
        return -1;

    return free;
}

//===================================================================

static int _get_prev_element_index(struct List* list, unsigned int index, 
                                                              LOG_PARAMS) {
    list_log_report();
    LIST_POINTER_CHECK(list);

    if (index <= 0 || index > list->capacity) {

        error_report(LIST_INV_INDEX);
        return -1;
    }

    for (long unsigned counter = 0; counter < list->capacity; counter ++) {

        if (list->next[counter] == (int)index)
            return (int)counter;
    }
    return 0;
}

//===================================================================

static int _list_pop_check(struct List* list, unsigned int index,
                                                      LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

     if (list->size == 0) {

        error_report(LIST_UNDERFLOW);
        return 0;
    }

    if (index == 0) {

        error_report(LIST_POP_BY_ZERO);
        return 0;
    }

    if (list->next[index] == -1) {

        error_report(LIST_EMPTY_INDEX);
        return 0;
    }

    return 1;
}

//===================================================================

elem_t _list_pop_by_index(struct List* list, unsigned int index, 
                                           int* err, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_ok = list_validator(list);
    if (is_ok == 0) {

        *err = -1;
        return -1;
    }

    is_ok = list_pop_check(list, index);
    if (is_ok == 0) {

        *err = -1;
        return -1;
    }

    if (list->head == list->tail && list->size == 1) {

        elem_t value = list_pop_last(list, err);
        
        if (*err == -1)
            return -1;
        else
            return value;
    }

    int prev = get_prev_element_index(list, index);

    if (prev == -1)
        return -1;

    elem_t value = list->data[index];

    int ret = clear_memory(&list->data[index], 1, sizeof(elem_t));
    if (ret != 1)
        return -1;

    if (prev == 0) 
        list->head = (unsigned)list->next[index];

    else {

        list->next[prev] = list->next[index];
        
        if (list->next[index] == 0) 
            list->tail = (unsigned)prev;
    }

    list->next[index] = -1;
    list->size--;
    
    ret = list_save_hash(list);
    if (ret == -1)
        return -1;

    is_ok = list_validator(list);
    if (is_ok == 0) {

        *err = -1;
        return -1;
    }

    return value;
}

//===================================================================

int _list_push_back(struct List* list, elem_t value, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_ok = list_validator(list);
    if (is_ok == 0)
        return -1;

    if (list->size == List_capacity - 1) {

        error_report(LIST_OVERFLOW);
        return -1;
    }

    int free = list_find_free(list);

    if (free == -1)
        return -1;

    int ret = list_push_after_index(list, list->tail, value);
    if (ret == -1)
        return -1;

    return free;
}

//===================================================================

elem_t _list_pop_back(struct List* list, int* err, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_ok = list_validator(list);
    if (is_ok == 0) {

        *err = -1;
        return -1;
    }

    elem_t value = list_pop_by_index(list, list->tail, err);
    if (*err == -1)
        return -1;

    return value;
}

//===================================================================

int _list_pop_front(struct List* list, int* err, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_ok = list_validator(list);
    if (is_ok == 0) {

        *err = -1;
        return -1;
    }

    elem_t value = list_pop_by_index(list, list->head, err);
    if (*err == -1)
        return -1;

    is_ok = list_validator(list);
    if (is_ok == 0) {

        *err = -1;
        return -1;
    }
    
    return value;
}

//===================================================================

int _list_push_front(struct List* list, elem_t value, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int is_ok = list_validator(list);
    if (is_ok == 0) 
        return -1;

    if (list->size == List_capacity - 1) {

        error_report(LIST_OVERFLOW);
        return -1;
    }

    int free = list_find_free(list);

    if (free == -1)
        return -1;

    if (list->head == 0 && list->tail == 0 && list->size == 0) {

        int ret = list_push_first(list, value, free);
        if (ret == -1)
            return -1;

        return free;
    }

    list->data[free] = value;
    list->next[free] = (int)list->head;

    list->head = (unsigned)free;

    list->size++;

    int ret = list_save_hash(list);
    if (ret == -1)
        return -1;

    is_ok = list_validator(list);
    if (is_ok == 0) 
        return -1;

    return free;
}

//===================================================================
