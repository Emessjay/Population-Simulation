#ifndef BREEDER_CPP
#define BREEDER_CPP

#include <cstdlib>
#include <ctime>

#include "Breeder.hpp"
#include "Generation.cpp"
#include "BreederBucket.cpp"
#include "helper.cpp"

Breeder::Breeder() {
    age = 0;
    ID = allTimePopulation++;
    loud = true;
    gen = nullptr;
    previous = nullptr;
    next = nullptr;
}

Breeder::Breeder(Generation* gen) {
    age = 0;
    ID = allTimePopulation++;
    loud = true;
    this->gen = gen;
    previous = nullptr;
    next = nullptr;
    if (loud)
        std::cout << "ID #" << ID << " (of type " << type << ")" << " was born." << std::endl;
}

Breeder::Breeder(const Breeder& toCopy) {
    age = toCopy.getAge();
    ID = toCopy.getID();
    loud = toCopy.isLoud();
    gen = toCopy.getGen();
    previous = toCopy.previous;
    next = toCopy.next;
}

Breeder::Breeder(Breeder* predecessor, bool isSame) {
    if (isSame) {
        age = predecessor->getAge() + 1;
        ID = predecessor->getID();
        loud = predecessor->isLoud();
        gen = predecessor->gen->getNext();
        previous = predecessor;
        next = nullptr;
        predecessor->next = this;
    } else {
        age = 0;
        ID = allTimePopulation++;
        loud = true;
        gen = predecessor->gen->getNext();
        previous = nullptr;
        next = nullptr;
        if (loud)
            std::cout << "ID #" << ID << " (of type " << type << ")" << " was born." << std::endl;
    }
}

Breeder& Breeder::operator=(const Breeder& toCopy) {
    age = toCopy.getAge();
    ID = toCopy.getID();
    loud = toCopy.isLoud();
    gen = toCopy.getGen();
    previous = toCopy.previous;
    next = toCopy.next;
    return *this;
}

std::vector<Breeder*> Breeder::descendants(double food) {
    std::vector<Breeder*> bucket;
    srand(time(0));
    if (food <= 0) {
        if (loud) std::cout << "ID #" << ID << " has died of starvation." << std::endl;
    } else if (food < survivalThreshold) {
        if ( helper::randIsAboveThreshold(food / survivalThreshold) ) {
            if (loud) std::cout << "ID #" << ID << " has died of starvation." << std::endl;
        } else {
            bucket.push_back(new Breeder(this, true));
            if (loud) std::cout << "ID #" << ID << " has survived." << std::endl;
        }
    } else {
        food -= survivalThreshold;
        bucket.push_back(new Breeder(this, true));
        if (loud) std::cout << "ID #" << ID << " has survived." << std::endl;
        while (food > 0) {
            if ( helper::randIsAboveThreshold( food/(reproductionThreshold - survivalThreshold) ) ) {
                break;
            } else {
                food -= (reproductionThreshold - survivalThreshold);
                bucket.push_back(new Breeder(this, false));
                if (loud) std::cout << "ID #" << ID << " has had a child." << std::endl;
            }
        }
    }
    return bucket;
}

double Breeder::interactionCoefficient(Breeder* other) const {
    if (other->type == "Breeder") {
        return 0.5;
    }

    return 0.5;
}

#endif