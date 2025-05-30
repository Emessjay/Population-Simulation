#include <string>
#include <iostream>

#include "Generation.cpp"

using namespace std;

const int ITERS = 10;

int main() {
    Generation gens[ITERS] = {Generation(10)};
    std::vector<int> b;
    int i;
    int j;

    for (i = 1; i < ITERS; i++) {
        gens[i] = *(gens[i - 1].nextGen());
    }

    for (i = 0; i < ITERS; i++) {
        b = gens[i].breedersBySlot();
        for (j = 0; j < 10; j++) {
            std::cout << b.at(j) << ' ' << std::flush;
        }
        std::cout << std::endl;
    }
}