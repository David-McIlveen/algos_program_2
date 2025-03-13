#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>     // For std::default_random_engine
using namespace std;

const string DEFAULT_FILE_NAME = "test_case";
const double MIN_VALUE = -10000; // Minimum value in the array
const double MAX_VALUE = 10000;  // Maximum value in the array

// Function to generate a random double in a given range
double get_random_double(double lower_bound, double upper_bound);

// Function to generate a random double in the default range
double get_random_double();

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Get user input for k
    int k;
    cout << "Enter k (1 <= k <= n): ";
    if (!(cin >> k) || k <= 0) {
        cout << "Invalid input for k. Using default value k = 1." << endl;
        k = 1;
    }

    // Get user input for n
    int n;
    cout << "Enter n (size of the array, n >= k): ";
    if (!(cin >> n) || n < k) {
        cout << "Invalid input for n. Using default value n = k." << endl;
        n = k;
    }

    // Get user input for the file name
    string file_name;
    cout << "Enter output file name (without extension): ";
    if (!(cin >> file_name) || file_name.empty()) {
        cout << "Invalid file name. Using default file name: " << DEFAULT_FILE_NAME << endl;
        file_name = DEFAULT_FILE_NAME;
    }

    // Generate the k-th smallest value
    double kth_value = get_random_double(MIN_VALUE, MAX_VALUE);

    // Generate numbers less than the k-th value
    vector<double> lt_nums;
    for (int i = 0; i < k - 1; i++) {
        lt_nums.push_back(get_random_double(MIN_VALUE, kth_value));
    }

    // Generate numbers greater than the k-th value
    vector<double> gt_nums;
    for (int i = k; i < n; i++) {
        gt_nums.push_back(get_random_double(kth_value, MAX_VALUE));
    }

    // Combine all numbers into a single array
    vector<double> values;
    values.insert(values.end(), lt_nums.begin(), lt_nums.end());
    values.push_back(kth_value); // Add the k-th value
    values.insert(values.end(), gt_nums.begin(), gt_nums.end());


    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(values.begin(), values.end(), g);

    // Write the test case to the file
    ofstream output_file(file_name + ".txt");
    if (!output_file.is_open()) {
        cerr << "Error: Could not open file for writing." << endl;
        return -1;
    }

    // Write k and the expected k-th smallest value to the file
    output_file << file_name << endl;
    output_file << k << endl;
    output_file << kth_value << endl;

    // Write the array to the file
    for (double value : values) {
        output_file << value << endl;
    }

    output_file.close();

    cout << "Test case generated successfully in file: " << file_name << ".txt" << endl;
    return 0;
}

// Generate a random double in the default range
double get_random_double() {
    return get_random_double(MIN_VALUE, MAX_VALUE);
}

// Generate a random double in a given range
double get_random_double(double lower_bound, double upper_bound) {
    double random = (double)rand() / RAND_MAX; // Random value between 0 and 1
    return lower_bound + random * (upper_bound - lower_bound);
}