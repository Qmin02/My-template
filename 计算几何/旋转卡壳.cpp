// 旋转卡壳算法解决凸包问题
#include <bits/stdc++.h>
using namespace std;

// 运用凸包算法先求出凸包
#define eps 1e-8
const int maxn = 1e5 + 5;
inline int sgn(double x){return x > eps ? 1 : x < -eps ? -1 : 0;}

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
};

// 凸包点集
int polygon_num; // 多边形点数
Point2 polygon[maxn]; // 逆时针存储多边形各点

int top, stk[maxn]; // 凸包点数,排序后polygon中作为凸包的序号
int used[maxn]; // Andrew算法需要使用

// Graham扫描法求凸包(stk存储凸包闭环,即最后一个点就是起始点)
int Graham_sort0(Point2 p1, Point2 p2){
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
int Graham_sort1(Point2 p1, Point2 p2){ //极角排序
    double op = (p1 - polygon[1]) ^ (p2 - polygon[1]);
    if(!sgn(op))return (p1 - polygon[1]).moudle() <= (p2 - polygon[1]).moudle();
    else return op > 0;
}
void Graham(){
    top = 0;
    sort(polygon + 1, polygon + polygon_num + 1, Graham_sort0);
    sort(polygon + 2, polygon + polygon_num + 1, Graham_sort1); stk[++top] = 1;
    for(int i = 2; i <= polygon_num; ++i){
        while(top >= 2 && sgn((polygon[stk[top]] - polygon[stk[top - 1]]) ^ (polygon[i] - polygon[stk[top]])) <= 0)--top;
        stk[++top] = i;
    }
    stk[++top] = 1;
}

// Andrew算法求凸包(stk存储凸包闭环,即最后一个点就是起始点)
int Andrew_sort(Point2 p1, Point2 p2){
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
void Andrew(){
    top = 0;
    sort(polygon + 1, polygon + polygon_num + 1, Andrew_sort); stk[++top] = 1;
    for(int i = 2; i <= polygon_num; ++i){
        while(top >= 2 && sgn((polygon[stk[top]] - polygon[stk[top - 1]]) ^ (polygon[i] - polygon[stk[top]])) <= 0)used[stk[top--]] = 0;
        used[i] = 1;
        stk[++top] = i;
    }
    int tmp = top;
    for(int i = polygon_num - 1; i > 0; --i){
        if(!used[i]){
            while(top > tmp && sgn((polygon[stk[top]] - polygon[stk[top - 1]]) ^ (polygon[i] - polygon[stk[top]])) <= 0)used[stk[top--]] = 0;
            used[i] = 1;
            stk[++top] = i;
        }
    }
}

// 凸包已求出 top和stk[]

// 旋转卡壳
// 求凸包直径
double dis(int x, int y){ // 两点间距离平方
    return (polygon[x].x - polygon[y].x) * (polygon[x].x - polygon[y].x) + (polygon[x].y - polygon[y].y) * (polygon[x].y - polygon[y].y);
}
double check(int p, int q, int op){ // 计算三角形面积的两倍
    return abs((polygon[q] - polygon[p]) ^ (polygon[op] - polygon[p]));
}
double Convex_Bale_Diameter(){ //返回直径平方
    if(top < 3)return 0;
    if(top == 3)return dis(stk[1], stk[2]);
    double ans = 0;
    for(int i = 1, op = 3; i <= top; ++i){
        while(check(stk[i], stk[i + 1], stk[op]) <= check(stk[i], stk[i + 1], stk[op % top + 1]))op = op % top + 1;
        ans = max(ans, max(dis(stk[i], stk[op]), dis(stk[i + 1], stk[op])));
    }
    return ans;
}

// 求凸包最小矩形覆盖

