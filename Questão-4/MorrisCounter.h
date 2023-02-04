#include <stdio.h>

using namespace std; 

class MorrisCounter {
    public:
        void update();
        int query();
        MorrisCounter(double e, double g);

    private:
        double b;
        int c;
};