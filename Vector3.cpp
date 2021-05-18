#include "Vector3.h"
#include <algorithm>
#include <iostream>

Vector3::Vector3() : x_(0), y_(0), z_(0) {}

Vector3::Vector3(float x, float y, float z) : x_(x), y_(y), z_(z) {}

Vector3 const Vector3::zero{};

Vector3 const Vector3::one(1, 1, 1);

Vector3 Vector3::operator+(Vector3 const& other) const
{
    return Vector3(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector3 Vector3::operator-(Vector3 const& other) const
{
    return Vector3(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Vector3 Vector3::Scale(Vector3 const& left, Vector3 const& right)
{
    return Vector3(left.x_ * right.x_, left.y_ * right.y_, left.z_ * right.z_);
}

Vector3 Vector3::operator*(float const d) const
{
    return Vector3(x_ * d, y_ * d, z_ * d);
}

Vector3 Vector3::Lerp(Vector3 const& a, Vector3 const& b, float t)
{
    auto clampT = std::clamp(t, 0.0f, 1.0f);
    return Vector3(a.x_ + ((b.x_ - a.x_) * clampT),
                     a.y_ + ((b.y_ - a.y_) * clampT),
                     a.z_ + ((b.z_ - a.z_) * clampT));
}

Vector3& Vector3::operator=(Vector3 const& other)
{
    x_ = other.x_;
    y_ = other.y_;
    z_ = other.z_;
    return *this;
}

//Vector3& Vector3::operator=(Vector3&& other) noexcept
//{
//    std::cout << "move" << std::endl;
//    x_ = other.x_;
//    y_ = other.y_;
//    z_ = other.z_;
//    return *this;
//}

std::ostream& operator<<(std::ostream& os, Vector3 const& vector3Nx)
{
    os << "<" << vector3Nx.x_ << ", " << vector3Nx.y_ << ", " << vector3Nx.z_ << ">";
    return os;
}

float Vector3::X() const
{
    return x_;
}

float Vector3::Y() const
{
    return y_;
}

float Vector3::Z() const
{
    return z_;
}

bool Vector3::operator==(const Vector3& other) const
{
    return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
}
