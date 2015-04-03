#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Vector3d
{
public:
	static const Vector3d kXAxis;
	static const Vector3d kYAxis;
	static const Vector3d kZAxis;
	static const Vector3d kZero;

	Vector3d() : m_x(0.0), m_y(0.0), m_z(0.0) {}
	Vector3d(const Vector3d& other) { m_x=other.m_x; m_y=other.m_y; m_z=other.m_z; }
	Vector3d(double x, double y, double z) { m_x = x; m_y=y; m_z=z; }
	virtual ~Vector3d(void) {}

	double x() const { return m_x; }
	double y() const { return m_y; }
	double z() const { return m_z; }

    double operator[] (unsigned int n) const;

	void set(double x, double y, double z) { m_x = x; m_y = y; m_z=z; }

	Vector3d operator+(const Vector3d& p) const;
	const Vector3d& Vector3d::operator+=(const Vector3d& v);

	Vector3d operator-(const Vector3d& p) const;
	const Vector3d& Vector3d::operator-=(const Vector3d& v);

	Vector3d operator*(double s) const;
	Vector3d& Vector3d::operator*=(double s);

	double dot (const Vector3d& v) const;
	Vector3d operator*(const Vector3d& v) const;

	double angle(const Vector3d& v, const Vector3d& about) const;

	double length() const;
	const Vector3d& normalize();
	bool isEqualTo(const Vector3d& v, double tol=1e-6) const;
	Vector3d perpendicular() const;

private:
	double m_x, m_y, m_z;
};

inline double Vector3d::operator[] (unsigned int n) const
{
	switch(n)
	{
	case 0: return m_x;
	case 1: return m_y;
	case 2: return m_z;
	}

	return 0.0;
}

inline Vector3d Vector3d::operator+(const Vector3d& p) const
{
	return Vector3d(m_x + p.m_x, m_y + p.m_y, m_z + p.m_z);
}

inline const Vector3d& Vector3d::operator+=(const Vector3d& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    return *this;
}

inline Vector3d Vector3d::operator-(const Vector3d& p) const
{
	return Vector3d(m_x - p.m_x, m_y - p.m_y, m_z - p.m_z);
}

inline const Vector3d& Vector3d::operator-=(const Vector3d& v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    return *this;
}

inline Vector3d Vector3d::operator*(double s) const
{
    return Vector3d (m_x * s, m_y * s, m_z * s);
}

inline Vector3d& Vector3d::operator*=(double s)
{
    m_x *= s;
	m_y *= s;
	m_z *= s;

	return *this;
}
inline Vector3d Vector3d::operator*(const Vector3d& v) const
{
    return Vector3d(
        m_y * v.m_z - m_z * v.m_y,
        m_z * v.m_x - m_x * v.m_z,
        m_x * v.m_y - m_y * v.m_x);
}

inline double Vector3d::dot(const Vector3d& v) const
{
    return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z;
}

inline double Vector3d::length() const
{
	return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

inline bool Vector3d::isEqualTo(const Vector3d& v, double tol) const
{
    double xDiff = m_x - v.m_x;
	double yDiff = m_y - v.m_y;
	double zDiff = m_z - v.m_z;
    return ( xDiff*xDiff + yDiff*yDiff + zDiff*zDiff <= tol*tol );
}

inline double Vector3d::angle(const Vector3d& v, const Vector3d& about) const
{
    double angle = dot(v) / (length() * v.length());

    if (angle > 1.0) // Account for any noise
        return 0.0;
    else if (angle < -1.0)
        return M_PI;

	angle = acos(angle);

    if (about.dot(*this * v) < 0.0)
        angle = M_PI*2 - angle;

    return angle;
}

inline Vector3d Vector3d::perpendicular() const
{
    if (fabs(m_x) < 0.015625 && fabs(m_y) < 0.015625) // 1/64
		return Vector3d(m_z, 0.0, -m_x);
	else
		return Vector3d(-m_y, m_x, 0.0);
}

inline const Vector3d& Vector3d::normalize()
{
    double lengthInverse = length();
	if (lengthInverse != 0.0)
		lengthInverse = 1.0 / lengthInverse;

    m_x *= lengthInverse;
    m_y *= lengthInverse;
    m_z *= lengthInverse;

    return *this;
}