#include <math.h>
#include <iostream>
#include <stdio.h>
#include "MorrisCounter.h"
using namespace std; 


MorrisCounter::MorrisCounter(double e, double g) {
    b = 1 + 2*e*e*g;
    c = 0;
};

void MorrisCounter::update(){
    float y = (float) rand()/RAND_MAX;
    if(y<pow(b, -c)) c = c + 1;
};

int MorrisCounter::query(){
    return int((pow(b, c)-1)/(b-1));
};
