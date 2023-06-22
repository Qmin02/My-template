#include<bits/stdc++.h>

using i64 = long long;
//using int128 = __int128_t;
constexpr int P = 998244353;
//constexpr int P = 1000000007;

using T = double;
struct Point {
    T x, y;
    Point (T x = 0, T y = 0) : x(x), y(y) {}

    Point & operator += (const Point & rhs) {
        x += rhs.x, y += rhs.y;
        return *this;
    }
    Point & operator -= (const Point & rhs) {
        x -= rhs.x, y += rhs.y;
        return *this;
    }
    Point & operator *= (const T & rhs) {
        x *= rhs, y *= rhs;
        return *this;
    }
    friend Point operator - (const Point & p) {
        return Point(-p.x, -p.y);
    }
    friend Point operator + (Point lhs, const Point & rhs) {
        return lhs += rhs;
    }
    friend Point operator - (Point lhs, const Point & rhs) {
        return lhs -= rhs;
    }
    friend Point operator * (Point lhs, const T & rhs) {
        return lhs *= rhs;
    }
};
T dot(const Point & lhs, const Point & rhs) {
    return (lhs.x * rhs.x + lhs.y * rhs.y);
}
T cross(const Point & lhs, const Point & rhs) {
    return (lhs.x * rhs.y - lhs.y * rhs.x);
}
