#include <math.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <set>
#include "Kmv.h"

using namespace std; 

Kmv::Kmv(int k, int r) {
    this->k = k;
    this->r = r;
};

int Kmv::hash(string x) {
    int y = 0;
    for(int i=0; i<x.length(); i++){
        y *= 131;
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

double Kmv::query(){
    if(list.size() < k) {
        return list.size();
    };
    int x = list.top().second;
    return (k - 1) * (r * 1.0/x);
};

double Kmv::merge(Kmv newKmv){
    priority_queue <pair<string, int>, vector<pair<string, int> >, Compare> originalList;

    originalList = list;

    while(!newKmv.list.empty()){
        update(newKmv.list.top().first);
        newKmv.list.pop();
    };
    
    double result = query();
    list = originalList;

    return result;
};

double Kmv::intersect(Kmv newKmv){
    int intersections = 0;
    for(auto itr : newKmv.set){
        if(set.count(itr) == 1){
            intersections++;
        }
    }
    int interval = min(list.top().second, newKmv.list.top().second);

    return ((r*1.0)/interval)*intersections;
};
