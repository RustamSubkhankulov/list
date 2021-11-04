#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors_and_logs.h"

//===================================================

int _error_report(int error_code, LOG_PARAMS) {

    fprintf(stderr, "\n ACHTUNG!!\n");

    fprintf(stderr, "\nAn error occured, my condolences((\n\n");

    fprintf(stderr, "File: %s\n",file_name);
    fprintf(stderr, "Function: %s\n", func_name);
    fprintf(stderr, "Line: %d\n", line);

    fprintf(stderr, "%s\n\n", get_error_descr(error_code));

    fprintf(stderr, "This message also reported in log file,"
                    " see logs to get more information about"
                                    " programm performing\n");

    fprintf(logs_file, "\n ACHTUNG!!\n");

    fprintf(logs_file, "\nAn error occured, my condolences((\n\n");

    fprintf(logs_file, "File: %s\n",file_name);
    fprintf(logs_file, "Function: %s\n", func_name);
    fprintf(logs_file, "Line: %d\n", line);

    fprintf(logs_file, "%s\n\n", get_error_descr(error_code));

    return 0;
}

//===================================================

// int _error_message(const char* message, LOG_PARAMS) {

//     fprintf(stderr, "Error message from file %s\n", file_name);

//     fprintf(stderr, "Function: %s\n", func_name);

//     fprintf(stderr, "Line: %d\n", line);

//     fprintf(stderr, "\n%s\n\n", message);
// }

//===================================================

FILE* open_log_file(const char* filename) {

    if (filename == NULL)
        return NULL;

    // char buf[LOG_FILE_DIR_BUF_SIZE] = { 0 };

    // strcpy(buf, LOG_DIR);
    // strcat(buf, filename);

    // printf("\n %s \n", buf);

    FILE* temp_ptr = fopen(filename, "a");

    if (temp_ptr == NULL) {

        fprintf(stderr, "Could not open log file\n");
        return NULL;
    }

    else 
        return temp_ptr;
}

//===================================================

int _close_log_file(LOG_PARAMS) {

    log_report();

    if (logs_file == NULL)
        return -1;

    int fclose_ret = fclose(logs_file);

    if (fclose_ret == EOF)
        return -1;

    return 0;
}

//================================================

int log_report_parameters_check(LOG_PARAMS) {

    if (line <= 0 
    || logs_file == NULL
    || file_name == NULL 
    || func_name == NULL) {
    
        error_report(LOG_REPORT_PARAMS_ERR);
        return 0;
    }
    return 1;
}

//================================================

int _log_report(LOG_PARAMS, const char* mother_func) {

    if (log_report_parameters_check(LOGS_ARGS_USE) == 0)
        return -1;

    int value = fprintf(logs_file, "Funtion: %s\n Called from: function: %s, file: %s."
                                      " Current line: %d.\n\n", mother_func, func_name, 
                                                                      file_name, line);

    if (value < 0) 
        error_report(FILE_OUTPUT_ERROR);

    return 0;
}

//================================================

int _smpl_log_report(LOG_PARAMS) {

    if (log_report_parameters_check(LOGS_ARGS_USE) == 0)
        return -1;

    int value = fprintf(logs_file, "Function: %s, file: %s, line: %d \n \n",
                                                func_name, file_name, line);

    if (value < 0) 
        error_report(FILE_OUTPUT_ERROR);

    return 0;
}

//=================================================

#define DEF_ERR(code, name, string)                 \
                                                    \
    case code : {                                   \
                                                    \
        return #string;                             \
                                                    \
        break;                                      \
    }                                               \

//=================================================

const char* get_error_descr(int error_code) {

    switch (error_code) {

    #include "../include/errors.txt"
    
    default:
        return NULL;
    }
}

#undef DEF_ERR