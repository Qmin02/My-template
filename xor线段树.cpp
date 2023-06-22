#include<bits/stdc++.h>

using i64 = long long;
//using int128 = __int128_t;
constexpr int P = 998244353;
//constexpr int P = 1000000007;

template<typename T> 
struct xor_segment{
    std::vector<std::vector<T>> a;
    std::function<T(T, T)> fun;
    T E;

    // 提前将a补成2次幂
    xor_segment(std::vector<T> _a, std::function<T(T, T)> fun, T E) : fun(fun), E(E) {
        int n = _a.size();
        a.resize(2 * n);
        for(int i = 0; i < n; ++i){
            a[n + i].push_back(_a[i]);
        }
        for(int i = n - 1; i >= 1; --i){
            int m = a[i << 1].size();
            for(int j = 0; j < m; ++j){
                a[i].push_back(fun(a[i << 1][j], a[i << 1 | 1][j]));
            }
            for(int j = 0; j < m; ++j){
                a[i].push_back(fun(a[i << 1 | 1][j], a[i << 1][j]));
            }
        }
    }
    
    // [l, r)
    T get(int now, int lnow, int rnow, int l, int r, int x) {
        if(lnow >= r || rnow <= l){
            return E;
        }
        if(l <= lnow && rnow <= r){
            return a[now][x];
        }
        int mid = (lnow + rnow) >> 1;
        // T res = E;
        T resL = get(now << 1, lnow, mid, l, r, x);
        T resR = get(now << 1 | 1, mid, rnow, l, r, x);
        return fun(resL, resR);
    }
};

struct Info {
    i64 sum, prefix, suffix, ans;
    Info() : sum(0), prefix(0), suffix(0), ans(0) {}
    Info(i64 x) {
        i64 v = std::max(x, 0LL);
        sum = x;
        prefix = suffix = ans = v;
    }

    friend std::ostream & operator << (std::ostream & os, const Info v) {
        os << v.sum << ' ' << v.prefix << ' ' << v.suffix << ' ' << v.ans;
        return os;
    }
};

Info fun(Info lhs, Info rhs) {
    Info res;
    res.prefix = std::max(lhs.prefix, lhs.sum + rhs.prefix);
    res.suffix = std::max(rhs.suffix, rhs.sum + lhs.suffix);
    res.sum = lhs.sum + rhs.sum;
    res.ans = std::max({lhs.ans, rhs.ans, lhs.suffix + rhs.prefix});
    return res;
}

void sol() {
    int n;
    std::cin >> n;

    std::vector<Info> a(1 << n);
    for(int i = 0; i < (1 << n); ++i){
        int x;
        std::cin >> x;
        a[i] = Info(x);
        //std::cout << a[i] << '\n';
    }

    xor_segment<Info> f(a, fun, Info());
    
    int q;
    std::cin >> q;
    
    int k = 0;
    while(q--){
        int x;
        std::cin >> x;
        k ^= (1 << x);
        std::cout << f.get(1, 0, 1 << n, 0, 1 << n, k).ans << '\n';
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;  
    //std::cin >> t;

    while(t--){
        sol();
    }

    return 0;
}