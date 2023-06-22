// 平面最近点对问题
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
#define debugs
#define inf 1 << 31 - 1
#define eps 1e-8
int sgn(double x){return x > eps ? 1 : x < -eps ? -1 : 0;}

struct Point2{
    double x, y;
    Point2():x(0), y(0){}
    Point2(double x, double y):x(x), y(y){}

    // 向量加
    Point2 operator + (const Point2 &a)const{
        return Point2(x + a.x, y + a.y);
    }
    // 向量减
    Point2 operator - (const Point2 &a)const{
        return Point2(x - a.x, y - a.y);
    }
    // 向量数乘
    Point2 operator * (const double a)const{
        return Point2(a * x, a * y);
    }
    // 向量数除
    Point2 operator / (const double a)const{
        return Point2(x / a, y / a);
    }

    // 向量点积
    double operator * (const Point2 &a)const{
        return x * a.x + y * a.y;
    }
    // 向量叉积
    double operator ^ (const Point2 &a)const{
        return x * a.y - a.x * y;
    }

    // 向量旋转
    Point2 rotate(double a){
        return Point2(x * cos(a) - y * sin(a), y * cos(a) - x * sin(a));
    }
    // 向量模长
    double moudle(){
        return sqrt(x * x + y * y);
    }
}tmp[maxn];

// 存储点
int polygon_num; // 点数
Point2 polygon[maxn]; // 各点

int cmp_x_y(Point2 p1, Point2 p2){
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
int cmp_y(Point2 p1, Point2 p2){
    return p1.y < p2.y;
}
double dis(Point2 p1, Point2 p2){
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double solve(int l, int r){
    if(l == r)return inf;
    if(l + 1 == r)return dis(polygon[l], polygon[r]);
    int mid = (l + r) >> 1;
    double ans = min(solve(l, mid), solve(mid + 1, r));
    int num = 0;
    for(int i = l; i <= r; ++i){
        if(fabs(polygon[mid].x - polygon[i].x) < ans)tmp[++num] = polygon[i];
    }
    sort(tmp + 1, tmp + num + 1, cmp_y);
    // 这里ans会随着循环改变使得第二重循环的判定条件随着改变
    // 不知什么原因
    // 正确
    for(int i = 1; i <= num; ++i){
        for(int j = i + 1; j <= num && tmp[j].y - tmp[i].y < ans; ++j){
            ans = min(ans, dis(tmp[i], tmp[j]));
        }
    }
    // 错误
    // for(int i = 1; i <= num; ++i){
    //     for(int j = 1; j < i && tmp[j].y - tmp[i].y < ans; ++j){
    //         ans = min(ans, dis(tmp[i], tmp[j]));
    //     }
    // }
    return ans;
}

int main(){

    // #ifdef debug
    // cout << "man" << endl;
    // #endif
    // #ifndef debug
    // cout << "woman" << endl;
    // #endif

    while(cin >> polygon_num){
        for(int i = 1; i <= polygon_num; ++i)scanf("%lf%lf", &polygon[i].x, &polygon[i].y);
        sort(polygon + 1, polygon + polygon_num + 1, cmp_x_y);
        printf("%.4lf\n", solve(1, polygon_num));
    }
    return 0;
}
