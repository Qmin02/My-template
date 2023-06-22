// 半平面交问题
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

#define eps 1e-8
int sgn(double x){return x > eps ? 1 : x < -eps ? -1 : 0;}

typedef Point2 Vector, Point;
struct Point2{ // 表示点或者向量
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

    // 向量逆时针旋转angle
    Point2 rotate(double angle){
        return Point2(x * cos(angle) - y * sin(angle), y * cos(angle) - x * sin(angle));
    }
    // 向量模长
    double moudle(){
        return sqrt(x * x + y * y);
    }
}points[maxn], vectors[maxn];
// 两向量夹角
double Angle(Vector p1, Vector p2){return acos(p1 * p2 / p1.moudle() / p2.moudle());}
// 测试向量p2是否在p1左边
bool ToLeft(Vector p1, Vector p2){return sgn(p1 ^ p2) > 0;}
// 计算向量p1、p2所围成的平行四边形的面积
double Area2(Vector p1, Vector p2){return abs(p1 ^ p2);}

int n; // 直线数量
typedef Line Line, Segement;
struct Line{ // 直线或线段
    Point p1, p2;
    Vector v;
    Line(Point p1, Point p2):p1(p1), p2(p2), v(p2 - p1){}
}lines[maxn], segements[maxn];

int Line_sort(Line point1, Line point2){
    double t1 = atan2(point1.p2.y - point1.p1.y, point1.p2.x - point1.p1.x);
    double t2 = atan2(point2.p2.y - point2.p1.y, point2.p2.x - point2.p1.x);
    if(sgn(t1 - t2))return t1 < t2;
    else return (point2.p1 - point1.p1) * (point2.p2 - point1.p1) > eps;
}

// 判断点线关系
// 返回1:点在直线左侧方 返回0:点在直线上 返回-1:点在直线右侧方
int Point_Line_Relation(Point point, Line line){
    return sgn((line.p2 - line.p1) ^ (point - line.p1));
}
// 计算两相交直线交点
Point Line_Intersection(Line line1, Line line2){
    Vector u = line1.p1 - line2.p1;
    double d = ((line2.v ^ u) / (line1.v ^ line2.v));
    return line1.p1 + line1.v * d;
}


int l, r, q[maxn]; // q[l ~ r]存储半平面交向量的索引
Point2 t[maxn]; // t[l + 1, r]存储r - l个交点
// 返回1:有核  返回0:无核
// 有核 [l, r - 1]为向量
// 无核 [l, r]为向量
int Hotter_Colder(){
    l = 1, r = 0; sort(lines + 1, lines + n + 1, Line_sort);
    for(int i = 1; i <= n; ++i){
        while(r - l >= 1 && Point_Line_Relation(t[r], lines[i]) != 1)--r; // 去尾
        while(r - l >= 1 && Point_Line_Relation(t[l + 1], lines[i]) != 1)++l; // 删头
        // 必须保证有两个向量故r - l >= 1
        q[++r] = i;
        if(r - l >= 1)t[r] = Line_Intersection(lines[q[r - 1]], lines[q[r]]);
    }
    while(r - l >= 2 && Point_Line_Relation(t[r], lines[q[l]]) != 1)--r;
    // 对开头向量进行去尾操作（逻辑闭合）必须保证有三个向量故r - l >= 2
    if(r - l <= 1)return 0;
    t[r + 1] = Line_Intersection(lines[q[l]], lines[q[r]]);
    if(Point_Line_Relation(t[r + 1], lines[l + 1]) != 1)return 0;
    else{++r; return 1;}
}

typedef Polygon Convex, Triangle, Polygon;
struct Polygon{
    static const int maxn = 105;
    int num;
    Point point[maxn];
}convex, triangle, polygon;
// 求多边形面积
double Polygon_Area(Polygon polygon){
    double ans = 0;
    for(int i = 1, j = polygon.num; i <= polygon.num; j =i++){
        Point p1 = polygon.point[i], p2 = polygon.point[j];
        ans += (p2 ^ p1) / 2;
    }
    return ans;
}
