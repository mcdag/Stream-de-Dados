#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Kmv.h"

int main(){
	string filename1("output1.csv"), filename2("output2.csv");
    fstream file_out1, file_out2;

    file_out1.open(filename1, std::ios_base::out);
	file_out2.open(filename2, std::ios_base::out);

    file_out1 << "K,R,Expected,Result,Error" << endl;
    file_out2 << "K,R,Expected,Result,Error" << endl;

    int total, unique;
    cin >> total >> unique;

    vector<string> strings;
    string str;

    // reading the input to insert it in a vector
    for(int i=0; i<total; i++) {
        cin >> str;
        strings.push_back(str);
    };

    vector<pair<int, int> > KRsChangingK;

    // creating differents Rs
    for(int i=200; i<unique; i+=200){
        KRsChangingK.push_back(make_pair(i,unique));
    };

    // interating the Ks vector
    for(auto vec : KRsChangingK) {
        Kmv kmv(vec.first, vec.second);
        for(string str : strings){
            kmv.update(str);
        }
        file_out1 << vec.first << "," << vec.second << "," << unique << "," << kmv.query() << "," << abs((unique - kmv.query())/(unique*1.0)) << endl;
    };

    vector<pair<int, int> > KRsChangingR;

    // creating differents Rs
    for(int i=200; i<unique; i+=200){
        KRsChangingR.push_back(make_pair(0.2*unique, i));
    };

    // interating the Rs vector
    for(auto vec : KRsChangingR) {
        Kmv kmv(vec.first, vec.second);
        for(string str : strings){
            kmv.update(str);
        }
        file_out2 << vec.first << "," << vec.second << "," << unique << "," << kmv.query() << "," << abs((unique - kmv.query())/(unique*1.0)) << endl;
    }

    return 0;
}
