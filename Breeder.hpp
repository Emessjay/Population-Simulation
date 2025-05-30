#include <string>
#include <iostream>

class Generation;
class BreederBucket;

class Breeder {
    public:
        // Constructors
        Breeder();
        Breeder(Generation* gen);
        Breeder(const Breeder& toCopy);
        Breeder(Breeder* predecessor, bool isSame); // True generates the next iteration of the Breeder. False generates a child.

        // Assignment operator
        Breeder& operator=(const Breeder& toCopy);

        // Accessors
        virtual std::string getType() const { return type; }
        int getAge() const { return age; }
        int getID() const { return ID; }
        bool isLoud() const { return loud; }
        Generation* getGen() const { return gen; }
        int getLifespan() const { return lifespan; }
        double getSurvivalThreshold() const { return survivalThreshold; }
        double getReproductionThreshold() const { return reproductionThreshold; }

        // Mutators
        void setLoud(bool loud) { this->loud = loud; }
        void setGen(Generation* gen)  { this->gen = gen; }
        void setLifespan(int l) { lifespan = l; }
        void setSurvivalThreshold(double s) { survivalThreshold = s; }
        void setReproductionThreshold(double r) { reproductionThreshold = r; }
        void giveNewID() { ID = allTimePopulation++; }

        // Pointers to previous and next iterations
        Breeder* previous;
        Breeder* next;

        // Breeder survival checker
        virtual std::vector<Breeder*> descendants(double food);

        // Calculates interaction effects between two Breeder types.
        virtual double interactionCoefficient(Breeder* other) const;
        
        // Breeder type (class constant, overridden for every derived class)
        static const std::string type;

    private:
        // Data members
        int age;
        unsigned long long ID;
        bool loud;
        bool copy;
        Generation* gen;

        // Keeps track of the total number of Breeders that have ever existed.
        static unsigned long long allTimePopulation;

        // Maximum lifespan of the Breeders.
        static int lifespan;

        // Thresholds for guaranteed survival and guaranteed reproduction.
        static double survivalThreshold;
        static double reproductionThreshold;
};

const std::string Breeder::type = "Breeder";
unsigned long long Breeder::allTimePopulation = 0;
int Breeder::lifespan = 5;
double Breeder::survivalThreshold = 1;
double Breeder::reproductionThreshold = 2;