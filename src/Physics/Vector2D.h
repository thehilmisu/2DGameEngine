#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
    public:
        float X, Y;

    public:
        Vector2D(float x=0, float y=0) : X(x), Y(y) {}

        //override + operator to add 2 vector together
        inline Vector2D operator+(const Vector2D& v2) const{
            return Vector2D(X + v2.X, Y + v2.Y);
        }

        //override - operator to substract 2 vector together
        inline Vector2D operator-(const Vector2D& v2) const{
            return Vector2D(X - v2.X, Y - v2.Y);
        }

        //override * operator.
        inline Vector2D operator*(const float& scalar) const{
            return Vector2D(X * scalar, Y * scalar);
        }

};

#endif