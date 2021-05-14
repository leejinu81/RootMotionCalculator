#pragma once

class Vector3Nx final
{
public:
    explicit Vector3Nx();

    explicit Vector3Nx(float x, float y, float z);

    Vector3Nx operator+(const Vector3Nx &other) const;

    Vector3Nx operator-(const Vector3Nx &other) const;

    Vector3Nx operator*(float d) const;

    Vector3Nx &operator=(const Vector3Nx &other);

    static Vector3Nx Scale(const Vector3Nx &left, const Vector3Nx &right);

    static Vector3Nx Lerp(const Vector3Nx &a, const Vector3Nx &b, float t);

    static const Vector3Nx zero;
    static const Vector3Nx one;
    const float &x = x_;
    const float &y = y_;
    const float &z = z_;

private:
    float x_;
    float y_;
    float z_;
};