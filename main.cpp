#include "list/list.h"
#include "stdlib.h"

//===================================================================

int main(int argc, char* argv[]) {

    LIST_ARGC_CHECK(argc);

    FILE* logs_file = open_log_file(argv[1]);

    if (logs_file == NULL)
        return -1;

    int err_val = 0;

    struct List list = { 0 };
    err_val = list_ctor(&list); $

    err_val = list_push_back(&list, 10); $
    err_val = list_push_back(&list, 20); $
    err_val = list_push_back(&list, 29); $
    err_val = list_push_back(&list, 40); $
    err_val = list_push_back(&list, 50); $
    err_val = list_push_back(&list, 60); $
    err_val = list_push_back(&list, 70); $
    err_val = list_push_back(&list, 80); $

    list_pop_by_index(&list, 7, &err_val); $
    list_pop_by_index(&list, 3, &err_val); $

    err_val = list_push_back(&list, 150); $
    err_val = list_push_front(&list, 5); $

    list_pop_by_index(&list, 5, &err_val); $

    err_val = list_linearize(&list); $


    err_val = list_push_back(&list, 160); $

    err_val = list_push_after_index(&list, 8, 170);$

    list_pop_front(&list, &err_val);$
    list_pop_front(&list, &err_val);$
    list_pop_front(&list, &err_val);$

    err_val = list_push_front(&list, 39);$
    err_val = list_push_front(&list, 38);$
    err_val = list_push_front(&list, 37);$
    err_val = list_push_front(&list, 36);$

    err_val = list_push_front(&list, 35);$
    err_val = list_push_front(&list, 34);$
    err_val = list_push_front(&list, 33);$

    err_val = list_push_front(&list, 32);$
    err_val = list_push_front(&list, 31);$

    err_val = list_linearize(&list); $

    err_val = list_dtor(&list);$
    err_val = list_ctor(&list);$

    list_linearize(&list);$

    fflush(logs_file);

    //list_linearize

    list_draw_graph(&list);$
    system(" dot list_graph.txt -Tpng -O");

    err_val = list_dtor(&list); $
    err_val = close_log_file(); $
}


