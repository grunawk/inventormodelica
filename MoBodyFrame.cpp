#include "stdafx.h"
#include "MoBodyFrame.h"
#include "MoBody.h"


MoBodyFrame::MoBodyFrame(MoBodyPtr body, const AcGeMatrix3d& transform) :
	m_body(body),
	m_transform(transform)
{
}

MoBodyFrame::~MoBodyFrame(void)
{
}

UTxString MoBodyFrame::frame() const
{
	if (auto body = m_body.lock())
	{
		TCHAR cstr[MAX_PATH];
		_stprintf_s<MAX_PATH>(cstr, L"%s_1.%s%d", body->name().c_str(), MoBody::bodyFrameBaseName(), id());
		return cstr;
	}
	ASSERT(0);
	return UTxString();
}

bool MoBodyFrame::write(FILE* moFile) const
{
    _ftprintf_s(moFile, L"    Modelica.Mechanics.MultiBody.Interfaces.Frame_b %s%d annotation(Placement(visible = true, transformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-102, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
						L"    Modelica.Mechanics.MultiBody.Parts.FixedRotation %s annotation(Placement(visible = true, transformation(origin = {-50, 0}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));\n",
						MoBody::bodyFrameBaseName(), id(), name().c_str());

	return true;
}

bool MoBodyFrame::connections(FILE* moFile) const
{
	if (auto body = m_body.lock())
	{
		_ftprintf_s(moFile, L"    connect(body1.frame_a, %s.frame_a) annotation(Line(points = {{0, 0}, {-40, 0}}, color = {95, 95, 95}));\n"
							L"    connect(%s%d, %s.frame_b) annotation(Line(points = {{-100, 0}, {-60, 0}}));\n",
							name().c_str(), MoBody::bodyFrameBaseName(), id(), name().c_str());
		return true;
	}
	return false;
}


