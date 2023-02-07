#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "Kmv.h"

using namespace std;

vector<int> primes;
double EPSILON = 0.005, DELTA = 0.05;
long long startTime;

void getPrimes(){
    vector<bool> aux;
    int MAX = 1e6;
    for(int i = 0; i < MAX; i++){
        aux.push_back(true);
    }
    for(int i = 2; i < MAX; i++){
        if(aux[i]){
            if(i >= 131){
                primes.push_back(i);
            }
            for(int j = 2*i; j < MAX; j+=i){
                aux[j] = false;
            }
        }
    }
}

int getRandomPrime(){
    srand(rand());
    return primes[rand()%primes.size()];
}

double run(int k, long long r, vector<string> strings, int it){
    startTime = time(NULL);
    vector<Kmv> kmvs;
    vector<double> results;

    int n = (int)ceil((4*log10(1/DELTA)));

    for(int i = 0; i < n; i++){
        srand(rand());
    
        Kmv newKmv = Kmv(k, r, getRandomPrime());
        kmvs.push_back(newKmv);
        int it2 = 0;
        for(string str : strings){
            newKmv.update(str);
        }
        results.push_back(newKmv.query());
    }

    sort(results.begin(), results.end());

    if(n%2 == 0){
        return (results[n/2] + results[(n+2)/2])/2;
    }
    return results[n/2];
}

pair<long double,long double> intersectAndMerge(Kmv kmv1, Kmv kmv2) {
    std::ifstream kmv1_dataset; kmv1_dataset.open("dataset_1");
    std::ifstream kmv2_dataset; kmv2_dataset.open("dataset_2");

    int total, unique;
    string str;

    vector<string> strings1, strings2;

    if(kmv1_dataset.is_open()) {
        kmv1_dataset >> total >> unique;

        for(int i=0; i<total; i++){
            kmv1_dataset >> str;
            strings1.push_back(str);
        }
    }

    if(kmv2_dataset.is_open()) {
        kmv2_dataset >> total >> unique;

        for(int i=0; i<total;i++){
            kmv2_dataset >> str;
            strings2.push_back(str);
        }
    }

    for(string str : strings1){
        kmv1.update(str);
    }

    for(string str : strings2) {
        kmv2.update(str);
    }

    long double intersect = kmv1.intersect(kmv2);
    long double merge = kmv1.merge(kmv2);

    return make_pair(intersect, merge);
}

int main(){
    srand((unsigned) time(NULL));
    getPrimes();

    string filename_intersect("output_intersect.csv"), filename_merge("output_merge.csv");
    fstream file_out_intersect, file_out_merge;

    file_out_intersect.open(filename_intersect, std::ios_base::out);
    file_out_merge.open(filename_merge, std::ios_base::out);

    file_out_intersect << "Expected,Result" << endl;
    file_out_merge << "Expected,Result" << endl;

    for(int i=0; i<100; i++){
        int randomPrime = getRandomPrime();
        Kmv kmv1(80000, 100000, randomPrime), kmv2(80000, 100000, randomPrime);
        
        pair<long double,long double> result;
        result = intersectAndMerge(kmv1, kmv2);

        file_out_intersect << "50000," << result.first << endl;
        file_out_merge << "250000," << result.second << endl;
    }


	// string filename("output.csv"), filename_k("output-ideal-k.csv");
    // fstream file_out, file_out_k;

    // file_out.open(filename, std::ios_base::out);
    // file_out_k.open(filename_k, std::ios_base::out);

    // file_out << "K,R,Expected,Result,Error" << endl;
    // file_out_k << "K,R,Expected,Result,Error" << endl;

    // long long total, unique;
    // cin >> total >> unique;

    // vector<string> strings;
    // string str;

    // // reading the input to insert it in a vector
    // for(long long i=0; i<total; i++) {
    //     cin >> str;
    //     strings.push_back(str);
    // };

    // vector<pair<long long, long long> > KRsChangingK;

    // // creating differents ks
    // for(long long i=int(0.02*unique); i<unique; i+=0.02*unique){
    //     KRsChangingK.push_back(make_pair(i, unique));
    // };

    // // iterating the Ks vector
    // long long i = 0;
    // for(auto vec : KRsChangingK) {
    //     for(int i = 0; i < 50; i++){
    //         double result = run(vec.first, vec.second, strings, i);
    //         double err = abs((unique - result)/(unique*1.0));
    //         file_out << vec.first << "," << vec.second << "," << unique << "," << result << "," << err << endl;
    //     }
    // };

    // // running using the ideal k
    // int k = (int)(20/pow(EPSILON, 2));
    // for(int i = 0; i < 100; i++){
    //     double result = run(k, unique, strings, 0);
    //     double err = abs((unique - result)/(unique*1.0));
    //     file_out_k << k << "," << unique << "," << unique << "," << result << "," << err << endl;   
    // }

    return 0;
}
