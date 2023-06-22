#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define rep(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define _rep(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)
#define repL(i, a, b) for(LL i = (LL)(a); i <= (LL)(b); ++i)
#define _repL(i, a, b) for(LL i = (LL)(a); i >= (LL)(b); --i)
const int inv2 = 500000004, inv3 = 333333336, inv6 = 166666668;
const int maxn = 1e4 + 10;
const int mod = 1e9 + 7;
inline LL rd(){ LL ans = 0; char last = ' ', ch = getchar();
        while(!isdigit(ch))last = ch, ch = getchar();
        while(isdigit(ch))ans = (ans << 1) + (ans << 3) + (ch ^ 48), ch = getchar();
        if(last == '-')ans = -ans; return ans;
}
inline int read(){ int ans = 0; char last = ' ', ch = getchar();
        while(!isdigit(ch))last = ch, ch = getchar();
        while(isdigit(ch))ans = (ans << 1) + (ans << 3) + (ch ^ 48), ch = getchar();
        if(last == '-')ans = -ans; return ans;
}
/*---------------------------------the head----------------------------------*/

int n, a, b, c, d, cnt;
struct scanline{
    int x, dy, uy, io;
    scanline(){}
    scanline(int x, int dy, int uy, int io):x(x), dy(dy), uy(uy), io(io){}
}line[maxn << 1];
bool cmp(scanline x, scanline y){return x.x < y.x  || (x.x == y.x && x.io > y.io);}

int cover[maxn << 2], ls[maxn << 2], rs[maxn << 2], lens[maxn << 2], parts[maxn << 2], yy[maxn << 1];
void build(int l, int r, int rt){
    if(l == r){cover[rt] = ls[rt] = rs[rt] = lens[rt] = parts[rt] = 0; return;}
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1); build(mid + 1, r, rt << 1 | 1);
}
void push_down(int l, int r, int rt){
    if(cover[rt]){
        lens[rt] = yy[r + 1] - yy[l];
        ls[rt] = 1; rs[rt] = 1; parts[rt] = 1;
    }else if(l == r){
        lens[rt] = ls[rt] = rs[rt] = parts[rt] = 0;
    }else{
        lens[rt] = lens[rt << 1] + lens[rt << 1 | 1];
        ls[rt] = ls[rt << 1]; rs[rt] = rs[rt << 1 | 1];
        parts[rt] = parts[rt << 1] + parts[rt << 1 | 1] - (rs[rt << 1] && ls[rt << 1 | 1]);
    }
}
void update(int l, int r, int ql, int qr, int io, int rt){
    if(l > qr || r < ql)return;
    if(ql <= l && r <= qr){
        cover[rt] += io;
        push_down(l, r, rt);
        return;
    }
    int mid = (l + r) >> 1;
    update(l, mid, ql, qr, io, rt << 1);
    update(mid + 1, r, ql, qr, io, rt << 1 | 1);
    push_down(l, r, rt);
}

int main(){
    freopen("in.txt", "r", stdin);
    n = read();
    rep(i, 1, n){
        a = read(), b = read(), c = read(), d = read(); 
        // cout << a << " " <<  b << " " << c << " " << d << endl;
        line[++cnt] = scanline(a, b, d, 1); yy[cnt] = b;
        line[++cnt] = scanline(c, b, d, -1); yy[cnt] = d;
    }
    sort(yy + 1, yy + cnt + 1); sort(line + 1, line + cnt + 1, cmp);
    int len = unique(yy + 1, yy + cnt + 1) - (yy + 2);
    build(1, len, 1);  LL ans = 0; int pre = 0;
    for(int i = 1; i <= cnt; ++i){
        int ql = lower_bound(yy + 1, yy + len + 2, line[i].dy) - yy;
        int qr = lower_bound(yy + 1, yy + len + 2, line[i].uy) - yy - 1;
        int io = line[i].io;
        update(1, len, ql, qr, io, 1);
        ans += abs(lens[1] - pre) + 2 * parts[1] * (line[i + 1].x - line[i].x);
        pre = lens[1];
        // cout << i << ":" << lens[1] << " " << parts[1] << endl;
        // cout << ans << endl;
    }
    cout << ans << endl;
    return 0;
}