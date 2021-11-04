#pragma once

#include <cstddef>

//===================================================================

//LIST PARAMETERS

//Element type of the list structure
typedef int elem_t;

#define TYPE_NAME "int"

#define ELEM_SPEC "%d"

const size_t List_capacity = 32;

const size_t Max_list_capacity = 32;

//===================================================================

//LIST OPTIONS

#define LIST_LOGS

#define LIST_DEBUG

#define CMND_LINE_ARGS_NUMBER 2

//==================================================================

//SUPPORTING DEFINITIONS

#define POISON_VALUE 228

//==================================================================

//GENERAL

#define GENERAL_LOGS
