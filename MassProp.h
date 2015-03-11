#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef INCLUDE_MI_MASS_PROP_H
#define INCLUDE_MI_MASS_PROP_H

#include <gepnt3d.h>

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// MIxInertiaTensor ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class MIxInertiaTensor
{
public:
	// Default constuctor
	MIxInertiaTensor();

	// Explicit constructor
	MIxInertiaTensor(const double moments[3],const double products[3]);

	// Copy constructor
	MIxInertiaTensor(const MIxInertiaTensor & source);

	// Create an inertia tensor for a point
	MIxInertiaTensor(const AcGePoint3d &point);

	// Assignment operator
	MIxInertiaTensor & operator=(const MIxInertiaTensor &source);

	// Addition operator
	MIxInertiaTensor operator+(const MIxInertiaTensor &right) const;

	// Addition assignment operator
	MIxInertiaTensor &operator+=(const MIxInertiaTensor &right);

	// Subtraction operator
	MIxInertiaTensor operator-(const MIxInertiaTensor &right) const;

	// Subtraction assignment operator
	MIxInertiaTensor &operator-=(const MIxInertiaTensor &right);

	// Provides matrix-like subscripting (indices start at 0)
	double & operator()(unsigned row,unsigned col);

	// Similarity transform by matrix
	MIxInertiaTensor operator*(const AcGeMatrix3d &matrix) const;

	// Left side scalar multiplication
	friend MIxInertiaTensor operator *(double scalar,const MIxInertiaTensor &tensor);

	// Right side scalar multiplication
	MIxInertiaTensor operator *(double scalar) {return scalar*(*this);}

	// Scalar multiplication/assignment
	MIxInertiaTensor &operator *=(double scalar);

	// Similarity transform by matrix w/ ability to reduce calcuations
	MIxInertiaTensor SimilarityTransformBy(const AcGeMatrix3d & matrix,
		int annihilateRow = -1,int annihilateCol = -1) const;

	// Translate an inertia tensor
	MIxInertiaTensor &TranslateBy(const AcGeVector3d &vector,
		const AcGePoint3d &centroid,double mass);

	// Translate an inertia tensor to the center of mass
	MIxInertiaTensor &TranslateBy(const AcGePoint3d &centroid,double mass);

	// Transform an inertia tensor
	MIxInertiaTensor &TransformBy(const AcGeMatrix3d &matrix,
		const AcGePoint3d &centroid,double mass);

	// Tensor diagonalization
	AcGeMatrix3d Diagonalize();

	// Compute principle moments and axes from inertia tensor
	void CalcPrinciples(double *moments,AcGeVector3d *axes) const;

	// Calculate radii of gyration from principle moments
	static void CalcRadiiOfGyration(double moments[3],double mass,
		double *pRadiiOfGyration);

	// Compute the rotation angles of the principle axes
	static void CalcPrincipleRotations(AcGeVector3d axes[3],double rotations[3]);

	// Properties
	//
	double m_momentsOfInertia[3];
	double m_productsOfInertia[3];
};


#endif // INCLUDE_MI_MASS_PROP_H

