#ifndef RANDGEN_CPP
#define RANDGEN_CPP

#include "RandGen.hpp"
#include "RepGen.cpp"

// Constructor
RandGen::RandGen() : Generation() {

}
RandGen::RandGen(RepGen* prev) : Generation(prev) {
    
}
RandGen::RandGen(const RandGen& gen) : Generation(gen) {

}

// Destructor
RandGen::~RandGen() {

}

// Assignment operator
RandGen& RandGen::operator=(const RandGen& gen) {
    this->Generation::operator=(gen);
}

// Creates a pointer to the next generation.
Generation* RandGen::nextGen() {
    Generation* successor = new RepGen(this);
    RandGen duplicate = *this;
    unsigned int i;

    duplicate.randomize();

    for (i = 0; i < xBuckets; i++) {
        (successor->locations)[i] = ((duplicate.locations)[i])->getNextGenBucket(successor);
    }

    return successor;
}

#endif