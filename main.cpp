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

    list_push_back(&list, 10); $

    list_push_back(&list, 20); $

    int pos30 = list_push_back(&list, 30); $
    int position = list_push_back(&list, 40); $
    list_push_back(&list, 50); $
    list_push_back(&list, 60); $
    list_push_back(&list, 70); $
    list_push_back(&list, 80); $
    list_push_back(&list, 90); $
    list_push_after_index(&list, (unsigned int)position, 50);

    list_push_back(&list, 100); $

    list_pop_by_index(&list, pos30, &err_val); 

    list_push_front(&list, 5);

    err_val = list_dtor(&list); $
    err_val = close_log_file(); $
}


