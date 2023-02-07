#include <stdio.h>
#include <queue>
#include <set>

using namespace std;

class Kmv {
    public:
        void update(string x);
        long double query();
        long double merge(Kmv x);
        long double intersect(Kmv x);
        Kmv(int k, long long r, int prime);

    private:
        struct Compare {
            bool operator()(const pair<string, long long>& x, const pair<string, long long>& y){
                return x.second < y.second;
            }
        };
        int k;
        long long r;
        long long prime;
        long long hash(string x);
        priority_queue <pair<string, long long>, vector<pair<string, long long> >, Compare> list;
        set <string> set;
};