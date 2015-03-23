#pragma once

#include "MoBase.h"
#include "MoBody.h"
#include <array>

class MoJoint : public MoBase
{
public:
	MoJoint(void);
	virtual ~MoJoint(void);

	const AcGeMatrix3d& frame(size_t i) const;
	MoBodyPtr body(size_t i) const;

	enum Type { eRevolute, ePrismatic };

	Type type() const { return m_type; }
	void type(Type t) { m_type = t; }

	virtual bool write(FILE* moFile, MoDiagram& moDiagram) const;
	bool connections(FILE* moFile, MoDiagram& moDiagram) const;
	static bool writeDefinition(FILE* moFile, Type type);

	virtual LPCTSTR baseName() const
	{
		switch(m_type)
		{
		case eRevolute:		return L"revolute";
		case ePrismatic:	return L"slider";
		default:			return L"joint";
		}
	}

private:
	static int m_lastId;

private:
	Type m_type;
	AcGeMatrix3d m_bodyFrame1, m_bodyFrame2;
	MoBodyWPtr m_body1, m_body2;
};




