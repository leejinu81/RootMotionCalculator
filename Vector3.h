#pragma once

#include <iostream>

class Vector3 final
{
public:
    explicit Vector3();

    explicit Vector3(float x, float y, float z);

    Vector3 operator+(Vector3 const& other) const;

    Vector3 operator-(Vector3 const& other) const;

    Vector3 operator*(float d) const;

    Vector3& operator=(Vector3 const& other);

//    Vector3& operator=(Vector3&& other) noexcept;
    bool operator==(Vector3 const& other) const;

    friend std::ostream& operator<<(std::ostream& os, Vector3 const& vector3Nx);

    static Vector3 Scale(Vector3 const& left, Vector3 const& right);

    static Vector3 Lerp(Vector3 const& a, Vector3 const& b, float t);

    static Vector3 const zero;
    static Vector3 const one;

    float X() const;

    float Y() const;

    float Z() const;

private:
    float x_;
    float y_;
    float z_;
};