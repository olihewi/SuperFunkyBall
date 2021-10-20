#pragma once
struct Vector3
{
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& other);
	Vector3& operator+=(const Vector3& v);
	Vector3 operator+(const Vector3& v) const;
	Vector3& operator-=(const Vector3& v);
	Vector3 operator-(const Vector3& v) const;
	Vector3& operator*=(const Vector3& v);
	Vector3 operator*(const Vector3& v) const;
	Vector3& operator/=(const Vector3& v);
	Vector3 operator/(const Vector3& v) const;

	Vector3& operator*=(const float scalar);
	Vector3 operator*(const float scalar) const;
	Vector3& operator/=(const float scalar);
	Vector3 operator/(const float scalar) const;

	Vector3 operator-() const;

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;
	bool operator<(const Vector3& v) const;
	bool operator<=(const Vector3& v) const;
	bool operator>(const Vector3& v) const;
	bool operator>=(const Vector3& v) const;

	float SqrMagnitude();
	float Magnitude();
	Vector3 Normalized();
	float DotProduct(const Vector3& v);

	float x, y, z;
};

namespace Vector3s
{
	const Vector3 zero { 0.0F, 0.0F, 0.0F };
	const Vector3 one { 1.0F, 1.0F, 1.0F };
	const Vector3 up { 0.0F, 1.0F, 0.0F };
	const Vector3 down { 0.0F, -1.0F, 0.0F };
	const Vector3 left { -1.0F, 0.0F, 0.0F };
	const Vector3 right { 1.0F, 0.0F, 0.0F };
	const Vector3 forward { 0.0F, 0.0F, 1.0F };
	const Vector3 backward { 0.0F, 0.0F, -1.0F };
}

