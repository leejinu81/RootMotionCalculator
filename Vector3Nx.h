#pragma once

#include <iostream>

class Vector3Nx final
{
public:
    explicit Vector3Nx();

    explicit Vector3Nx(float x, float y, float z);

    Vector3Nx operator+(Vector3Nx const& other) const;

    Vector3Nx operator-(Vector3Nx const& other) const;

    Vector3Nx operator*(float d) const;

    Vector3Nx& operator=(Vector3Nx const& other);

//    Vector3Nx& operator=(Vector3Nx&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, Vector3Nx const& vector3Nx);

    static Vector3Nx Scale(Vector3Nx const& left, Vector3Nx const& right);

    static Vector3Nx Lerp(Vector3Nx const& a, Vector3Nx const& b, float t);

    static Vector3Nx const zero;
    static Vector3Nx const one;

    float X() const;

    float Y() const;

    float Z() const;

private:
    float x_;
    float y_;
    float z_;
};