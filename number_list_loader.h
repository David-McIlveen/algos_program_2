#ifndef NUMBER_LIST_LOADER
#define NUMBER_LIST_LOADER

#include<string>

struct number_list{
    int size;
    std::string test_name;
    int k;
    int expected_result;
    double* nubmers;
};

struct number_test_list{
    int num_of_tests;
    number_list* tests;
};

number_test_list* get_nubmers();

#endif