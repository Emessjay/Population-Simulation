#include <functional>
#include "distributor.cpp"

// TODO: Add additional stats to statsByLocation()

class Breeder;
class BreederBucket;
class Simulation;

class Generation {
    public:
        // Constructors
        Generation();
        Generation(unsigned int x, std::function<double(int, unsigned int, int, unsigned int)> dist = distributor::standard);
        Generation(Generation* prev);
        Generation(const Generation& gen);

        // Destructor
        ~Generation();

        // Accessors
        virtual Generation* getPrevious() { return previous; };
        virtual Generation* getNext() { return next; };
        unsigned int getXBuckets() const { return xBuckets; }

        // Assignment operator
        Generation& operator=(const Generation& gen);

        // Creates a pointer to the next generation.
        virtual Generation* nextGen();

        // Gets statistics.
        std::vector<int> breedersBySlot();
        std::vector<double> statsByLocation(); // Returns mean and median.

        // Gets the next step in the cycle.
        static char nextState(char s);

    protected:
        // Number of buckets there are.
        const unsigned int xBuckets;

        // Array of buckets.
        BreederBucket** locations;

        // Gets a vector containing pointers to every Breeder in this Generation.
        virtual std::vector<Breeder*> getAllBreeders();

        // Randomizes breeders in buckets.
        virtual void randomize();

        // Deallocates memory for the locations array.
        virtual void deallocateArr();

        // Allocates (or reallocates) memory for the locations array.
        virtual void allocateArr();

        // Copies elements of locations array into another Generation's locations array. Returns false if copy was not possible.
        virtual bool copyArr(const Generation& gen);

    private:
        // Pointers to the previous generation and the next.
        Generation* previous;
        Generation* next;

        // Pointer to the simulation itself.
        Simulation* sim;

        // Tracks what step the simulation is on.
        unsigned int timeStep;

        // Tracks what state the generation is in.
        const char state;
};