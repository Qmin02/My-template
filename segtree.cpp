#include<bits/stdc++.h>

using namespace std;
using i64 = long long;

int __FAST_IO__ = []() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return 0;
}();

// no-lazy version, op for merge 
template<class S, S (*op)(S, S), S (*e)()> class Seg{
    public:
        Seg() : Seg(0) {}
        explicit Seg(int n) : Seg(vector<S>(n, e())) {}
        explicit Seg(const vector<S> & v) : _n(v.size()) {
            log = 0;
            while((1 << log) < _n) { log++; }
            size = 1 << log;
            tr = vector<S>(size << 1, e());
            for(int i = 0; i < _n; ++i){
                tr[size + i] = v[i];
            }
            for(int i = size - 1; i > 0; --i){ update(i); }
        }

        void set(int p, S v) {
            assert(0 <= p && p < _n);
            p += size;
            tr[p] = v;
            for(int i = 1; i <= log; ++i){
                update(p >> i);
            }
        }
        S get(int p) const {
            assert(0 <= p && p < _n);
            return tr[p + size];
        }

        S prod(int l, int r) const {
            assert(0 <= l && l <= r && r <= _n);
            if(l == r) { return e(); }

            l += size;
            r += size;

            S resL = e(), resR = e();
            while(l < r){
                if(l & 1) { resL = op(resL, tr[l++]); }
                if(r & 1) { resR = op(tr[--r], resR); }
                l >>= 1;
                r >>= 1;
            }
            return op(resL, resR);
        }
        S all_prod() const { return tr[1]; }

    private:
        int _n, size, log;
        vector<S> tr;

        void update(int k) {
            assert(1 <= k && k < size);
            tr[k] = op(tr[k << 1], tr[k << 1 | 1]);
        }
};