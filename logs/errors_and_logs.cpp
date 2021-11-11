#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors_and_logs.h"
#include "../list/list_config.h"

//===================================================

// #define ERRORS_MAX_COUNT 20

// int Error_counter = 0;

// long int Error_pos = 0;

// int Error_codes[ERRORS_MAX_COUNT] = { 0 };

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

    fprintf(logs_file, "\n\n<div style = \" font-size: 15;"
                                          " text-align: center;"
                                          " color: white;"
                                          " background-color: red;\"><pre>\n");

    fprintf(logs_file, "\nACHTUNG!!\n");

    fprintf(logs_file, "\nAn error occured, my condolences((\n\n");

    fprintf(logs_file, "File: %s\n",file_name);
    fprintf(logs_file, "Function: %s\n", func_name);
    fprintf(logs_file, "Line: %d\n\n", line);

    fprintf(logs_file, "%s\n\n", get_error_descr(error_code));

    fprintf(logs_file, "\n</pre></div>\n");

    return 0;
}

//===================================================

FILE* open_log_file(const char* filename) {

    if (filename == NULL)
        return NULL;

    char directory_name[DIR_NAME_SIZE];
    sprintf(directory_name, "%s%s", TEMP_DIR, filename);

    FILE* logs_file = fopen(directory_name, "wb");

    if (logs_file == NULL) {

        fprintf(stderr, "Could not open log file\n");
        return NULL;
    }

    int ret = write_head_html(logs_file);
    if (ret == -1)
        return NULL;
     
    return logs_file;
}

//===================================================

int write_head_html(FILE* logs_file) {

    if (logs_file == NULL)
        return -1;

    fprintf(logs_file, "<html><head>");

    fprintf(logs_file, "<style>\n .outline {\n border: 0px solid black;"
                                           "\n padding: 0 10px;"
                                           "\n bgcolor = \"#196fA1\";"
                                           "\n color = \"white\";"
                                           "\n}\n </style>");

    fprintf(logs_file, "<style>\n .table { \n background: lightgrey;"
                                          "\n padding: 5px; border: 1px solid black;"
                                          "\n}\n</style>");
                                          
    fprintf(logs_file, "<style> \n td {\n border: 1px solid black;\n}\n </style>");
    
    fprintf(logs_file, "</head>");
    fprintf(logs_file, "\n<body bgcolor = \"#777777\">");


    return 0;
}

//===================================================

int _close_log_file(LOG_PARAMS) {

    log_report();

    fprintf(logs_file, "</body></html>");

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

    fprintf(logs_file, "\n<pre>\n");

    int value = fprintf(logs_file, "<div class=\"outline\"  "
                                   "style = \"background-color:lightgrey;\" "
                                   "style = \"text-align: center;\"><b>Funtion: %s\n\n</b> "
                                   "Called from: function: <b>%s</b>, file: <b>%s</b>."
                                   "Current line: <b>%d</b>.\n </div>", mother_func, 
                                                        func_name, file_name, line);

    fprintf(logs_file, "\n</pre>\n");

    if (value < 0) 
        error_report(FILE_OUTPUT_ERROR);

    return 0;
}

//================================================

int _smpl_log_report(LOG_PARAMS) {

    if (log_report_parameters_check(LOGS_ARGS_USE) == 0)
        return -1;

    fprintf(logs_file, "\n<pre>\n");

    int value = fprintf(logs_file, "Function: %s, file: %s, line: %d \n \n",
                                                func_name, file_name, line);

    fprintf(logs_file, "\n</pre>\n");

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