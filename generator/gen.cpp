#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

const string DEFAULT_FILE_NAME = "temp_polygon";
const double min_value = -1000000000;
const double max_value = 1000000000;

double get_random_double();

double get_random_double(double lower_bound, double upper_bound);

main(){
    cout << "Enter K: ";
    int k;
    if(!(cin >> k)){
        cout << "Please restart and enter a int value!" << endl;
        return -1;
    }
    cout << endl;

    if(k <= 0){
        cout << "K cannot be 0 or less, using default value of 1." << endl;
        k = 1;
    }

    cout << "Enter N ( Must be greater than: " << k << " ): ";
    int n;
    if(!(cin >> n)){
        cout << "Please restart and enter a int value!" << endl;
        return -1;
    }
    cout << endl;
    if(n <= 0){
        cout << "N cannot be 0 or less, using a default value of 1." << endl;
        n = 1;
    }
    if(n < k){
        cout << "Invalid N of " << n << " using default value of (k + n) or: " << k + n << endl; 
        n = k + n;
    }

    string file_name;
    cout << "Enter file Name: ";
    if(!(cin >> file_name) || file_name == ""){
        cout << endl << "Using defualt file name: " << DEFAULT_FILE_NAME;
        file_name = DEFAULT_FILE_NAME;
    }
    cout << endl;

    double kth_value = get_random_double();
    vector<double> lt_nums;
    vector<double> gt_nums;
    for (int i = 0; i < k - 1; i++){
        lt_nums.push_back(get_random_double(min_value, kth_value));
    }

    for (int i = k + 1; i < n; i++){
        gt_nums.push_back(get_random_double(kth_value, max_value));
    }

    srand(time(NULL));
    int k_element_index = rand() % n;
    double* values = new double[n];
    values[k_element_index] = kth_value;
    for (int i = 0; i < n; i++){
        if(i == k_element_index) continue; // Don't erase K!
        if(rand() % 2 == 0 && gt_nums.size() != 0){
            values[i] = gt_nums.at(gt_nums.size() - 1);
            gt_nums.pop_back();
        } else {
            values[i] = lt_nums.at(lt_nums.size() - 1);
            lt_nums.pop_back();
        }
    }
    
    

    std::ofstream print_out;
    print_out.open(file_name + ".txt");
    
    print_out << k << endl;

    for (int i = 0; i < n; i++){
        print_out << values[i] << endl;
    }
    
}

double get_random_double(){
    return get_random_double(min_value, max_value);
}

// From https://www.geeksforgeeks.org/generate-random-double-numbers-in-cpp/
double get_random_double(double lower_bound, double upper_bound){
    const long max_rand = 1000000L;
 
    srand(time(NULL));
 
      // Using random function to
      // get random double value
    double random_double = lower_bound
                           + (upper_bound - lower_bound)
                                 * (rand() % max_rand)
                                 / max_rand;
  
    return 0;
}