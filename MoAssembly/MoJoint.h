#pragma once

#include "MoBase.h"
#include "MoBody.h"
#include "Matrix3d.h"

class MoJoint : public MoBase
{
public:
	MoJoint(void);
	virtual ~MoJoint(void);

	void init(MoBodyWPtr b1, const Matrix3d& bodyFrame1, MoBodyWPtr b2, const Matrix3d& bodyFrame2);

	const Matrix3d& frame(size_t i) const;
	MoBodyPtr body(size_t i) const;

	enum Type { eRevolute=0, ePrismatic, eCylindrical, ePlanar, eSpherical, eRigid, eUnknown };

	Type type() const { return m_type; }
	void type(Type t) { m_type = t; }

	virtual bool write(FILE* moFile) const;
	bool connections(FILE* moFile) const;

	static bool writeDefinitions(FILE* moFile, const std::vector<MoJointPtr>& joints);

	virtual wchar_t* baseName() const;

private:
	Type m_type;
	Matrix3d m_bodyFrame1, m_bodyFrame2;
	MoBodyWPtr m_body1, m_body2;
};




