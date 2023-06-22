/* 
    扫描线算法
    2021.10.21
    正常线段树要开4倍空间
    扫描线对于每个矩形有两条扫描线，所以至少开八倍空间
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define rep(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define _rep(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)
#define repL(i, a, b) for(LL i = (LL)(a); i <= (LL)(b); ++i)
#define _repL(i, a, b) for(LL i = (LL)(a); i >= (LL)(b); --i)
const int inv2 = 500000004, inv3 = 333333336, inv6 = 166666668;
const int maxn = 1e6 + 5;
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

//求矩阵面积并
int n, a, b, c, d, cnt;
struct scanline{
	int x;
	int dy, uy;
	int io;
	scanline(){}
	scanline(int x, int dy, int uy, int io):x(x), dy(dy), uy(uy), io(io){}
}line[maxn << 1];
int cmp(scanline x, scanline y){return x.x < y.x && (x.x == y.x && x.io > y.io);}


int cover[maxn << 2], lens[maxn << 2], yy[maxn << 1];
void build(int l, int r, int rt){
    if(l == r){cover[rt] = lens[rt] = 0; return;}
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1); build(mid + 1, r, rt << 1 | 1);
}
void push_down(int l, int r, int rt){
	if(cover[rt])lens[rt] = yy[r + 1] - yy[l];
	else if(l == r)lens[rt] = 0;
	else lens[rt] = lens[rt << 1] + lens[rt << 1 | 1];
}
void update(int l, int r, int ql, int qr, int rt, int io){
    if(r < ql || l > qr)return;
    if(ql <= l && r <= qr){
        cover[rt] += io;
        push_down(l, r, rt);
        return;
    }
    int mid = (l + r) >> 1;
    update(l, mid, ql, qr, rt << 1, io);
    update(mid + 1, r, ql, qr, rt << 1 | 1, io);
    push_down(l, r, rt);
}


int main(){
    freopen("in.txt", "r", stdin);
    n = read();
    rep(i, 1, n){
        a = read(), b = read(), c = read(), d = read();
        line[++cnt] = scanline(a, d, b, 1); yy[cnt] = b;
        line[++cnt] = scanline(c, d, b, -1); yy[cnt] = d;
    }
    sort(yy + 1, yy + cnt + 1); sort(line + 1, line + cnt + 1, cmp);
	int len = unique(yy + 1, yy + cnt + 1) - (yy + 2);
    build(1, len, 1); LL ans = 0;
    for(int i = 1; i <= cnt; ++i){
        ans += 1ll * lens[1] * (line[i].x - line[i - 1].x);
        int ql = lower_bound(yy + 1, yy + len + 2, line[i].dy) - yy;
        int qr = lower_bound(yy + 1, yy + len + 2, line[i].uy) - yy - 1;
        int io = line[i].io;
        update(1, len, ql, qr, 1, io);
    }
    cout << ans << endl;
    return 0;
}
