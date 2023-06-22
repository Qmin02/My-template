#include<bits/stdc++.h>

using namespace std;
using i64 = long long;

int __FAST_IO__ = []() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return 0;
}();

template<int(*op)(int, int), int(*e)()>
class Fenwick{
    public:
        explicit Fenwick(int n): n(_n), tr(n, e()){}
        void apply_single(int p, int v){
            assert(0 <= p and p <= _n);
            if(p == 0)return;
            for(int i = p; i <= _n; i += (i & -i))tr[i] = op(tr[i], p);
        }
        int prod(int r){
            assert(0 <= r and r <= _n);
            if(r == 0)return 0;
            int ans = e();
            for(int i = r; i; i -= (i & -i))ans = op(ans, tr[i]);
            return ans;
        }
    private:
        int _n;
        vector<int> tr;
};


