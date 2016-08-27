#include "tbb/tbb.h"
#include <iostream>
#include <random>

void random_fill(const tbb::blocked_range<int*>& range) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,9);
    
    for (auto & value : range)
        value = distribution(generator);
    
}

int sum(const tbb::blocked_range<int*>& range, int init) {
    for(auto value : range)
        init += value;
    return init;
}


int join(const int x, const int y) { return x + y; }

int main(int, char**) {
    
    int* x = new int [10000];
    auto x_range = tbb::blocked_range<int*>(x, x + 10000);
    
    tbb::parallel_for(x_range, & random_fill);
    int result = tbb::parallel_reduce(x_range, 0, & sum, & join);
    
    std::cout << result << "\n";
    
    delete [] x;
    
    return 0;
}