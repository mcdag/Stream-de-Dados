#include <math.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <set>
#include "Kmv.h"

using namespace std; 

Kmv::Kmv(int k, long long r, int prime) {
    this->k = k;
    this->r = r;
    this->prime = prime;
};

long long Kmv::hash(string x) {
    long long y = 0;
    for(int i=0; i<x.length(); i++){
        y *= this->prime;
        y += x[i];
        y %= r;
    }
    return y + 1;
};

void Kmv::update(string x){
    if(set.count(x) == 0) {
        list.push(make_pair(x, hash(x)));
        set.insert(x);
        if(list.size() > k) {
            set.erase(list.top().first);
            list.pop();
        };
    }
};

long double Kmv::query(){
    if(list.size() < k) {
        return list.size();
    };
    int x = list.top().second;
    return (k - 1) * (r * 1.0/x);
};

long double Kmv::merge(Kmv newKmv){
    priority_queue <pair<string, long long>, vector<pair<string, long long> >, Compare> originalList;

    originalList = list;

    while(!newKmv.list.empty()){
        update(newKmv.list.top().first);
        newKmv.list.pop();
    };
    
    long double result = query();
    list = originalList;

    return result;
};

long double Kmv::intersect(Kmv newKmv){
    int intersections = 0;
    for(auto itr : newKmv.set){
        if(set.count(itr) == 1){
            intersections++;
        }
    }
    int interval = min(list.top().second, newKmv.list.top().second);

    return ((r*1.0)/interval)*intersections;
};
