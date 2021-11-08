#pragma once
struct Vector3
{
	Vector3();
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
	Vector3 CrossProduct(const Vector3& v);
	Vector3 Absolute();
	Vector3 Sqrt();
	Vector3 Lerp(Vector3 end, float t);

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

struct Vector2
{
	Vector2();
	Vector2(float _x, float _y);
	Vector2(const Vector2& other);
	Vector2& operator+=(const Vector2& v);
	Vector2 operator+(const Vector2& v) const;
	Vector2& operator-=(const Vector2& v);
	Vector2 operator-(const Vector2& v) const;
	Vector2& operator*=(const Vector2& v);
	Vector2 operator*(const Vector2& v) const;
	Vector2& operator/=(const Vector2& v);
	Vector2 operator/(const Vector2& v) const;

	Vector2& operator*=(const float scalar);
	Vector2 operator*(const float scalar) const;
	Vector2& operator/=(const float scalar);
	Vector2 operator/(const float scalar) const;

	Vector2 operator-() const;

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;
	bool operator<(const Vector2& v) const;
	bool operator<=(const Vector2& v) const;
	bool operator>(const Vector2& v) const;
	bool operator>=(const Vector2& v) const;

	float SqrMagnitude();
	float Magnitude();
	Vector2 Normalized();
	float DotProduct(const Vector2& v);
	Vector2 Lerp(Vector2 end, float t);
	Vector2 Rotate(float angle);
	Vector2 RotatedClockwise();

	float x, y;
};

namespace Vector2s
{
	const Vector2 zero{ 0.0F, 0.0F };
	const Vector2 one{ 1.0F, 1.0F };
	const Vector2 up{ 0.0F, 1.0F };
	const Vector2 down{ 0.0F, -1.0F };
	const Vector2 left{ -1.0F, 0.0F };
	const Vector2 right{ 1.0F, 0.0F };
	const Vector2 forward{ 0.0F, 0.0F };
	const Vector2 backward{ 0.0F, 0.0F };
}
