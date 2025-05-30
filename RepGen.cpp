#ifndef REPGEN_CPP
#define REPGEN_CPP

#include "RepGen.hpp"

// Constructor
RepGen::RepGen();
RepGen::RepGen(unsigned int x, std::function<double(int, unsigned int, int, unsigned int)> dist = distributor::standard);
RepGen::RepGen(RandGen* prev);
RepGen::RepGen(const RepGen& gen);

// Destructor
RepGen::~RepGen();

// Assignment operator
RepGen& RepGen::operator=(const RepGen& gen);

// Creates a pointer to the next generation.
Generation* nextGen(); 

#endif