#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "MorrisCounter.h"

using namespace std;

int main() {
	string filename1("output1.csv"), filename2("output2.csv");
    fstream file_out1, file_out2;

    file_out1.open(filename1, std::ios_base::out);
	file_out2.open(filename2, std::ios_base::out);

	file_out1 << "Expected,Result" << endl;
	file_out2 << "Expected,Result" << endl;

    double e1, e2, g;

	// both counters will be using the same gama aproximation of 0.95
	cin >> e1 >> e2 >> g;

    srand(time(nullptr));
	
	for(int i=1000; i<=1000000; i*=10) {
		for(int j=0; j<10000; j++) {
			// different seed everytime a new counter is running
			srand(rand());

			cerr << "new exec: " << i << " " << j <<  endl; 

			// counter using e = 0.005
			MorrisCounter counter1(e1, g);
			// counter using base 2
			MorrisCounter counter2(e2, g);

			for(int k=0; k<i; k++){
				counter1.update();
				counter2.update();
			};

			file_out1 << i << "," << counter1.query() << endl;
			file_out2 << i << "," << counter2.query() << endl;
		};
	};
	return 0;
}