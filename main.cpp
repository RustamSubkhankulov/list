#include "list/list.h"
#include "list/list_tests.h"
#include "stdlib.h"

//===================================================================

int main(int argc, char* argv[]) {

    LIST_ARGC_CHECK(argc);

    FILE* logs_file = open_log_file(argv[1]);

    if (logs_file == NULL)
        return -1;

    int err_val = 0;

    struct List list = { 0 };

    int is_ok = list_unit_tests(&list);
    if (is_ok == -1)
        return -1;

    err_val = list_ctor(&list); $

    //list_pop_back(&list, &err_val); $

    err_val = list_push_front(&list, 39);$
    err_val = list_push_front(&list, 38);$
    err_val = list_push_front(&list, 37);$
    err_val = list_push_front(&list, 36);$

    err_val = list_push_front(&list, 35);$
    err_val = list_push_front(&list, 34);$
    err_val = list_push_front(&list, 33);$

    err_val = list_push_front(&list, 32);$
    err_val = list_push_front(&list, 31);$

    list_linearize(&list);$

    fflush(logs_file);

    err_val = list_dtor(&list); $
    err_val = close_log_file(); $
}


