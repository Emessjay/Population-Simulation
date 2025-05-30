#include "Generation.cpp"

class Breeder;
class BreederBucket;
class RepGen;
class Simulation;

class RandGen : public Generation {
    public:
        // Constructors
        RandGen();
        RandGen(RepGen* prev);
        RandGen(const RandGen& gen);

        // Destructor
        ~RandGen();

        // Assignment operator
        RandGen& operator=(const RandGen& gen);

        // Creates a pointer to the next generation.
        Generation* nextGen();        
};