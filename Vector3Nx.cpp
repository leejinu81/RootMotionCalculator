#include "Vector3Nx.h"
#include <algorithm>
#include <iostream>

Vector3Nx::Vector3Nx() : x_(0), y_(0), z_(0) {}

Vector3Nx::Vector3Nx(float x, float y, float z) : x_(x), y_(y), z_(z) {}

Vector3Nx const Vector3Nx::zero{};

Vector3Nx const Vector3Nx::one(1, 1, 1);

Vector3Nx Vector3Nx::operator+(Vector3Nx const& other) const
{
    return Vector3Nx(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector3Nx Vector3Nx::operator-(Vector3Nx const& other) const
{
    return Vector3Nx(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Vector3Nx Vector3Nx::Scale(Vector3Nx const& left, Vector3Nx const& right)
{
    return Vector3Nx(left.x_ * right.x_, left.y_ * right.y_, left.z_ * right.z_);
}

Vector3Nx Vector3Nx::operator*(float const d) const
{
    return Vector3Nx(x_ * d, y_ * d, z_ * d);
}

Vector3Nx Vector3Nx::Lerp(Vector3Nx const& a, Vector3Nx const& b, float t)
{
    auto clampT = std::clamp(t, 0.0f, 1.0f);
    return Vector3Nx(a.x_ + ((b.x_ - a.x_) * clampT),
                     a.y_ + ((b.y_ - a.y_) * clampT),
                     a.z_ + ((b.z_ - a.z_) * clampT));
}

Vector3Nx& Vector3Nx::operator=(Vector3Nx const& other)
{
    x_ = other.x_;
    y_ = other.y_;
    z_ = other.z_;
    return *this;
}

std::ostream& operator<<(std::ostream& os, Vector3Nx const& vector3Nx)
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
