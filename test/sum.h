#ifndef sum_h
#define sum_h

#include "tbb/tbb.h"

int parallel_sum(const tbb::blocked_range<int*>& range);

#endif /* sum_h */
