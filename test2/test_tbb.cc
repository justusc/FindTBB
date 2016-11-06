#include <iostream>
#include <random>
#include "sum.h"

void random_fill(const tbb::blocked_range<int*>& range) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,9);
    
    for (auto & value : range)
        value = distribution(generator);
    
}

int main(int, char**) {
    
    std::unique_ptr<int[]> x(new int [10000]);
    auto x_range = tbb::blocked_range<int*>(x.get(), x.get() + 10000);
    
    tbb::parallel_for(x_range, & random_fill);
    int result = parallel_sum(x_range);
    
    std::cout << result << "\n";
    
    return 0;
}
