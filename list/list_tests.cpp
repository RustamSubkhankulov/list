#include "list_tests.h"

//===================================================================

int _list_test_init(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list_ctor(list);

    return 0;
}

//===================================================================

int _list_test_stop(struct List* list, int err_val, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    if (err_val != 0) {

        int dump_ok = list_dump(list, logs_file);
        if (dump_ok == -1)
            return -1;
    }

    list_dtor(list);

    return 0;
}

//===================================================================

int _list_ctor_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int err_val = 0;

    int ret = list_ctor(list);
    if (ret == -1)
        err_val++;

    if (list->head != 0) 
        list_error(LIST_CTOR_TEST_FAILED, 
                   LIST_INV_HEAD, &err_val);

    if (list->tail != 0) 
        list_error(LIST_CTOR_TEST_FAILED, 
                   LIST_INV_TAIL, &err_val);

    if (list->free != 1) 
        list_error(LIST_CTOR_TEST_FAILED, 
                   LIST_INV_FREE, &err_val);

    if (list->is_linearized != 1) 
        list_error(LIST_CTOR_TEST_FAILED, 
                   INV_IS_LINEARIZED_VALUE, &err_val);
            
    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================


int _list_pop_last_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int err_val = 0;
    list_test_init(list);

    elem_t value = 0;
    int value_pos = 0;

    int free = list_get_free(list);
    value_pos = list_push_first(list, value, free);

    elem_t return_value = list_pop_last(list, &err_val);
    if (err_val == -1)
        err_val++;

    if (return_value != value) 

        list_error(LIST_POP_LAST_TEST_FAILED, 
                   LIST_POP_INV_RET_VALUE, &err_val);

    if (list->head != 0) 

        list_error(LIST_POP_LAST_TEST_FAILED, 
                   LIST_INV_HEAD, &err_val);

    if (list->tail != 0) 

        list_error(LIST_POP_LAST_TEST_FAILED, 
                   LIST_INV_TAIL, &err_val);

    if (list->size != 0) 

        list_error(LIST_POP_LAST_TEST_FAILED, 
                   LIST_INV_SIZE, &err_val);

    if (list->free != (unsigned)value_pos) 

        list_error(LIST_POP_LAST_TEST_FAILED, 
                   LIST_INV_FREE, &err_val);

    if (list->prev[value_pos] != -1) 

        list_error(LIST_POP_LAST_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_push_first_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    int err_val = 0;
    list_test_init(list);

    int free = list_get_free(list);

    elem_t value = 10;
    int value_pos = 0;

    value_pos = list_push_first(list, value, free);
    if (value_pos == -1)
        return -1;

    if (list->data[value_pos] != value) 

        list_error(LIST_PUSH_FIRST_TEST_FAILED, 
                   LIST_DATA_IS_EMPTY, &err_val);

    if (list->prev[value_pos] != 0) 

        list_error(LIST_PUSH_FIRST_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    if (list->next[value_pos] != 0) 

        list_error(LIST_PUSH_FIRST_TEST_FAILED, 
                   LIST_INV_NEXT, &err_val);

    if (list->tail != (unsigned)value_pos) 

        list_error(LIST_PUSH_FIRST_TEST_FAILED, 
                   LIST_INV_TAIL, &err_val);

    if (list->head != (unsigned)value_pos) 

        list_error(LIST_PUSH_FIRST_TEST_FAILED, 
                   LIST_INV_HEAD, &err_val);

    if (list->size != 1) 

        list_error(LIST_PUSH_FIRST_TEST_FAILED, 
                   LIST_DATA_IS_EMPTY, &err_val);

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_push_back_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list_test_init(list);

    elem_t value = 10;
    int free = list_get_free(list);
    int pos_prev = list_push_first(list, value, free);

    size_t prev_size = list->size;
    int err_val = 0;


    int value_pos = list_push_back(list, value);
    if (value_pos == -1)
        err_val++;

    if (list->tail != (unsigned)value_pos) 

        list_error(LIST_PUSH_BACK_TEST_FAILED, 
                   LIST_INV_TAIL, &err_val);

    if (list->data[value_pos] != value) 

        list_error(LIST_PUSH_BACK_TEST_FAILED, 
                   LIST_INV_DATA, &err_val);

    if (list->prev[value_pos] != pos_prev) 

        list_error(LIST_PUSH_BACK_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    if (list->next[value_pos] != 0) 

        list_error(LIST_PUSH_BACK_TEST_FAILED, 
                   LIST_INV_TAIL_NEXT, &err_val);

    if (list->size != prev_size + 1) 

        list_error(LIST_PUSH_BACK_TEST_FAILED, 
                   LIST_INV_SIZE, &err_val);

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_pop_back_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list_test_init(list);

    elem_t value = 10;
    int prev_pos  = list_push_back(list, value);
    int value_pos = list_push_back(list, value);

    size_t prev_size = list->size;
    int err_val = 0;

    elem_t returning_value = list_pop_back(list, &err_val);
    if (err_val == -1)
        err_val = 1;

    if (returning_value != value) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_POP_INV_RET_VALUE, &err_val);

    if (list->tail != (unsigned)prev_pos) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_TAIL, &err_val);

    if (list->next[prev_pos] != 0) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_TAIL_NEXT, &err_val);

    if (list->prev[value_pos] != -1) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_PREV_FOR_FREE_ELEM, &err_val);

    if (list->free != (unsigned)value_pos) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_FREE, &err_val);

    if (list->size != prev_size - 1) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_SIZE, &err_val);

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_push_front_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list_test_init(list);

    elem_t value = 10;
    int prev_pos  = list_push_back(list, value);

    size_t prev_size = list->size;
    int err_val = 0;

    int value_pos = list_push_front(list, value);
    if (value_pos == -1)
        err_val++;
    
    if (list->data[value_pos] != value) 

        list_error(LIST_PUSH_FRONT_TEST_FAILED, 
                   LIST_INV_DATA, &err_val);

    if (list->head != (unsigned)value_pos) 

        list_error(LIST_PUSH_FRONT_TEST_FAILED, 
                   LIST_INV_HEAD, &err_val);

    if (list->prev[value_pos] != 0) 

        list_error(LIST_PUSH_FRONT_TEST_FAILED, 
                   LIST_INV_HEAD_PREV, &err_val);

    if (list->next[value_pos] != prev_pos) 

        list_error(LIST_PUSH_FRONT_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    if (list->size != prev_size + 1) 

        list_error(LIST_PUSH_FRONT_TEST_FAILED,
                   LIST_INV_SIZE, &err_val)

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_pop_front_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list_test_init(list);

    elem_t value = 10;
    int prev_pos  = list_push_back (list, value);
    int value_pos = list_push_front(list, value);

    size_t prev_size = list->size;
    int err_val = 0;

    elem_t returning_value = list_pop_front(list, &err_val);
    if (err_val == -1)
        err_val = 1;

    if (returning_value != value) 

        list_error(LIST_POP_FRONT_TEST_FAILED, 
                   LIST_POP_INV_RET_VALUE, &err_val);

    if (list->head != (unsigned)prev_pos) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_HEAD, &err_val);

    if (list->prev[value_pos] != -1) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_PREV_FOR_FREE_ELEM, &err_val);

    if (list->free != (unsigned)value_pos) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_FREE, &err_val);

    if (list->size != prev_size - 1) 

        list_error(LIST_POP_BACK_TEST_FAILED, 
                   LIST_INV_SIZE, &err_val);

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_push_after_index_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list_test_init(list);

    elem_t value = 10;
    int pos_1 = list_push_back(list, value);
    int pos_2 = list_push_back(list, value);

    size_t prev_size = list->size;
    int err_val = 0;

    int value_pos = list_push_after_index(list, 
                       (unsigned)pos_1, value);
    if (value_pos == -1)
        err_val++;

    if (list->data[value_pos] != value) 

        list_error(LIST_PUSH_AFTER_INDEX_TEST_FAILED, 
                   LIST_INV_DATA, &err_val);

    if (list->prev[value_pos] != pos_1) 

        list_error(LIST_PUSH_AFTER_INDEX_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    if (list->next[value_pos] != pos_2) 

        list_error(LIST_PUSH_AFTER_INDEX_TEST_FAILED, 
                   LIST_INV_NEXT, &err_val);

    if (list->prev[pos_2] != value_pos) 

        list_error(LIST_PUSH_AFTER_INDEX_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    if (list->next[pos_1] != value_pos) 

        list_error(LIST_PUSH_AFTER_INDEX_TEST_FAILED, 
                   LIST_INV_NEXT, &err_val);

    if (list->size != prev_size + 1) 

        list_error(LIST_PUSH_AFTER_INDEX_TEST_FAILED, 
                   LIST_INV_SIZE, &err_val);

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_push_before_index_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list_test_init(list);

    elem_t value = 10;
    int pos_1 = list_push_back(list, value);
    int pos_2 = list_push_back(list, value);

    size_t prev_size = list->size;
    int err_val = 0;

    int value_pos = list_push_before_index(list, 
                       (unsigned)pos_2, value);
    if (value_pos == -1)
        err_val++;

    if (list->data[value_pos] != value) 

        list_error(LIST_PUSH_BEFORE_INDEX_TEST_FAILED, 
                   LIST_INV_DATA, &err_val);

    if (list->prev[value_pos] != pos_1) 

        list_error(LIST_PUSH_BEFORE_INDEX_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    if (list->next[value_pos] != pos_2) 

        list_error(LIST_PUSH_BEFORE_INDEX_TEST_FAILED, 
                   LIST_INV_NEXT, &err_val);

    if (list->prev[pos_2] != value_pos) 

        list_error(LIST_PUSH_BEFORE_INDEX_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    if (list->next[pos_1] != value_pos) 

        list_error(LIST_PUSH_BEFORE_INDEX_TEST_FAILED, 
                   LIST_INV_NEXT, &err_val);

    if (list->size != prev_size + 1) 

        list_error(LIST_PUSH_BEFORE_INDEX_TEST_FAILED, 
                   LIST_INV_SIZE, &err_val);

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_pop_by_index_test(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    list_test_init(list);

    elem_t value = 10;
    int pos_1     = list_push_back(list, value);
    int value_pos = list_push_back(list, value);
    int pos_2     = list_push_back(list, value);

    size_t prev_size = list->size;
    int err_val = 0;

    elem_t returning_value = list_pop_by_index(list, 
                                (unsigned)value_pos, 
                                          &err_val);
    if (err_val == -1)
        err_val = 1;;
    
    if (returning_value != value) 

        list_error(LIST_POP_BY_INDEX_TEST_FAILED, 
                   LIST_POP_INV_RET_VALUE, &err_val);


    if (list->prev[value_pos] != -1) 

        list_error(LIST_POP_BY_INDEX_TEST_FAILED, 
                   LIST_INV_PREV_FOR_FREE_ELEM, &err_val);

    if (list->free != (unsigned)value_pos) 

        list_error(LIST_POP_BY_INDEX_TEST_FAILED, 
                   LIST_INV_FREE, &err_val);

    if (list->prev[pos_2] != pos_1) 

        list_error(LIST_POP_BY_INDEX_TEST_FAILED, 
                   LIST_INV_PREV, &err_val);

    if (list->next[pos_1] != pos_2) 

        list_error(LIST_POP_BY_INDEX_TEST_FAILED, 
                   LIST_INV_NEXT, &err_val);

    if (list->size != prev_size - 1) 

        list_error(LIST_POP_BY_INDEX_TEST_FAILED, 
                   LIST_INV_SIZE, &err_val);

    list_test_stop(list, err_val);

    if (err_val != 0)
        return 0;
    else
        return 1;
}

//===================================================================

int _list_unit_tests(struct List* list, LOG_PARAMS) {

    list_log_report();
    LIST_POINTER_CHECK(list);

    fprintf(logs_file, "<div style = \" font_size: 15;"
                                      " text-align: center;"
                                      " color: white;"
                                      " padding: 20px;"
                                      " background-color: green;\">"
                                      " <pre>\nList unit testing started\n"
                                      " </pre></div>");

    int is_ok = 0;
    int failed_test_count = 0;

    is_ok = list_push_first_test(list);
    if (is_ok == 0)
        failed_test_count++;

    is_ok = list_pop_last_test(list);
    if (is_ok == 0)
        failed_test_count++;

    is_ok = list_push_back_test(list);
    if (is_ok == 0)
        failed_test_count++;

    is_ok = list_pop_back_test(list);
    if (is_ok == 0)
        failed_test_count++;

    is_ok = list_push_front_test(list);
    if (is_ok == 0)
        failed_test_count++;

    is_ok = list_pop_front_test(list);
    if (is_ok == 0)
        failed_test_count++;

    is_ok = list_push_after_index_test(list);
    if (is_ok == 0)
        failed_test_count++;

    is_ok = list_push_before_index_test(list);
    if (is_ok == 0)
        failed_test_count++;
    
    is_ok = list_pop_by_index_test(list);
    if (is_ok == 0)
        failed_test_count++;;

    fprintf(logs_file, "<div style = \" font_size: 15;"
                                      " text-align: center;"
                                      " color: white;"
                                      " padding: 20px;\">");

    fprintf(logs_file, " <pre>\nTotal tests failed"
                       " : %d\n</pre></div>", 
                         failed_test_count);

    if (failed_test_count == 0)
        fprintf(logs_file, "<div style = \" font_size: 15;"
                                      " text-align: center;"
                                      " color: white;"
                                      " padding: 20px;"
                                      " background-color: green;\">"
                                      " <pre>\n All tests passed"
                                      " successfully\n</pre></div>");

    if (failed_test_count != 0)
        return -1;
    else
        return 0;
}
