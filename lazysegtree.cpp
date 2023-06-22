#include<bits/stdc++.h>

using namespace std;
using i64 = long long;

int __FAST_IO__ = []() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return 0;
}();

template<class S, S (*op)(S, S), S (*e)(),
         class F, S (*mapping)(S, F), F (*comp)(F, F), F (*id) ()>
class Lazyseg {
    public:
        Lazyseg() : Lazyseg(0){}
        explicit Lazyseg(int n) : Lazyseg(vector<S>(n, e())){}
        explicit Lazyseg(const vector<S>& a) : _n(a.size()) {
            log = 0;
            while((1 << log) < _n){ log++; }
            size = 1 << log;
            tr = vector<S>(size << 1, e());
            lz = vector<F>(size, id());
            for(int i = 0; i < _n; ++i){
                tr[size + i] = a[i];
            }
            for(int i = size - 1; i >= 1; --i){ update(i); }
        }

        void set(int p, S x){
            assert(0 <= p && p < _n);
            p += size;
            for(int i = log; i >= 1; --i){ push(p >> i); }
            tr[p] = x;
            for(int i = 1; i <= log; ++i){ update(p >> i); }
        }
        S get(int p) {
            assert(0 <= p && p < _n);
            p += size;
            for(int i = log; i >= 1; --i){ push(p >> i); }
            return tr[p];
        }

        S prod(int l, int r) {
            assert(0 <= l && l <= r && r <= _n);
            if(l == r){ return e(); }

            l += size;
            r += size;

            for(int i = log; i >= 1; --i){
                if(((l >> i) << i) != l){ push(l >> i); }
                if(((r >> i) << i) != r){ push((r - 1) >> i); }
            }

            S resL = e(), resR = e();
            while(l < r){
                if(l & 1){ resL = op(resL, tr[l++]); }
                if(r & 1){ resR = op(tr[--r], resR); }
                l >>= 1;
                r >>= 1;
            }
            return op(resL, resR);
        }
        S all_prod() const { return tr[1]; }

        void apply_single(int p, F f) {
            assert(0 <= p && p < _n);
            p += size;
            for(int i = log; i >= 1; --i){ push(p >> i); }
            all_apply(p, f);
            for(int i = 1; i <= log; ++i){ update(p >> i); }
        }
        void apply(int l, int r, F f) {
            assert(0 <= l && l <= r && r <= _n);
            if(l == r){ return; }

            l += size;
            r += size;

            for(int i = log; i >= 1; --i){
                if(((l >> i) << i) != l){ push(l >> i); }
                if(((r >> i) << i) != r){ push((r - 1) >> i); }
            }

            int lx = l, rx = r;
            while(l < r){
                if(l & 1){all_apply(l++, f);}
                if(r & 1){all_apply(--r, f);}
                l >>= 1;
                r >>= 1;
            }
            l = lx, r = rx;

            for(int i = 1; i <= log; ++i){
                if(((l >> i) << i) != l){ update(l >> i); }
                if(((r >> i) << i) != r){ update((r - 1) >> i); }
            }
        }

    private:
        int _n, size, log;
        vector<S> tr;
        vector<F> lz;

        void update(int k) {
            tr[k] = op(tr[k << 1], tr[k << 1 | 1]);
        }
        void all_apply(int k, F f) {
            tr[k] = mapping(tr[k], f);
            if(k < size){
                lz[k] = comp(lz[k], f);
            }
        }
        void push(int k){
            all_apply(k << 1, lz[k]);
            all_apply(k << 1 | 1, lz[k]);
            lz[k] = id();
        }
};

