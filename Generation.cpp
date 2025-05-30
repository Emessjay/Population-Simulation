#ifndef GENERATION_CPP
#define GENERATION_CPP

// TODO: incorporate simulation into constructors.

#include "Generation.hpp"
#include "Breeder.cpp"
#include "BreederBucket.cpp"
#include <algorithm>

Generation::Generation() : xBuckets(10), state('d') {
    locations = nullptr;
    previous = nullptr;
    next = nullptr;
    sim = nullptr;
    timeStep = 0;
}

Generation::Generation(unsigned int x, std::function<double(int, unsigned int, int, unsigned int)> dist) : xBuckets(x), state('d') {
    locations = nullptr;
    previous = nullptr;
    next = nullptr;
    sim = nullptr;
    timeStep = 0;
    allocateArr();
    locations[0]->breeders.push_back(new Breeder(this));
    for (unsigned int i = 0; i < xBuckets; i++) {
        locations[i]->food = dist(i, xBuckets, 0, 1);
    }
}

Generation::Generation(Generation* prev) : xBuckets(prev->xBuckets), state(Generation::nextState(prev->state)) {
    locations = nullptr;
    previous = prev;
    next = nullptr;
    sim = prev->sim;
    timeStep = (prev->timeStep) + 1;
    prev->next = this;
    allocateArr();
}

Generation::Generation(const Generation& gen) : xBuckets(gen.getXBuckets()), state(gen.state) {
    locations = nullptr;
    previous = gen.previous;
    next = gen.next;
    sim = gen.sim;
    timeStep = gen.timeStep;
    allocateArr();
    copyArr(gen);
}

Generation::~Generation() {
    deallocateArr();
}

Generation& Generation::operator=(const Generation& gen) {
    locations = nullptr;
    previous = gen.previous;
    next = gen.next;
    sim = gen.sim;
    timeStep = gen.timeStep;
    allocateArr();
    copyArr(gen);
    return *this;
}

Generation* Generation::nextGen() {
    Generation* successor = new Generation(this);
    unsigned int i;

    if (state == 'd') {
        *successor = *this;
        successor->randomize();
        for (i = 0; i < xBuckets; i++) {
            for (int j = 0; j < ((successor->locations)[i])->breeders.size(); j++) {
                ((successor->locations)[i])->breeders.at(j) = new Breeder(((successor->locations)[i])->breeders.at(j), true);
            }
        }
    } else if (state == 'r') {
        for (i = 0; i < xBuckets; i++) {
            (successor->locations)[i] = ((this->locations)[i])->getNextGenBucket(successor);
        }
    }

    return successor;
}

std::vector<int> Generation::breedersBySlot() {
    std::vector<int> b;
    b.resize(xBuckets);
    for (unsigned int i = 0; i < xBuckets; i++) {
        b.at(i) = locations[i]->breeders.size();
    }
    return b;
}

std::vector<double> Generation::statsByLocation() {
    std::vector<int> breedersPerSlot = breedersBySlot();
    std::vector<double> summaryStats;
    unsigned int i;
    int mean = 0;
    int frequency = 0;
    int mode = 0;

    for (i = 0; i < xBuckets; i++) {
        mean = breedersPerSlot.at(i);
    }

    summaryStats.push_back(static_cast<double>(mean) / xBuckets);

    std::sort(breedersPerSlot.begin(), breedersPerSlot.end());
    if ( (xBuckets % 2) == 1) {
        summaryStats.push_back(breedersPerSlot.at(xBuckets / 2));
    } else {
        summaryStats.push_back( ( breedersPerSlot.at(xBuckets / 2)
            + breedersPerSlot.at((xBuckets / 2) - 1) ) / 2.0 );
    }
    return summaryStats;
}

char Generation::nextState(char s) {
    switch (s) {
        case 'd':
            return 'r';
        case 'r':
            return 'd';
        default:
            return '\0';
    }
}

std::vector<Breeder*> Generation::getAllBreeders() {
    std::vector<Breeder*> allBreeders;
    std::vector<Breeder*> temp;
    int i;
    for (i = 0; i < xBuckets; i++) {
        temp = locations[i]->breeders;
        allBreeders.insert(allBreeders.end(), temp.begin(), temp.end());
    }
    return allBreeders;
}

void Generation::randomize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rng(0, xBuckets - 1);

    std::vector<Breeder*> allBreeders = getAllBreeders();
    locations[0]->breeders.clear();

    while (allBreeders.size() > 0) {
        locations[rng(gen)]->breeders.push_back(allBreeders.at(allBreeders.size() - 1));
        allBreeders.pop_back();
    }
}

void Generation::deallocateArr() {
    for (unsigned int i = 0; i < xBuckets; i++) {
        delete locations[i];
    }

    delete[] locations;
    locations = nullptr;
}

void Generation::allocateArr() {
    if (locations != nullptr) {
        deallocateArr();
    }
    
    locations = new BreederBucket*[xBuckets];

    for (unsigned int i = 0; i < xBuckets; i++) {
        locations[i] = new BreederBucket(this);
    }
}

bool Generation::copyArr(const Generation& gen) {
    if (xBuckets != gen.getXBuckets()) return false;
    for (unsigned int i = 0; i < xBuckets; i++) {
        *(locations[i]) = *(gen.locations[i]);
        locations[i]->setGen(this);
    }
    return true;
}

#endif