// 三维计算几何基础
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

#define eps 1e-8
int sgn(double x){return x > eps ? 1 : x < -eps ? -1 : 0;}

struct Point3{ // 三维点或三维向量
    double x, y, z;
    Point3():x(0), y(0), z(0){}
    Point3(double x, double y, double z):x(x), y(y), z(z){}

    // 三维向量加
    Point3 operator + (const Point3 &a)const{
        return Point3(x + a.x, y + a.y, z + a.z);
    }
    // 三维向量减
    Point3 operator - (const Point3 &a)const{
        return Point3(x - a.x, y - a.y, z - a.z);
    }
    // 三维向量数乘
    Point3 operator * (const double a)const{
        return Point3(a * x, a * y, a * z);
    }
    // 三维向量数除
    Point3 operator / (const double a)const{
        return Point3(x / a, y / a, z / a);
    }


    // 三维向量点积
    double operator * (const Point3 &a)const{
        return x * a.x + y * a.y + z * a.z;
    }
    // 三维向量叉积
    Point3 operator ^ (const Point3 &a)const{
        return Point3(y * a.z - a.y * z, a.x * z - x * a.z, x * a.y - a.x * y);
    }


    // 三维向量的模
    double moudle(){
        return sqrt(x * x + y * y + z * z);
    }
}point3[maxn];

struct Plane{ // 三维平面
    Point3 p, n; // 平面上一点和平面法向量
}plane[maxn];

// 判断点是否在平面内 dot为判断点,p为平面上一点,n为平面法向量
// 返回1:点在平面内 返回0:点不在平面内
bool OnPlane(Point3 dot, Point3 p, Point3 n){
    return !((dot - p) * n);
}