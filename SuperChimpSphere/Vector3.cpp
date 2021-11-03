#include "Vector3.h"
#include <cmath>

Vector3::Vector3() : x(0.0F), y(0.0F), z(0.0F)
{
}

Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}

Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z)
{
}

Vector3& Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const {
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3& Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& v) const {
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3& Vector3::operator*=(const Vector3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3 Vector3::operator*(const Vector3& v) const {
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3& Vector3::operator/=(const Vector3& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

Vector3 Vector3::operator/(const Vector3& v) const {
	return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3& Vector3::operator*=(const float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3 Vector3::operator*(const float scalar) const {
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3& Vector3::operator/=(const float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vector3 Vector3::operator/(const float scalar) const {
	return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 Vector3::operator-() const {
	return Vector3(-x, -y, -z);
}

bool Vector3::operator==(const Vector3& v) const {
	return x == v.x && y == v.y && z == v.z;
}

bool Vector3::operator!=(const Vector3& v) const {
	return x != v.x || y != v.y || z != v.z;
}

bool Vector3::operator<(const Vector3& v) const {
	if (x == v.x) {
		if (y == v.y) {
			return z < v.z;
		}
		return y < v.y;
	}
	return x < v.x;
}

bool Vector3::operator>(const Vector3& v) const {
	if (x == v.x) {
		if (y == v.y) {
			return z > v.z;
		}
		return y > v.y;
	}
	return x > v.x;
}

bool Vector3::operator<=(const Vector3& v) const {
	if (x == v.x) {
		if (y == v.y) {
			return z <= v.z;
		}
		return y < v.y;
	}
	return x < v.x;
}

bool Vector3::operator>=(const Vector3& v) const {
	if (x == v.x) {
		if (y == v.y) {
			return z >= v.z;
		}
		return y > v.y;
	}
	return x > v.x;
}

float Vector3::SqrMagnitude()
{
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;
	return x2 + y2 + z2;
}

float Vector3::Magnitude()
{
	return std::sqrtf(SqrMagnitude());
}

Vector3 Vector3::Normalized()
{
	float mag2 = SqrMagnitude();
	if (mag2 == 0.0F)
	{
		return Vector3s::zero;
	}
	return *this * std::sqrtf(mag2);
}

float Vector3::DotProduct(const Vector3& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector2::Vector2() : x(0.0F), y(0.0F)
{
}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{
}

Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y)
{
}

Vector2& Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& v) const {
	return Vector2(x + v.x, y + v.y);
}

Vector2& Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& v) const {
	return Vector2(x - v.x, y - v.y);
}

Vector2& Vector2::operator*=(const Vector2& v) {
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2 Vector2::operator*(const Vector2& v) const {
	return Vector2(x * v.x, y * v.y);
}

Vector2& Vector2::operator/=(const Vector2& v) {
	x /= v.x;
	y /= v.y;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& v) const {
	return Vector2(x / v.x, y / v.y);
}

Vector2& Vector2::operator*=(const float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 Vector2::operator*(const float scalar) const {
	return Vector2(x * scalar, y * scalar);
}

Vector2& Vector2::operator/=(const float scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2 Vector2::operator/(const float scalar) const {
	return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator-() const {
	return Vector2(-x, -y);
}

bool Vector2::operator==(const Vector2& v) const {
	return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v) const {
	return x != v.x || y != v.y;
}

bool Vector2::operator<(const Vector2& v) const {
	if (x == v.x) {
		return y < v.y;
	}
	return x < v.x;
}

bool Vector2::operator>(const Vector2& v) const {
	if (x == v.x) {
		return y > v.y;
	}
	return x > v.x;
}

bool Vector2::operator<=(const Vector2& v) const {
	if (x == v.x) {
		return y < v.y;
	}
	return x < v.x;
}

bool Vector2::operator>=(const Vector2& v) const {
	if (x == v.x) {
		return y > v.y;
	}
	return x > v.x;
}

float Vector2::SqrMagnitude()
{
	float x2 = x * x;
	float y2 = y * y;
	return x2 + y2;
}

float Vector2::Magnitude()
{
	return std::sqrtf(SqrMagnitude());
}

Vector2 Vector2::Normalized()
{
	float mag2 = SqrMagnitude();
	if (mag2 == 0.0F)
	{
		return Vector2s::zero;
	}
	return *this * std::sqrtf(mag2);
}

float Vector2::DotProduct(const Vector2& v)
{
	return x * v.x + y * v.y;
}