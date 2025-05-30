#include <vector>

class Breeder;
class Generation;

class BreederBucket {
    public:
        BreederBucket(Generation* gen = nullptr);
        BreederBucket(std::vector<Breeder*> b);
        BreederBucket(const BreederBucket& bb);

        std::vector<Breeder*> breeders;
        double food = 0.0;

        Generation* getGen() const { return gen; }
        void setGen(Generation* gen);
        
        BreederBucket* getNextGenBucket(Generation* g);

        BreederBucket& operator=(const BreederBucket& bb);
    private:
        Generation* gen;
        std::vector<Breeder*> copyBreeders() const;
};