#include "stdafx.h"
#include "MoJoint.h"
#include "MoBodyFrame.h"

int MoJoint::m_lastId = 0;

MoJoint::MoJoint(void) :
	MoBase(++m_lastId),
	m_type(eRevolute)
{
}

MoJoint::~MoJoint(void)
{
}

bool MoJoint::write(FILE* moFile) const
{
	TCHAR* typeNames[2] = { L"Revolute", L"Prismatic" };

	if (m_type > ePrismatic)
		return false;

	_ftprintf_s(moFile, L"  Modelica.Mechanics.MultiBody.Joints.%s %s annotation(Placement(visible = true, transformation(origin = {-30, 70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n",
		typeNames[m_type],
		name().c_str());
	return true;
}

bool MoJoint::connections(FILE* moFile) const
{
	if (auto f1 = m_frame1.lock())
	{
		if (auto f2 = m_frame2.lock())
		{
			_ftprintf_s(moFile, L"  connect(%s.frame_a, %s) annotation(Line(points = {{-40, 70}, {-60, 70}}, color = {95, 95, 95}));\n",
				name().c_str(), f1->frame().c_str());
			_ftprintf_s(moFile, L"  connect(%s.frame_b, %s) annotation(Line(points = {{-40, 70}, {-60, 70}}, color = {95, 95, 95}));\n",
				name().c_str(), f2->frame().c_str());
			return true;
		}
	}
	return false;
}
