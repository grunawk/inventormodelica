#include "StdAfx.h"
#include "MassProp.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

InertiaTensor::InertiaTensor() :
	m_moments(1.0, 1.0, 1.0),
	m_products(Vector3d::kZero)
{
}

InertiaTensor::InertiaTensor(const Vector3d& moments, const Vector3d& products) :
	m_moments(moments),
	m_products(products)
{
}

InertiaTensor::InertiaTensor(const InertiaTensor& source)
{
	*this = source;
}

InertiaTensor InertiaTensor::operator+(const InertiaTensor &right) const
{
	return InertiaTensor(m_moments+right.m_moments, m_products+right.m_products);
}

InertiaTensor &InertiaTensor::operator+=(const InertiaTensor &right)
{
	m_moments += right.m_moments;
	m_products += right.m_products;
	return *this;
}

InertiaTensor &InertiaTensor::operator=(const InertiaTensor &other)
{
	m_moments = other.m_moments;
	m_products = other.m_products;
	return *this;
}

InertiaTensor &InertiaTensor::operator*=(double s)
{
	m_moments *= s;
	m_products *= s;
	return (*this);
}