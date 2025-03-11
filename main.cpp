#include "number_list_loader.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double algorithm(double* array, int size, int k);

double find_smallest_value(double* array, int size);

double medianOfMedians(double* array, int size);

int main(){
    number_test_list* tests = get_nubmers();
    cout << "There are " << tests->num_of_tests << " tests." << endl;
    for(int i = 0; i < tests->num_of_tests; ++i){
        number_list current_test = tests->tests[i];
        cout << "Test #" << i << " (" << current_test.test_name << ") where k = " << current_test.k << endl;
        cout << endl << "    ";
        for (int i = 0; i < current_test.size; i++){
            cout << current_test.nubmers[i] << ", ";
        }        
        try{
            double kth_smallest_value = algorithm(current_test.nubmers, current_test.size, current_test.k);
            cout << endl << "The Kth smallest value is " << kth_smallest_value << "." << endl;    
            if (kth_smallest_value == current_test.expected_result){
                cout << "The result is correct!" << endl;
            } else {
                cout << "The result is incorrect! Expected " << current_test.expected_result << "." << endl;
            }
        } catch (string e){
            cout << e << endl;
        }
        cout << endl << endl;
    }
}

// Computes the median of medians for pivot selection
double medianOfMedians(double* array, int size) {
    if (size <= 5) {
        // Base case: Sort and return the median
        sort(array, array + size);
        return array[size / 2];
    }

    // Divide the array into groups of 5
    int numGroups = (size + 4) / 5; // Ceiling division
    vector<double> medians(numGroups);

    for (int i = 0; i < numGroups; i++) {
        int groupStart = i * 5;
        int groupEnd = min(groupStart + 5, size);
        int groupSize = groupEnd - groupStart;

        // Sort the group and find its median
        sort(array + groupStart, array + groupEnd);
        medians[i] = array[groupStart + (groupSize / 2)];
    }

    // Recursively find the median of medians
    return medianOfMedians(medians.data(), numGroups);
}

double algorithm(double* array, int size, int k){
    // This shouldn't happen as the program can't process files w/ 0 numbers, but just in case;
    if(k <= 0) throw "ERROR! K cannot be 0 or less!";
    if(size <= 0) throw "ERROR! The algorithm should not have a value of 0 or less in the size!";

    //Base case(s) if k = 1 (We just need to find the smallest element)
    if(k == 1) return find_smallest_value(array, size);
    if(size == 1) throw "ERROR! Array is to small for the k value!";

    double pivot = medianOfMedians(array, size);
    vector<double> greater_nums;
    vector<double> lesser_nums;
    // Counting duplicate values
    int dupe_count = 0;
    for (int i = 0; i < size; i++){
        if(array[i] == pivot){
            ++dupe_count;
        } else if (array[i] < pivot){
            lesser_nums.push_back(array[i]);
        } else {
            greater_nums.push_back(array[i]);
        }
    }

    // Copy values into arrays
    int gt_count = greater_nums.size();
    int lt_count = lesser_nums.size();

    //We don't need the orgial array any more
    delete [] array;

    // K is in the lesser nums
    if(k <= lt_count){
        //Copy vector to array
        double* lt_array = new double[lt_count];
        for (int i = 0; i < lt_count; i++){
            lt_array[i] = lesser_nums.at(i);
        }
        return algorithm(lt_array, lt_count, k);
    }

    // K is in greater
    if(k > lt_count + dupe_count ){
        //Adjust K
        k = k - lt_count - dupe_count;
        //Copy Vector to array
        double* gt_array = new double[gt_count];
        for (int i = 0; i < gt_count; i++){
            gt_array[i] = greater_nums.at(i);
        }
        return algorithm(gt_array, gt_count, k);
    }

    // K is the pivot
    return pivot;
}

// Finds the smallest value of an array and deletes said array
double find_smallest_value(double* array, int size){
    if(size == 0) throw "ERROR! Cannot find smallest value of empty array!";
    double smallest = array[0];
    for (int i = 0; i < size; i++){
        if(array[i] < smallest) smallest = array[i];
    }
    delete [] array;
    return smallest;
}

