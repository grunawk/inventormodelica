#pragma once
#include "Vector3d.h"

class InertiaTensor
{
public:
	// Default constuctor
	InertiaTensor();
	InertiaTensor(const Vector3d& moments, const Vector3d& products);
	InertiaTensor(const InertiaTensor & source);

	InertiaTensor & operator=(const InertiaTensor &source);

	InertiaTensor operator+(const InertiaTensor &right) const;
	InertiaTensor &operator+=(const InertiaTensor &right);

	// Scalar multiplication/assignment
	InertiaTensor &operator *=(double scalar);

	const Vector3d& moments() const { return m_moments; }
	const Vector3d& products() const { return m_products; }

private:
	Vector3d m_moments;
	Vector3d m_products;
};


