//CODE_COVERAGE_FEATURE(ASSEMBLY,PART)

#include "StdAfx.h"
#include "MassProp.h"
#include <gemat3d.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

////////////////////////////////////////////////////////////////////////////////
//  Local macros and definitions
////////////////////////////////////////////////////////////////////////////////

// SIGNUM returns the sign of its parameter
#define SIGNUM(x) (x < 0. ? -1. : 1.)

// Maximum diagonalization iterations
#define DIAG_MAX_ITERATIONS 200

// Power of 10 constant generation
#define POWER_10(x) (10e##x)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  I have to replae the macro call with a number(15) on Mac, otherwise, I will get an error of "Exponent has no digits"
//  By checking the preprocessed file, I notice the POWER_10(DBL_DIG) was processed as 10eDBL_DIG, which means that
//  the ## in POWER_10 doesn't handle the case of macro DBL_DIG, instead, it treats DBL_DIG as a simple token, which looks to me
//  makes sens
//  BTW, on Windows, DBL_DIG is defined as 15
#define POWER_10_DBL_DIG    (POWER_10(15))

//#define DBL_DIG_BY_2 DBL_DIG/2
#define POWER_10_DBL_DIG_BY_2   (POWER_10(7))
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// MIxInertiaTensor ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Construction
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   MIxInertiaTensor
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Default constructor
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor::MIxInertiaTensor()
{
	m_momentsOfInertia[0] = m_momentsOfInertia[1] =
		m_momentsOfInertia[2] = 1.0;
	m_productsOfInertia[0] = m_productsOfInertia[1] =
		m_productsOfInertia[2] = 0.0;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   MIxInertiaTensor
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Explicit constructor
//
//  PARAMETERS:
//      moments - Moments of inertia
//      products - products of inertia
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor::MIxInertiaTensor(const double moments[3],const double products[3])
{
	memcpy_s(m_momentsOfInertia,sizeof(m_momentsOfInertia),moments,3*sizeof(double));
	memcpy_s(m_productsOfInertia,sizeof(m_productsOfInertia),products,3*sizeof(double));
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   MIxInertiaTensor
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Copy constructor
//
//  PARAMETERS:
//      source - Source tensor
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor::MIxInertiaTensor(const MIxInertiaTensor & source)
{
	*this = source;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   MIxInertiaTensor
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Constructor for point-masses
//
//  PARAMETERS:
//      point - Position of particle
//
//  COMMENTS:
//      The mass of the particle is not factored in.
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor::MIxInertiaTensor(const AcGePoint3d & point)
{
	m_momentsOfInertia[0] = point.y*point.y + point.z*point.z;
	m_momentsOfInertia[1] = point.x*point.x + point.z*point.z;
	m_momentsOfInertia[2] = point.x*point.x + point.y*point.y;

	m_productsOfInertia[0] = -point.y*point.z;
	m_productsOfInertia[1] = -point.x*point.z;
	m_productsOfInertia[2] = -point.x*point.y;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator()
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Provides matrix-like subscripting
//
//  PARAMETERS:
//      row - Tensor row
//      col - Tensor column
//
//  RETURNS:
//      operator() returns a reference to the specified tensor element
//
//  COMMENTS:
//      Indices start at 0
////////////////////////////////////////////////////////////////////////////////

double & MIxInertiaTensor::operator()(unsigned row, unsigned col)
{
	// Are we interested in products or moments?
	if (row == col)
		// Moments are along the diagonal
		return m_momentsOfInertia[row];
	else
	{
		// Products of inertia are off the diagonal
		static const int productSubscriptTable[3][3] =
		{
			{0,2,1},
			{2,0,0},
			{1,0,0}
		};

		return m_productsOfInertia[ productSubscriptTable[row][col] ];
	}
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator *
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Multiplication operator - similarity transform by matrix
//
//  PARAMETERS:
//      matrix - A 3d matrix with an embedded 3x3 orthogonal
//          transformation matrix.
//
//  RETURNS:
//      operator * returns the transformed tensor
//
//  COMMENTS:
//      Only the 3x3 transformation elements of matrix are used, the
//			translational components are ignored.
//      Matrix is assumed to be orthogonal.
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor MIxInertiaTensor::operator *(const AcGeMatrix3d & matrix) const
{
	return SimilarityTransformBy(matrix);
	MIxInertiaTensor output;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator *
//
//  PURPOSE:
//      Scalar multiplication operator
//
//  PARAMETERS:
//      scalar - left operand
//      tensor - right operand
//
//  RETURNS:
//      operator * returns the product
//
//  COMMENTS:
//      This operator is a friend of class MIxInertiaTensor
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor operator *(double scalar,const MIxInertiaTensor &tensor)
{
	MIxInertiaTensor output;

	for (int i = 0; i < 3; i++)
	{
		output.m_momentsOfInertia[i] = scalar*tensor.m_momentsOfInertia[i];
		output.m_productsOfInertia[i] = scalar*tensor.m_productsOfInertia[i];
	}

	return output;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator *=
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Scalar multiplication/assignment
//
//  PARAMETERS:
//      scalar - right operand
//
//  RETURNS:
//      operator *= returns a reference to the product object (*this)
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor &MIxInertiaTensor::operator *=(double scalar)
{
	for (int i = 0; i < 3; i++)
	{
		m_momentsOfInertia[i] *= scalar;
		m_productsOfInertia[i] *= scalar;
	}

	return (*this);
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator +
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Addition operator
//
//  PARAMETERS:
//      right - right operand
//
//  RETURNS:
//      operator + returns the sum of the tensors
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor MIxInertiaTensor::operator+(const MIxInertiaTensor &right) const
{
	MIxInertiaTensor output;

	for (int i = 0; i < 3; i++)
	{
		output.m_momentsOfInertia[i] = m_momentsOfInertia[i] + right.m_momentsOfInertia[i];
		output.m_productsOfInertia[i] = m_productsOfInertia[i] + right.m_productsOfInertia[i];
	}

	return output;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator +=
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Addition/assignment operator
//
//  PARAMETERS:
//      right - right operand
//
//  RETURNS:
//      operator += returns a reference to the left operand (*this)
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor &MIxInertiaTensor::operator+=(const MIxInertiaTensor &right)
{
	for (int i = 0; i < 3; i++)
	{
		m_momentsOfInertia[i] += right.m_momentsOfInertia[i];
		m_productsOfInertia[i] += right.m_productsOfInertia[i];
	}

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator -
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Subtraction operator
//
//  PARAMETERS:
//      right - right operand
//
//  RETURNS:
//      operator - returns the difference of the tensors
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor MIxInertiaTensor::operator-(const MIxInertiaTensor &right) const
{
	MIxInertiaTensor output;

	for (int i = 0; i < 3; i++)
	{
		output.m_momentsOfInertia[i] = m_momentsOfInertia[i] - right.m_momentsOfInertia[i];
		output.m_productsOfInertia[i] = m_productsOfInertia[i] - right.m_productsOfInertia[i];
	}

	return output;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator -=
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Subtraction/assignment operator
//
//  PARAMETERS:
//      right - right operand
//
//  RETURNS:
//      operator -= returns a reference to the left operand (*this)
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor &MIxInertiaTensor::operator-=(const MIxInertiaTensor &right)
{
	for (int i = 0; i < 3; i++)
	{
		m_momentsOfInertia[i] -= right.m_momentsOfInertia[i];
		m_productsOfInertia[i] -= right.m_productsOfInertia[i];
	}

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   operator =
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Assignment operator
//
//  PARAMETERS:
//      source - Source tensor
//
//  RETURNS:
//      operator = returns a reference to the new tensor
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor & MIxInertiaTensor::operator =(const MIxInertiaTensor & source)
{
	memcpy_s(this->m_momentsOfInertia,sizeof(this->m_momentsOfInertia),source.m_momentsOfInertia,3*sizeof(double));
	memcpy_s(this->m_productsOfInertia,sizeof(this->m_productsOfInertia),source.m_productsOfInertia,3*sizeof(double));

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   SimilarityTransformBy
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Similarity transform by matrix: *this = Transpose[M].(*this).M
//
//  PARAMETERS:
//      matrix - A 3d matrix with an embedded 3x3 orthogonal
//          transformation matrix.
//      annihilateRow - row of element known to become 0
//      annihilateCol - col of element known to become 0
//
//  RETURNS:
//      SimilarityTransformBy returns the transformed tensor
//
//  COMMENTS:
//      Only the 3x3 transformation elements of matrix are used, the
//			translational components are ignored.
//      Matrix is assumed to be orthogonal.
//		A pure rotation matrix always leaves one diagonal element unmodifed.
//			We take advantage of this.  e.g. if we're rotationg to annihilate
//          the (0,1) element, (2,2) can just be copied.
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor MIxInertiaTensor::SimilarityTransformBy(const AcGeMatrix3d & matrix,
	int annihilateRow,int annihilateCol) const
{
	MIxInertiaTensor output;
	double p1,p2,p3;	// Partial computations for speed.
	int zeroRow,zeroCol;

	// Be sure column is greater than row for easier comparisons.
	// This swap is ok because the matrix is symmetric.
	//
	if (annihilateCol >= annihilateRow)
	{
		zeroRow = annihilateRow;
		zeroCol = annihilateCol;
	}
	else
	{
		zeroRow = annihilateCol;
		zeroCol = annihilateRow;
	}

	//
	// This is just Transpose(matrix).Tensor.matrix expanded out with Mathematica
	//

	// Moments of inertia
	//
	if (zeroRow == 1 && zeroCol == 2)
		output(0,0) = m_momentsOfInertia[0];
	else
	{
		p1 = m_productsOfInertia[2]*matrix(0,0)*matrix(1,0);
		p2 = m_productsOfInertia[1]*matrix(0,0)*matrix(2,0);
		p3 = m_productsOfInertia[0]*matrix(1,0)*matrix(2,0);
		output(0,0) = m_momentsOfInertia[0]*matrix(0,0)*matrix(0,0) + p1 + p1 +
			m_momentsOfInertia[1]*matrix(1,0)*matrix(1,0) + p2 + p2 + p3 + p3 +
			m_momentsOfInertia[2]*matrix(2,0)*matrix(2,0);
	}

	if (zeroRow == 0 && zeroCol == 2)
		output(1,1) = m_momentsOfInertia[1];
	else
	{
		p1 = m_productsOfInertia[2]*matrix(0,1)*matrix(1,1);
		p2 = m_productsOfInertia[1]*matrix(0,1)*matrix(2,1);
		p3 = m_productsOfInertia[0]*matrix(1,1)*matrix(2,1);
		output(1,1) = m_momentsOfInertia[0]*matrix(0,1)*matrix(0,1) + p1 + p1 +
			m_momentsOfInertia[1]*matrix(1,1)*matrix(1,1) + p2 + p2 + p3 + p3 +
			m_momentsOfInertia[2]*matrix(2,1)*matrix(2,1);
	}

	if (zeroRow == 0 && zeroCol == 1)
		output(2,2) = m_momentsOfInertia[2];
	else
	{
		p1 = m_productsOfInertia[2]*matrix(0,2)*matrix(1,2);
		p2 = m_productsOfInertia[1]*matrix(0,2)*matrix(2,2);
		p3 = m_productsOfInertia[0]*matrix(1,2)*matrix(2,2);
		output(2,2) = m_momentsOfInertia[0]*matrix(0,2)*matrix(0,2) + p1 + p1 +
			m_momentsOfInertia[1]*matrix(1,2)*matrix(1,2) + p2 + p2 + p3 + p3 +
			m_momentsOfInertia[2]*matrix(2,2)*matrix(2,2);
	}

	// Products of inertia
	//
	if (zeroRow == 0 && zeroCol == 1)
		output(0,1) = 0.0;
	else
		output(0,1) = m_momentsOfInertia[0]*matrix(0,0)*matrix(0,1) +
			m_productsOfInertia[2]*matrix(0,1)*matrix(1,0) +
			m_productsOfInertia[2]*matrix(0,0)*matrix(1,1) +
			m_momentsOfInertia[1]*matrix(1,0)*matrix(1,1) +
			m_productsOfInertia[1]*matrix(0,1)*matrix(2,0) +
			m_productsOfInertia[0]*matrix(1,1)*matrix(2,0) +
			m_productsOfInertia[1]*matrix(0,0)*matrix(2,1) +
			m_productsOfInertia[0]*matrix(1,0)*matrix(2,1) +
			m_momentsOfInertia[2]*matrix(2,0)*matrix(2,1);
	if (zeroRow == 0 && zeroCol == 2)
		output(0,2) = 0.0;
	else
		output(0,2) = m_momentsOfInertia[0]*matrix(0,0)*matrix(0,2) +
			m_productsOfInertia[2]*matrix(0,2)*matrix(1,0) +
			m_productsOfInertia[2]*matrix(0,0)*matrix(1,2) +
			m_momentsOfInertia[1]*matrix(1,0)*matrix(1,2) +
			m_productsOfInertia[1]*matrix(0,2)*matrix(2,0) +
			m_productsOfInertia[0]*matrix(1,2)*matrix(2,0) +
			m_productsOfInertia[1]*matrix(0,0)*matrix(2,2) +
			m_productsOfInertia[0]*matrix(1,0)*matrix(2,2) +
			m_momentsOfInertia[2]*matrix(2,0)*matrix(2,2);
	if (zeroRow == 1 && zeroCol == 2)
		output(1,2) = 0.0;
	else
		output(1,2) = m_momentsOfInertia[0]*matrix(0,1)*matrix(0,2) +
			m_productsOfInertia[2]*matrix(0,2)*matrix(1,1) +
			m_productsOfInertia[2]*matrix(0,1)*matrix(1,2) +
			m_momentsOfInertia[1]*matrix(1,1)*matrix(1,2) +
			m_productsOfInertia[1]*matrix(0,2)*matrix(2,1) +
			m_productsOfInertia[0]*matrix(1,2)*matrix(2,1) +
			m_productsOfInertia[1]*matrix(0,1)*matrix(2,2) +
			m_productsOfInertia[0]*matrix(1,1)*matrix(2,2) +
			m_momentsOfInertia[2]*matrix(2,1)*matrix(2,2);

	return output;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   TranslateBy
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Translate an inertia tensor
//
//  PARAMETERS:
//      vector - Translation vector
//      centroid - Center of mass of the body
//      mass - Mass of the body
//
//  RETURNS:
//      TranslateBy returns a reference to this object
//
//  COMMENTS:
//      Use's Steiner's parallel axis theorem
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor &MIxInertiaTensor::TranslateBy(const AcGeVector3d &vector,
	const AcGePoint3d &centroid,double mass)
{
	return (*this) += mass*(MIxInertiaTensor(centroid+vector)-MIxInertiaTensor(centroid));
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   TranslateBy
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Translate an inertia tensor
//
//  PARAMETERS:
//      centroid - Center of mass of the body
//      mass - Mass of the body
//
//  RETURNS:
//      TranslateBy returns a reference to this object
//
//  COMMENTS:
//      Use's Steiner's parallel axis theorem
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor &MIxInertiaTensor::TranslateBy(const AcGePoint3d &centroid,double mass)
{
	return (*this) -= mass*(MIxInertiaTensor(centroid));
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   TransformBy
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Transform an inertia tensor
//
//  PARAMETERS:
//      matrix - Transform matrix, must have only tranlation and rotation
//          components
//      centroid - Center of mass of the body
//      mass - Mass of the body
//
//  RETURNS:
//      TransformBy returns a reference to the transformed body (*this)
//
//  COMMENTS:
//      Handling of uniform scaling and mirroring can be added if needed
////////////////////////////////////////////////////////////////////////////////

MIxInertiaTensor &MIxInertiaTensor::TransformBy(const AcGeMatrix3d &matrix,
	const AcGePoint3d &centroid,double mass)
{
	// Extract the pure rotation matrix for rotating the center of mass
	AcGeMatrix3d pureRotation = matrix;
	pureRotation(0,3) = pureRotation(1,3) = pureRotation(2,3) = 0.;

	// Rotate the center of mass, but do not translate for input to TranslateBy
	AcGePoint3d rotCentroid = pureRotation*centroid;

	return (*this) = SimilarityTransformBy(matrix.transpose()).
		TranslateBy(matrix.translation(),rotCentroid,mass);
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   Diagonalize
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Diagonalizes the tensor
//
//  RETURNS:
//      Diagonalize returns the orthogonal matrix which diagonalizes the tensor.
//
//  COMMENTS:
//      This function uses Jacobi's method as discribed in "Mass Properties in
//			Rubicon."  We follow the method in Press et. al., Numerical Recipes
//			in C.
////////////////////////////////////////////////////////////////////////////////

AcGeMatrix3d MIxInertiaTensor::Diagonalize()
{
	AcGeMatrix3d diagonalizingMatrix;
	AcGeMatrix3d rotateMatrix;

	// Conversion table of product subscripts to matrix subscripts.
	int productSubs[3][2] = {{0,1},{0,2},{1,2}};

	// subscript of the smallest product of inertia
	int minProd;

	// absolute values of the current and minimum product of inertia
	double absCurProd,absMinProd;

	// Numerator and denominator of fraction	
	double numer,denom;

	// Phi is the rotation angle. We never actually compute that, but we use trig functions:
	double tanPhi,sinPhi,cosPhi;

	// theta is half of the arccos(phi)
	double theta;

	// Hopefully we will never iterate this long, but just in case
	for (int i = 0; i < DIAG_MAX_ITERATIONS; i++)
	{
		// Find the largest off-diagonal element and eliminate it.
		// Use the corner first if all are the same
		minProd = 1;
		absMinProd = fabs(m_productsOfInertia[1]);
		absCurProd = fabs(m_productsOfInertia[2]);
		if (absCurProd > absMinProd)
		{
			minProd = 0;
			absMinProd = absCurProd;
		}
		absCurProd = fabs(m_productsOfInertia[0]);
		if (absCurProd > absMinProd)
			minProd = 2;

		int row = productSubs[minProd][0];
		int col = productSubs[minProd][1];

		numer = (*this)(row,row) - (*this)(col,col);
		denom = (*this)(row,col) * 2.0;

		// Test for effectively diagonal already
		double threshold = DBL_EPSILON*( (*this)(row,row) + (*this)(col,col) );
		if ( fabs( numer ) < threshold && fabs( denom ) < threshold )
			break;

		// Test for effective divide by zero
		if (fabs(denom)*POWER_10_DBL_DIG <= fabs(numer))
			break;

		theta = numer/denom;

		if (fabs(theta) > POWER_10_DBL_DIG_BY_2)	// if adding 1 to theta^2 makes no difference
			tanPhi = 1./(theta + theta);
		else
			tanPhi = SIGNUM(theta)/(fabs(theta) + sqrt(theta*theta + 1.));

		cosPhi = 1./sqrt(tanPhi*tanPhi + 1.);
		if ( 1.0 - cosPhi < DBL_EPSILON )
			break;	// sinPhi == 0

		sinPhi = cosPhi*tanPhi;

		// Now build the rotation matrix
		rotateMatrix.setToIdentity();
		rotateMatrix(row,row) = rotateMatrix(col,col) = cosPhi;
		rotateMatrix(row,col) = -(rotateMatrix(col,row) = sinPhi);

		// Accumulate the diagonalizing matrix
		diagonalizingMatrix.postMultBy(rotateMatrix);

		// Apply the rotation
		(*this) = SimilarityTransformBy(rotateMatrix,row,col);
	}

	// Set all products of inertia to zero
	m_productsOfInertia[2] = m_productsOfInertia[1] = m_productsOfInertia[0] = 0.;

	return diagonalizingMatrix;
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   CalcPrinciples
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Compute the principle moments and axes of the inertia tensor
//
//  PARAMETERS:
//      moments - Destination array of moments (at least three elements)
//      axes - Destination array of principle axes (at least three elements)
////////////////////////////////////////////////////////////////////////////////

void MIxInertiaTensor::CalcPrinciples(double * moments, AcGeVector3d * axes) const
{
	MIxInertiaTensor diagonalTensor = *this;
	AcGeMatrix3d transform = diagonalTensor.Diagonalize();

	for (int i = 0; i < 3; i++)
	{
		// The diagonals of the new tensor are the principle moments
		moments[i] = diagonalTensor(i,i);

		// The columns of the diagonalizing transform are the principle axes
		axes[i] = AcGeVector3d(transform(0,i),transform(1,i),transform(2,i));
	}
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   CalcRadiiOfGyration
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Compute the radii of gyration from the principle moments and mass
//
//  PARAMETERS:
//      moments - principle moment calculated from
//          MIxInertiaTensor::CalcPrinciples()
//      mass - mass of the body
//      pRadiiOfGyration - destination for radii of gyration
////////////////////////////////////////////////////////////////////////////////

void MIxInertiaTensor::CalcRadiiOfGyration(double moments[3],double mass,
	double *pRadiiOfGyration)
{
	// A little fault tolerance here
	mass = fabs(mass);

	for (int i = 0; i < 3; i++)
	{
		// Check to see if mass and moments[i] are compatible for division
		if (mass*POWER_10_DBL_DIG >= fabs(moments[i]))
			pRadiiOfGyration[i] = sqrt(fabs(moments[i])/mass);
		else
			pRadiiOfGyration[i] = DBL_MAX;
	}
}

////////////////////////////////////////////////////////////////////////////////
//  METHOD:   CalcPrincipleRotations
//
//  CLASS:    MIxInertiaTensor
//
//  PURPOSE:
//      Compute the rotation angles of the principle axes
//
//  PARAMETERS:
//      axes - Principle axes (computed with MIxInertiaTensor::CalcPrinciples)
//      rotations - Destination for return values
////////////////////////////////////////////////////////////////////////////////

void MIxInertiaTensor::CalcPrincipleRotations(AcGeVector3d axes[3],double rotations[3])
{
	AcGeMatrix3d principle,rotate;
	double acosValue;

	// Specify the axes as a coordinate system to compact computation
	principle.setCoordSystem(AcGePoint3d(0.,0.,0.),axes[0],axes[1],axes[2]);

	//
	// Choose rotations[0] about x which transforms axes[2] onto the x-z plane
	//

	double b = principle(1,2), c = principle(2,2);
	double numer = c;
	double denom = sqrt(b*b + c*c);

	// Make sure we can do the division.  If not, then axes[2] is already in the x-z plane
	if(fabs(denom)*POWER_10_DBL_DIG <= fabs(numer))
		rotations[0] = 0.0;
	else
	{
		double q = numer/denom;
		if (q >= 1.)
			acosValue = 0.;
		else if (q <= -1.)
			acosValue = M_PI;
		else
			acosValue = acos(q);
		rotations[0] = SIGNUM(b)*acosValue;
		rotate.setToRotation(rotations[0],AcGeVector3d(1.,0.,0.));
		principle.preMultBy(rotate);
	}

	//
	// Choose rotations[1] about y which transforms axes[3] onto the z axis
	//

	if (principle(2,2) >= 1.)
		acosValue = 0.;
	else if (principle(2,2) <= -1.)
		acosValue = M_PI;
	else
		acosValue = acos(principle(2,2));
	rotations[1] = SIGNUM(-principle(0,2))*acosValue;
	rotate.setToRotation(rotations[1],AcGeVector3d(0.,1.,0.));
	principle.preMultBy(rotate);

	//
	// Choose rotations[2] about z which transforms axes[0] onto the x axis
	//

	if (principle(0,0) >= 1.)
		acosValue = 0.;
	else if (principle(0,0) <= -1.)
		acosValue = M_PI;
	else
		acosValue = acos(principle(0,0));
	rotations[2] = SIGNUM(-principle(1,0))*acosValue;
}
