// 随机增量法
// 最小覆盖圆问题
# include <bits/stdc++.h>
using namespace std;

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


// n为点数,r为最小覆盖圆半径平方
int n;
double r;
Point2 p[maxn]; // 存储点

inline double dis(int x, int y){
    return (p[x].x - p[y].x) * (p[x].x - p[y].x) + (p[x].y - p[y].y) * (p[x].y - p[y].y);
}
inline bool incircle(int op){
    return dis(op, 0) <= r;
}

void MSCM(){
    random_shuffle(p + 1, p + n + 1);//(随机化,避免最坏情况的发生)
    for(int i = 1; i <= n; ++i){
        if(!incircle(i)){
            p[0] = p[i], r = 0;
            for(int j = 1; j < i; ++j){
                if(!incircle(j)){
                    p[0] = (p[i] + p[j]) / 2, r = dis(i, 0);
                    for(int k = 1; k < j; ++k){
                        if(!incircle(k)){
                            double a1 = p[j].x - p[i].x, b1 = p[j].y - p[i].y, c1 = (a1 * a1 + b1 * b1) / 2;
                            double a2 = p[k].x - p[i].x, b2 = p[k].y - p[i].y, c2 = (a2 * a2 + b2 * b2) / 2;
                            double d = a1 * b2 - a2 * b1;
                            p[0] = Point2(p[i].x + (c1 * b2 - c2 * b1) / d, p[i].y + (a1 * c2 - a2 * c1) / d), r = dis(i, 0);
                        }
                    }
                }
            }
        }
    }
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; ++i)cin >> p[i].x >> p[i].y;
    MSCM();
    printf("%.10lf\n%.10lf %.10lf\n", sqrt(r), p[0].x, p[0].y);
    return 0;
}
