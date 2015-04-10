#pragma once

#include "MoBase.h"
#include "Vector3d.h"
#include "MassProp.h"

// MoBody is a Modelica Body

class MoBody : public MoBase
{
public:
	MoBody(void);
	virtual ~MoBody(void);

	virtual bool write(FILE* moFile) const;

	double mass() const { return m_mass; }
	void addMass(double mass, const Vector3d& cg, const InertiaTensor& inertia);

	void grounded(bool g) { m_grounded = g; }
	bool grounded() const { return m_grounded; }

	void thumbnail(const std::string& thumbnail) { m_thumbnail = thumbnail; }

	virtual LPCTSTR baseName() const { return L"rigidBody"; }

	// name of model that is instanced
	std::wstring definitionName() const;

private:

	double			m_mass;
	InertiaTensor	m_inertia;
	Vector3d		m_cg;
	bool			m_grounded;

	std::string		m_thumbnail;
};
