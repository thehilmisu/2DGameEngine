#ifndef POINT_H
#define POINT_H

class Point
{
public:
    float x;
    float y;

    Point() : x(0), y(0) {}
    Point(float x, float y) : x(x), y(y) {}

    inline Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    inline Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    inline friend Point operator+=(Point& p1, const Point& p2) {
        p1.x += p2.x;
        p1.y += p2.y;
        return p1;
    }

    inline friend Point operator-=(Point& p1, const Point& p2) {
        p1.x -= p2.x;
        p1.y -= p2.y;
        return p2;
    }

    inline Point operator*(float scalar) const {
        return Point(x * scalar, y * scalar);
    }

    inline Point operator/(float scalar) const {
        return Point(x / scalar, y / scalar);
    }

    inline friend Point operator*=(Point& p, float scalar) {
        p.x *= scalar;
        p.y *= scalar;
        return p;
    }

    inline friend Point operator/=(Point& p, float scalar) {
        p.x /= scalar;
        p.y /= scalar;
        return p;
    }
};

#endif