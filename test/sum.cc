#include "sum.h"

namespace {

int sum(const tbb::blocked_range<int*>& range, int init) {
    for(auto value : range)
        init += value;
    return init;
}


int join(const int x, const int y) { return x + y; }

}

int parallel_sum(const tbb::blocked_range<int*>& range) {
    return tbb::parallel_reduce(range, 0, & sum, & join);
}
