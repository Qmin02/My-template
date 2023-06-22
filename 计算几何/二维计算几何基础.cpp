// 二维计算几何基础
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
        return Point2(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
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


typedef Line Line, Segement;
struct Line{ // 直线或线段
    Point p1, p2;
    Vector v;
    Line(Point p1, Point p2):p1(p1), p2(p2), v(p2 - p1){}
}lines[maxn], segements[maxn];


// 计算两点间距离
double Point_Point_Distance(Point point1, Point point2){
    return (point1 - point2).moudle();
}

// 判断点线关系
// 返回1:点在直线左侧方 返回0:点在直线上 返回-1:点在直线右侧方
int Point_Line_Relation(Point point, Line line){
    return sgn((line.p2 - line.p1) ^ (point - line.p1));
}
// 计算点线距离
double Point_Line_Distance(Point point, Line line){
    return fabs((point - line.p1) ^ line.v);
}
// 计算点到直线的投影点
Point Point_Line_Projection(Point point, Line line){
    int d = ((point - line.p1) * line.v) / line.v.moudle();
    return line.p1 + d * line.v;
}
// 计算点到直线的对称点symmetry
Point Point_Line_Symmetry(Point point, Line line){
    return point + (Point_Line_Projection - point) * 2;
}

// 判断点是否在线段上
bool On_Segement(Point point, Segement segement){
    return !Point_Line_Relation(point, segement) && (segement.p1 - point) * (segement.p2 - point) <= 0;
}
// 点与线段距离垂线距离可以转化为点到直线距离

// 判断线段是否相交(包括端点)(如不包括端点则去掉所有判断的等于号)
// 返回1:线段相交 返回0:线段不相交
bool Segment_Intersect(Point2 a, Point2 b, Point2 c, Point2 d, Segement segement1, Segement segement2){
    return min(segement1.p1.x, segement1.p1.x) <= max(segement2.p1.x, segement2.p1.x) \
        && min(segement2.p1.x, segement2.p1.x) <= max(segement1.p1.x, segement1.p1.x) \
        && min(segement1.p1.y, segement1.p1.y) <= max(segement2.p1.y, segement2.p1.y) \
        && min(segement2.p1.y, segement2.p1.y) <= max(segement1.p1.y, segement1.p1.y) \
        && ToLeft(segement1.v, segement2.p1 - segement1.p1) * ToLeft(segement1.v, segement2.p2 - segement1.p1) <= 0 \
        && ToLeft(segement2.v, segement1.p1 - segement2.p1) * ToLeft(segement2.v, segement1.p2 - segement2.p1) <= 0;
}
// 两相交线段可以转化为下面两相交直线的交点


// 判断两直线关系
// 返回1:相交 返回-1：重合 返回0:平行
int Line_Line_Relation(Line line1, Line line2){
    if(!sgn(line1.v ^ line2.v)){
        if(!Point_Line_Relation(line1.p1, line2))return -1;
        else return 0;
    }else return 1;
}
// 计算两相交直线交点
Point Line_Intersection(Line line1, Line line2){
    Vector u = line1.p1 - line2.p1;
    double d = ((line2.v ^ u) / (line1.v ^ line2.v));
    return line1.p1 + line1.v * d;
}

typedef Polygon Convex, Triangle, Polygon;
struct Polygon{
    static const int maxn = 105;
    int num;
    Point point[maxn];
}convex, triangle, polygon;

// 三角形
// 求三角形重心
Point Triangle_Braycenter(Triangle triangle){
    return (triangle.point[1] + triangle.point[2] + triangle.point[3]) / 3;
}
// 求三角形内心
Point Triangle_Innercenter(Triangle triangle){
    double len1 = (triangle.point[1] - triangle.point[2]).moudle();
    double len2 = (triangle.point[2] - triangle.point[3]).moudle();
    double len3 = (triangle.point[3] - triangle.point[1]).moudle();
    return (triangle.point[1] * len2 + triangle.point[2] * len3 + triangle.point[3] * len1) / (len1 + len2 + len3); // 内心公式
}
// 求三角形外心
Point Triangle_Circumcenter(Triangle triangle){
    double d1 = triangle.point[2] * triangle.point[2] - triangle.point[1] * triangle.point[1];
    double d2 = triangle.point[3] * triangle.point[3] - triangle.point[2] * triangle.point[2];
    double d = 2.0 * ( (triangle.point[3].y - triangle.point[2].y) * (triangle.point[2].x - triangle.point[1].x) \ 
                   - (triangle.point[2].y - triangle.point[1].y) * (triangle.point[3].x - triangle.point[2].x) );
    return  Point( ((triangle.point[3].y - triangle.point[2].y) * d2 - (triangle.point[2].y - triangle.point[1].y) * d1) / d, \
                   ((triangle.point[2].x - triangle.point[1].x) * d2 - (triangle.point[3].x - triangle.point[2].x) * d1) / d  ); // 外心公式
}
// 求三角形垂心
Point Triangle_Orthocenter(Triangle triangle){
    return 3.0 * Triangle_Braycenter(triangle) - 2.0 * Triangle_Circumcenter(triangle); // 利用重心、外心、垂心关系
}

// 多边形
// 判断点是否在多边形内(包括边)(若不包括边则使得On_Segement返回0)
bool Point_In_Polygon(Point point, Polygon polygon){
    int flag = 0;
    Point2 p1, p2;
    for(int i = 1, j = polygon.num; i <= polygon.num; j = i++){
        p1 = polygon.point[i], p2 = polygon.point[j];
        if(On_Segement(point, Segement(p1, p2)))return 1;
        if((min(p1.y, p2.y) < point.y && point.y <= max(p1.y, p2.y)) && sgn(point.x - (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) - p1.x) < 0){
            flag = !flag;
        }
    }
    return flag;
}
// 判断线段是否在多边形内(包括边)(若不包括边则相应改变Point_In_Polygon)
bool Segement_In_Polygon(Segement segement, Polygon polygon){
    return Point_In_Polygon(segement.p1, polygon) && Point_In_Polygon(segement.p2, polygon);
}
// 求多边形重心
Point Polygon_Braycenter(Polygon polygon){
    Point braycenter; double areas = 0.0;
    Point p0 = polygon.point[1];
    for(int i = 2; i < polygon.num; ++i){
        Point p1 = polygon.point[i], p2 = polygon.point[i + 1];
        double area = Area2(p1 - p0, p2 - p0) / 2;
        braycenter += (p0 + p1 + p2) * area;
        areas += area;
    }
    return braycenter / areas / 3;
}
// 求多边形面积
double Polygon_Area(Polygon polygon){
    double ans = 0;
    for(int i = 1, j = polygon.num; i <= polygon.num; j =i++){
        Point p1 = polygon.point[i], p2 = polygon.point[j];
        ans += (p2 ^ p1) / 2;
    }
    return ans;
}

// 圆
struct Circle{
    Point o;
    double r;
}circles[maxn];

// 判断点圆关系
// 返回1:圆内 返回0:圆上 返回-1:圆外
int Point_Circle_Relation(Point point, Circle circle){
    double d = Point_Point_Distance(point, circle.o);
    return sgn(circle.r - d);
}
// 求圆外一点的两个切点
Point pointcut1, pointcut2;
void Point_Circle_Pointcut(Point point, Circle circle){
    double d = Point_Point_Distance(point, circle.o);
    double angle = acos(circle.r / d);
    Vector v = (point - circle.o) * circle.r / d;
    pointcut1 = v.rotate(angle), pointcut2 = v.rotate(-angle);
}

// 判断直线与圆的关系
// 返回1:相交 返回0:相切 返回-1:相离
int Line_Circle_Relation(Line line, Circle circle){
    double d = Point_Line_Distance(circle.o, line);
    return sgn(d - circle.r);
}
// 计算相切直线与圆的切点
Point Tangent_Circle_Pointcut(Line tangent, Circle circle){
    return Point_Line_Projection(circle.o, tangent);
}
// 计算相交直线与圆的两个交点
Point intersection1, intersection2;
void Line_Circle_Intersection(Line line, Circle circle){
    Point midpoint = Point_Line_Projection(circle.o, line);
    double d = Point_Point_Distance(circle.o, midpoint);
    double angle = acos(d / circle.r);
    Vector v = (midpoint - circle.o) * circle.r / d;
    intersection1 = v.rotate(angle), intersection2 = v.rotate(-angle);
}

// 判断线段与圆的关系
int Segement_Circle_Relation(Segement segement, Circle circle){
    int check1 = Point_Circle_Relation(segement.p1, circle.o);
    int check2 = Point_Circle_Relation(segement.p2, circle.o);
    int check = check1 + check2;
    if(!check){
        if(!check1 && !check2)return 1; // 线段两端点均在圆上
        else return 2;                  // 线段一端点在圆内,一段点在圆外
    }else if(check == 1){
        return 3;                       // 线段一端点在圆内,一端点在圆上
    }else if(check == 2){
        return 4;                       // 线段两端点均在圆内
    }else if(check == -1){
        return 5;                       // 线段一端点在圆上,一端点在圆外
    }else{ // check == -2
        return Line_Circle_Relation(segement, circle) + 7; // 6 : 线段两端点均在圆外,与圆相离
    }                                                     // 7 : 线段两端点均在圆外,与圆相切
}                                                        // 8 : 线段两端点均在圆外,与圆相交
// 若求线段与圆的交点,则对应情况调用相应函数即可

// 判断圆与圆的关系
int Circle_Circle_Relation(Circle circle1, Circle circle2){
    if(sgn(circle1.r - circle2.r))swap(circle1, circle2);
    double d = Point_Point_Distance(circle1.o, circle2.o);
    double l = circle2.o - circle1.o, r = circle1.o + circle2.o;
    if(sgn(l - d))return -2;       // 内含
    else if(!sgn(l - d))return -1; // 内切
    else if(!sgn(r - d))return 1;  // 外切
    else if(sgn(r - d))return 2;   // 外离
    else return 0;                 // 相交
}
// 计算两外切圆的切点
Point Circle_Circle_Out_Pointcut(Circle circle1, Circle circle2){
    if(sgn(circle1.r - circle2.r))swap(circle1, circle2);
    return circle1.o + (circle2.o - circle1.o) * circle1.r / (circle1.r + circle2.r);
}
// 求两内切圆的切点
Point Circle_Circle_In_Pointcut(Circle circle1, Circle circle2){
    if(sgn(circle1.r - circle2.r))swap(circle1, circle2);
    return circle1.o + (circle1.o - circle2.o) * circle1.r / (circle2.r - circle1.r);
}
// 计算两相交圆的交点
Point intersection1, intersection2;
void Circle_Circle_Intersection(Circle circle1, Circle circle2){
    double x0 = (circle2.o - circle1.o).x;
    double y0 = (circle2.o - circle1.o).y;
    double M = circle1.r * circle1.r - circle2.r * circle2.r + circle2.o * circle2.o - circle1.o * circle1.o;
    Point p1, p2;
    if(!sgn(x0))p1 = Point(-1.0, M / y0), p2 = Point(1.0, M / y0);
    else if(!sgn(y0))p1 = Point(M / x0, -1.0), p2 = Point(M / x0, 1.0);
    else p1 = Point(0, M / y0), p2 = Point(M / x0, 0);
    Line_Circle_Intersection(Line(p1, p2), circle1);
}
// 计算两相交圆的相交面积
Point Circle_Circle_Intersecting_Area(Circle circle1, Circle circle2){
    Circle_Circle_Intersection(circle1, circle2);
    return Area2(intersection1 - circle1.o, intersection2 - circle1.o) / 2 \
            + Area2(intersection1 - circle2.o, intersection2 - circle2.o) / 2;
}
// 计算圆上的公切线(待补充)

// 多边形与网格相关
// 计算多边形的边上的网格数
int Gcd(int x, int y){return y ? Gcd(y, x % y) : x;}
int Grid_On_Polygon(Polygon polygon){
    int ans = 0;
    for(int i = 1, j = polygon.num; i <= polygon.num; j = i++){
        Vector v = polygon.point[i] - polygon.point[j];
        ans += Gcd(abs(v.x), abs(v.y));
    }
    return ans;
}
// 计算多边形内的网格数
int Grid_In_Polygon(Polygon polygon){
    return (Polygon_Area(polygon) - Grid_On_Polygon(polygon) + 2) / 2; // 运用Pick定理 多边形面积 = 内网格数 + 边上网格数 / 2 - 1
}