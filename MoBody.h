#pragma once

#include "MoBase.h"
#include <gemat3d.h>
#include "MassProp.h"

// MoBody is a Modelica Body

class MoBody : public MoBase
{
public:
	MoBody(void);
	virtual ~MoBody(void);

	virtual bool write(FILE* moFile) const;

	void addMass(double mass, const AcGePoint3d& cg, const MIxInertiaTensor& inertia);

	void grounded(bool g) { m_grounded = g; }
	bool grounded() const { return m_grounded; }

	void thumbnail(const std::string& thumbnail) { m_thumbnail = thumbnail; }

	virtual LPCTSTR baseName() const { return L"rigidBody"; }

private:

	double				m_mass;
	MIxInertiaTensor	m_inertia;
	AcGePoint3d			m_cg;
	bool				m_grounded;

	std::string			m_thumbnail;
};
