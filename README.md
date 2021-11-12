Doubly linked list structure
============================

Brief decription
----------------

This is one of my studying projects in the first year at MIPT university, DREC - a doubly linked list structure.

Configuration
-------------

Before work you should check list_config.h in list package. It is a configuration file, where you can find several options, that will effect on work of list.

- Temporary directiry address.

    <code>#define TEMP_DIR "/mnt/c/users/rust2/appdata/local/temp/" </code>
    
- Size of buffer, used to concatinate directory address

    <code> #define DIR_NAME_SIZE 100 </code>
    
- Size of buffer, used to 'system' commands

    <code> #define SYSTEM_COMMAND_BUF_SIZE 200 </code>

- Type, used in list structure.

    <code> #define elem_t int </code>   Definition for the type, used in structure.
  
- Definition for the name of type.
 
    <code>#define TYPE_NAME "int" </code>   Used only in list dump.
  
- Definition for speicifcator of <code> elem_t </code>
 
    <code>#define ELEM_SPEC "%d" </code>
    
- List starting capacity. Default value is 4.
 
    <code> const size_t List_start_capacity = 4; </code>
    
- List maximum capacity. Default value is 16.
 
    <code> const size_t List_max_capacity = 16; </code>
    
- Logging in list functions. Log file location - logs.html file in temporary package.
 
    <code> #define LIST_LOGS </code>
    
- Logging in general-use functions. Logs location the same as for list functions.
 
    <code> #define GENERAL_LOGS </code>
    
- Debug mode. Adds more checks in list_validator and calls dump in validator every time it called.
 
    <code> #define LIST_DEBUG </code>
    
- List hash protection.
 
    <code> #define LIST_HASH </code>
    
- List graphviz visualisation.
 
    <code> #define LIST_GRAPHVIZ </code>
    
- List poison value, that is used to fill list structure in destructor.
 
    <code> #define POISON_VALUE 228 </code>  Can be any value from 0 to 255 on your choise.
    
What's inside structure?
------------------------

1. <code> elem_t* data </code> pointer to the data 
2. <code> int* next </code> pointer to the array of indexes of next elements
3. <code> int* prev </code> pointer to the array of indexes of prev elements   
4. <code> unsigned int head </code> index of the first element in list
5. <code> unsigned int tail </code> index of the last element in list
6. <code> unsigned int free </code> index of the first element in queue of free elements
7. <code> size_t capacity </code> capacity of list (including first always free index)
8. <code> unsigned int size </code> size of list
9. <code> int is_linerized </code> flag that shows that list is linearized
    
Using, main functions
---------------------

1. List_ctor. 
  >First functions to be called after work. Construction will be successfull if list structure is completely empty or was poisoned by destructor
2. List_dtor
  >Last functions. Poisons structure. Consrtuctor can be called after destructing again.
3. List_unit_test
  >Unit tests for list structure.
4. List_dump
  >Dump function for list. Called in debug mode from validator
5. List_draw_graph
  >Uses graphviz to vizualise links in list structure
6. List_pop_back
  >Takes element from end of list and returns it.
  >Takes as an argument pointer to the int value. Value set to -1 if error occures
7. List_pop_front
  >Takes element fron start of list and returns it.
  >Takes as an argument pointer to the int value. Value set to -1 if error occures
8. List_push_back
  >Pushes element to the end of list
9. List_push_back
  >Pushes element to the start of list
10. List_push_after_index
  >Pushes element after index, that is taken as argument. If index is empty, -1 returned
11. List_push_before_index
  >Pushes element before index, that is taken as argument. If index is empty, -1 returned
12. List_pop_by_index
  >Takes element from index of list and returns it.
  >Takes as an argument pointer to the int value. Value set to -1 if error occures

Special use functions
---------------------

1. <code> List_get_by_logical_number </code>
  >Gets as a number and returns the value of the element that is on this hook in a logical sequence.
  >Is not recommended to use if list is not linearized.
2. <code> List_liearize </code>
  >Slow functions, but it makes work of list_get_by_lodical_number
  >Takes elements of list and places them in logical order 
  >List can decrease only when list linearized 
