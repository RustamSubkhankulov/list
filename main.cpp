#include "list/list.h"

//===================================================================

int main(int argc, char* argv[]) {

    LIST_ARGC_CHECK(argc);

    FILE* logs_file = open_log_file(argv[1]);

    if (logs_file == NULL)
        return -1;

    int err_val = 0;

    struct List list = { 0 };
    err_val = list_ctor(&list); $

    // err_val = list_push_back(&list, 10); $

    // err_val = list_push_back(&list, 20); $

    // err_val = list_push_back(&list, 30); $

    // err_val = list_push_back(&list, 40); $

    // err_val = list_push_back(&list, 50); $

    // err_val = list_push_back(&list, 60); $

    // err_val = list_push_after_index(&list, 3, 35); $

    // elem_t value = list_pop_by_index(&list, 5, &err_val); $

    //     printf("\n\n value returned is %d\n\n", value);

    // value = list_pop_by_index(&list, 6, &err_val); $

    //     printf("\n\n value returned is %d\n\n", value);

    // value = list_pop_by_index(&list, 1, &err_val); $

    //     printf("\n\n value returned is %d\n\n", value);

    // value = list_pop_front(&list, &err_val); $

    //      printf("\n\n value returned is %d\n\n", value);

    // value = list_pop_back(&list, &err_val); $

    //     printf("\n\n value returned is %d\n\n", value);    

    // value = list_push_after_index(&list, 7, 120); $

    //      printf("\n\n position is %d\n\n", value); 

    // err_val = list_push_front(&list, 110); $

    // value = list_pop_front(&list, &err_val); $

    //     printf("\n\n head element is %d\n\n", value); 

    // value = list_pop_back(&list, &err_val); $

    //     printf("\n\n tail element is %d\n\n", value); 

    // int position = list_push_front(&list, 25); $

    //     printf("\n\n 25 position is %d\n\n", position); 

    // position = list_push_back(&list, 37); $

    //     printf("\n\n 37 position is %d\n\n", position); 

    // position = list_push_after_index(&list, 3, 33); $

    //     printf("\n\n 33 position is %d\n\n", position);

    // list_pop_back(&list, &err_val); $

    // list_pop_back(&list, &err_val); $

    // list_pop_back(&list, &err_val); $

    // list_pop_back(&list, &err_val); $

    // list_pop_back(&list, &err_val); $


    list_push_front(&list, 10); $
    list_push_front(&list, 20); $
    list_push_front(&list, 30); $
    list_push_front(&list, 10); $
    list_push_front(&list, 20); $
    list_push_front(&list, 30); $

    list_draw_graph(&list);

    // list_push_front(&list, 10); $
    // list_push_front(&list, 20); $
    // list_push_front(&list, 30); $

    //хэш


    err_val = list_dtor(&list); $
    err_val = close_log_file(); $
}


