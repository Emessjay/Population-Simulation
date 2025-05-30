#ifndef BREEDERBUCKET_CPP
#define BREEDERBUCKET_CPP

#include <cstdlib>
#include <ctime>
#include <random>

#include "Breeder.cpp"
#include "BreederBucket.hpp"

BreederBucket::BreederBucket(Generation* gen) {
    this->gen = gen;
}

BreederBucket::BreederBucket(std::vector<Breeder*> b) {
    breeders = b;
}

BreederBucket::BreederBucket(const BreederBucket& bb) {
    breeders = bb.copyBreeders();
    food = bb.food;
    gen = bb.getGen();
}

void BreederBucket::setGen(Generation* gen) {
    this->gen = gen;
    for (int i = 0; i < breeders.size(); i++) {
        breeders.at(i)->setGen(gen);
    }
}

BreederBucket* BreederBucket::getNextGenBucket(Generation* g) {
    BreederBucket* nextGen = new BreederBucket(g);
    if (breeders.size() == 0) {
    } else if (breeders.size() == 1) {
        nextGen->breeders = breeders.at(0)->descendants(food);
    } else {
        std::vector<Breeder*> excess = breeders;
        std::vector<Breeder*> reproductionCandidates;
        std::vector<Breeder*> temp;
        int i;

        std::random_device rd;
        std::mt19937 gen(rd());

        for (i = 0; i < excess.size(); i++) {
            if (excess.at(i)->getAge() >= excess.at(i)->getLifespan()) {
                if (excess.at(i)->isLoud()) {
                    std::cout << "ID #" << excess.at(i)->getID() << " has died of old age." << std::endl;
                }
                excess.erase(excess.begin() + i);
                --i;
            }
        }
        
        std::uniform_int_distribution<> rng1(0, excess.size() - 1);
        i = rng1(gen);
        reproductionCandidates.push_back(excess.at(i));
        excess.erase(excess.begin() + i);

        std::uniform_int_distribution<> rng2(0, excess.size() - 1);
        i = rng2(gen);
        reproductionCandidates.push_back(excess.at(i));
        excess.erase(excess.begin() + i);

        while (excess.size() > 0) {
            excess.at(excess.size() - 1)->descendants(-100);
            excess.pop_back();
        }

        temp = reproductionCandidates.at(0)->descendants(
            food * reproductionCandidates.at(0)->interactionCoefficient(reproductionCandidates.at(1)));
        nextGen->breeders.insert(nextGen->breeders.end(), temp.begin(), temp.end());

        temp = reproductionCandidates.at(1)->descendants(
            food * reproductionCandidates.at(1)->interactionCoefficient(reproductionCandidates.at(0)));
        temp = reproductionCandidates.at(0)->descendants(2);
        nextGen->breeders.insert(nextGen->breeders.end(), temp.begin(), temp.end());

    }
    
    nextGen->food = food;

    return nextGen;
}

BreederBucket& BreederBucket::operator=(const BreederBucket& bb) {
    breeders = bb.copyBreeders();
    food = bb.food;
    gen = bb.getGen();
    return *this;
}

std::vector<Breeder*> BreederBucket::copyBreeders() const {
    std::vector<Breeder*> b;
    for (int i = 0; i < breeders.size(); i++) {
        b.push_back( new Breeder( *(breeders.at(i)) ) );
    }
    return b;
}

#endif