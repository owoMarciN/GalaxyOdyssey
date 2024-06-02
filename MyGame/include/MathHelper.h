#ifndef MathHelper_H_
#define MathHelper_H_

#include <cmath>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f
#define RAD_TO_DEG 180.0f / PI

struct Vector2{
    float x, y;
    Vector2(float Nx = 0.0f, float Ny = 0.0f)
        :x(Nx), y(Ny) {};

    float Magnitude(){
        return (x*x) + (y*y);
    }

    float MagnitudeSqrt(){
        return (float)sqrt((x*x) + (y*y));
    }

    Vector2 Normalized(){
        float Mag = MagnitudeSqrt();

        return Vector2(x / Mag, y / Mag);
    }

    Vector2 &operator +=(const Vector2 &rhs){
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2 &operator -=(const Vector2 &rhs){
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2 operator -() const{
        return Vector2(-x, -y);
    }

};

inline Vector2 operator +(const Vector2 &lhs, const Vector2 &rhs){
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2 &lhs, const Vector2 &rhs){
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2 &lhs, const float &rhs){
    return Vector2(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2 Rotatevector(Vector2 & vec, float angle){
    float radAngle = (float)(angle*DEG_TO_RAD);
    return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

inline float DotProduct(const Vector2 &lhs, Vector2 &rhs){
    float dotproduct = acos((lhs.x * rhs.x + lhs.y * rhs.y) / (sqrt(lhs.x*lhs.x + lhs.y*lhs.y) * sqrt(rhs.x*rhs.x + rhs.y*rhs.y)));
    return dotproduct*RAD_TO_DEG;
}

const Vector2 VEC2_ZERO = {0.0f, 0.0f};
const Vector2 VEC2_ONE = {1.0f, 1.0f};
const Vector2 VEC2_UP = {0.0f, 1.0f};
const Vector2 VEC2_RIGHT = {1.0f, 0.0f};

struct BezierCurve{
    Vector2 p0;
    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
    Vector2 calculateCurvePoint(float t){
        float t_2 = t*t;
        float t_3 = t*t_2;
        float u = 1.0f - t;
        float u_2 = u * u;
        float u_3 = u_2 * u;

        Vector2 point = (p0*u_3) + (p1*3*t*u_2) + (p2*3*u*t_2) + p3*t_3;
        point.x = round(point.x);
        point.y = round(point.y);
        return point;
    }
};

#endif