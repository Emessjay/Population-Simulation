#include "Generation.cpp"

class Breeder;
class BreederBucket;
class RandGen;
class Simulation;

class RepGen : public Generation {
    public:
        // Constructors
        RepGen();
        RepGen(unsigned int x, std::function<double(int, unsigned int, int, unsigned int)> dist = distributor::standard);
        RepGen(RandGen* prev);
        RepGen(const RandGen& gen);

        // Destructor
        ~RepGen();

        // Assignment operator
        RepGen& operator=(const RepGen& gen);

        // Creates a pointer to the next generation.
        Generation* nextGen(); 
};