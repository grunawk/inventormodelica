#pragma once
#include "Vector3d.h"

class Matrix3d
{
public:
	static Matrix3d kIdentity;

	Matrix3d();
	Matrix3d(const Matrix3d& m);
	Matrix3d(const Vector3d& pos, const Vector3d& xAxis, const Vector3d& yAxis, const Vector3d& zAxis);
	virtual ~Matrix3d() {};

	Vector3d operator[](unsigned int i) const;
	double operator() (unsigned int i, unsigned int j) const;

	// scale translation
	const Matrix3d& operator*=(double s);

private:
	double m_t[4][4];
};

inline Matrix3d::Matrix3d(const Vector3d& pos, const Vector3d& xAxis, const Vector3d& yAxis, const Vector3d& zAxis)
{
	m_t[0][3] = pos.x();   m_t[1][3] = pos.y();   m_t[2][3] = pos.z();
	m_t[0][0] = xAxis.x(); m_t[1][0] = xAxis.y(); m_t[2][0] = xAxis.z();
	m_t[0][1] = yAxis.x(); m_t[1][1] = yAxis.y(); m_t[2][1] = yAxis.z();
	m_t[0][2] = zAxis.x(); m_t[1][2] = zAxis.y(); m_t[2][2] = zAxis.z();
}

inline Vector3d Matrix3d::operator[](unsigned int i) const
{
	if (i>3)
		return Vector3d::kZero;

	return Vector3d(m_t[0][i], m_t[1][i], m_t[2][i]);
}

inline double Matrix3d::operator()(unsigned int i, unsigned int j) const
{
	if (i>3 || j>3)
		return 0;

	return m_t[i][j];
}

inline const Matrix3d& Matrix3d::operator*=(double s)
{
	m_t[0][3] *= s;
	m_t[1][3] *= s;
	m_t[2][3] *= s;

	return *this;
}

