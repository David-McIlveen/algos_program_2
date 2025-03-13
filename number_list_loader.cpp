#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>

#include "number_list_loader.h"


using namespace std;
namespace fs = std::filesystem;

number_test_list* get_nubmers(){
    fs::path current_path = fs::current_path();
    fs::path test_dir = current_path / "tests";
    if(!fs::is_directory(test_dir)){
        throw "The dir \'tests\' does not exist in the current context, please add it.";
    }

    vector<number_list> list_of_lists;

    for (const auto & entry : fs::directory_iterator(test_dir)){
        fs::path file_path = entry.path();   
        std::ifstream text_to_process;
        text_to_process.open(file_path);
        number_list list_m;
        string line;
        if(std::getline(text_to_process, line)){
            list_m.test_name = line;
        } else {
            continue; // Empty File, don't process
        }

        if(std::getline(text_to_process, line)){
            std::istringstream iss(line);
            int k;
            if (!(iss >> k)) { continue; } // error
            list_m.k = k;
        }
        if(std::getline(text_to_process, line)){
            std::istringstream iss(line);
            double expected_result;
            if (!(iss >> expected_result)) { continue; } // error
            list_m.expected_result = expected_result;
        }
        vector<double> numbers_to_process;

        // From https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
        while(std::getline(text_to_process, line)){
            std::istringstream iss(line);
            double a;
            if (!(iss >> a)) { break; } // error
            numbers_to_process.push_back(a);
        }




        if(numbers_to_process.size() == 0) continue; //End if empty / no points to process
        if((size_t) list_m.k > numbers_to_process.size()) continue; //End if k is greater than n (impossible)

        int points_array_size = numbers_to_process.size();
        list_m.nubmers = new double[points_array_size];
        for (int i = 0; i < points_array_size; i++){
            list_m.nubmers[i] = numbers_to_process.at(i);
        }
        list_m.size = points_array_size;
        list_of_lists.push_back(list_m);

    }

    number_test_list* to_return = new number_test_list;
    to_return->num_of_tests = list_of_lists.size();
    to_return->tests = new number_list[to_return->num_of_tests];
    for (int i = 0; i < to_return->num_of_tests; i++){
        to_return->tests[i] = list_of_lists.at(i);
    }
    
    return to_return; // Temp
}

