#include <stdio.h>
#include <queue>
#include <set>

using namespace std;

class Kmv {
    public:
        void update(string x);
        double query();
        double merge(Kmv x);
        double intersect(Kmv x);
        Kmv(int k, int r);

    private:
        struct Compare {
            bool operator()(const pair<string, int>& x, const pair<string, int>& y){
                return x.second < y.second;
            }
        };
        int r;
        int k;
        int hash(string x);
        priority_queue <pair<string, int>, vector<pair<string, int> >, Compare> list;
        set <string> set;
};