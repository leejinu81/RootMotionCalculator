#include "Vector3Nx.h"
#include <algorithm>
#include <iostream>

Vector3Nx::Vector3Nx() : x_(0), y_(0), z_(0)
{}

Vector3Nx::Vector3Nx(float x, float y, float z) : x_(x), y_(y), z_(z)
{}

const Vector3Nx Vector3Nx::zero{};
const Vector3Nx Vector3Nx::one{1, 1, 1};

Vector3Nx Vector3Nx::operator+(const Vector3Nx& other) const
{
    return Vector3Nx(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector3Nx Vector3Nx::operator-(const Vector3Nx& other) const
{
    return Vector3Nx(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Vector3Nx Vector3Nx::Scale(const Vector3Nx& left, const Vector3Nx& right)
{
    return Vector3Nx(left.x_ * right.x_, left.y_ * right.y_, left.z_ * right.z_);
}

Vector3Nx Vector3Nx::operator*(const float d) const
{
    return Vector3Nx(x_ * d, y_ * d, z_ * d);
}

Vector3Nx Vector3Nx::Lerp(const Vector3Nx& a, const Vector3Nx& b, float t)
{
    auto clampT = std::clamp(t, 0.0f, 1.0f);
    return Vector3Nx(a.x_ + ((b.x_ - a.x_) * clampT),
                     a.y_ + ((b.y_ - a.y_) * clampT),
                     a.z_ + ((b.z_ - a.z_) * clampT));
}

Vector3Nx& Vector3Nx::operator=(const Vector3Nx& other)
{
    x_ = other.x_;
    y_ = other.y_;
    z_ = other.z_;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector3Nx& vector3Nx)
{
    os << "<" << vector3Nx.x_ << ", " << vector3Nx.y_ << ", " << vector3Nx.z_ << ">";
    return os;
}

float Vector3Nx::X() const
{
    return x_;
}

float Vector3Nx::Y() const
{
    return y_;
}

float Vector3Nx::Z() const
{
    return z_;
}
