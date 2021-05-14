#include "Vector3Nx.h"
#include <algorithm>

Vector3Nx::Vector3Nx() : x_(0), y_(0), z_(0) {}

Vector3Nx::Vector3Nx(float x, float y, float z) : x_(x), y_(y), z_(z) {}

const Vector3Nx Vector3Nx::zero{};
const Vector3Nx Vector3Nx::one{1, 1, 1};

Vector3Nx Vector3Nx::operator+(const Vector3Nx& other) const
{
    return Vector3Nx(x + other.x, y + other.y, z + other.z);
}

Vector3Nx Vector3Nx::operator-(const Vector3Nx& other) const
{
    return Vector3Nx(x - other.x, y - other.y, z - other.z);
}

Vector3Nx Vector3Nx::Scale(const Vector3Nx& left, const Vector3Nx& right)
{
    return Vector3Nx(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3Nx Vector3Nx::operator*(const float d) const
{
    return Vector3Nx(x * d, y * d, z * d);
}

Vector3Nx Vector3Nx::Lerp(const Vector3Nx& a, const Vector3Nx& b, float t)
{
    auto clampT = std::clamp(t, 0.0f, 1.0f);
    return Vector3Nx(a.x + ((b.x - a.x) * clampT),
                     a.y + ((b.y - a.y) * clampT),
                     a.z + ((b.z - a.z) * clampT));
}

Vector3Nx& Vector3Nx::operator=(const Vector3Nx& other)
{
    x_ = other.x_;
    y_ = other.y_;
    z_ = other.z_;
    return *this;
}