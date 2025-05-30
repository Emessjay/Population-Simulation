#ifndef HELPER_CPP
#define HELPER_CPP

#include <random>

namespace helper {

    bool randIsBelowThreshold(double threshold) {
        std::random_device rd;
        std::mt19937 gen(rd());
        return ( std::generate_canonical<double, 10>(gen) < threshold );
    }

    bool randIsAboveThreshold(double threshold) {
        return !randIsBelowThreshold(threshold);
    }

}

#endif