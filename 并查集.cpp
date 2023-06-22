#include<bits/stdc++.h>

using namespace std;
using i64 = long long;

class Dsu{
    public:
        explicit Dsu(int n): _n(n), fa(n), siz(n, 1){iota(fa.begin(), fa.end(), 0);}
        int leader(int x){while(x != fa[x])x = fa[x] = fa[fa[x]]; return x;}
        int same(int x, int y){return leader(x) == leader(y);}
        int merge(int x, int y){
            x = leader(x), y = leader(y);
            if(x == y)return 0;
            if(siz[x] < siz[y])swap(x, y);
            fa[y] = x, siz[x] += siz[y];
            return 1;
        }
    private:
        int _n;
        vector<int> fa, siz;
};
