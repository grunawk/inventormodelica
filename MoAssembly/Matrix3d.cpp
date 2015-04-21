#include "types.h"
#include "Matrix3d.h"

Matrix3d::Matrix3d()
{
	// visual studio 2012 can't use array initializers yet
	m_t[0][0] = 1.0; m_t[0][1] = 0.0; m_t[0][2] = 0.0; m_t[0][3] = 0.0;
    m_t[1][0] = 0.0; m_t[1][1] = 1.0; m_t[1][2] = 0.0; m_t[1][3] = 0.0;
    m_t[2][0] = 0.0; m_t[2][1] = 0.0; m_t[2][2] = 1.0; m_t[2][3] = 0.0;
    m_t[3][0] = 0.0; m_t[3][1] = 0.0; m_t[3][2] = 0.0; m_t[3][3] = 1.0;

}

Matrix3d::Matrix3d(const Matrix3d& m)
{
	*this = m;
}


