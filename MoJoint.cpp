#include "stdafx.h"
#include "MoJoint.h"
#include "MoDiagram.h"

int MoJoint::m_lastId = 0;

namespace {
	TCHAR* jointDef[] =
	{
	L"model RevoluteAssemble\n"
	L"  parameter SI.Position r1[3] = {0, 0, 0};\n"
	L"  parameter SI.Position r2[3] = {0, 0, 0};\n"
	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation1(r = r1) annotation(Placement(visible = true, transformation(origin = {-50, 0}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation2(r = r2) annotation(Placement(visible = true, transformation(origin = {50, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_a frame_a annotation(Placement(visible = true, transformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_b frame_b annotation(Placement(visible = true, transformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Revolute revolute1 annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation(Placement(visible = true, transformation(origin = {0, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {0, 70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_b annotation(Placement(visible = true, transformation(origin = {-50, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-50, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
	L"  connect(flange_a, revolute1.axis) annotation(Line(points = {{0, 100}, {0, 10}}));\n"
	L"  connect(flange_b, revolute1.support) annotation(Line(points = {{-50, 100}, {-50, 40}, {-6, 40}, {-6, 10}}));\n"
	L"  connect(fixedrotation1.frame_b, frame_a) annotation(Line(points = {{-60, 0}, {-100, 0}, {-100, 0}, {-100, 0}}, color = {95, 95, 95}));\n"
	L"  connect(revolute1.frame_b, fixedrotation1.frame_a) annotation(Line(points = {{10, 0}, {40, 0}, {40, 0}, {40, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_a, revolute1.frame_a) annotation(Line(points = {{-40, 0}, {-10, 0}, {-10, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_b, frame_b) annotation(Line(points = {{60, 0}, {100, 0}, {100, 0}, {100, 0}}, color = {95, 95, 95}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {-79, 3}, fillColor = {200, 200, 200}, fillPattern = FillPattern.Solid, extent = {{-21, 7}, {21, -13}}), Rectangle(origin = {77, 3}, fillColor = {200, 200, 200}, fillPattern = FillPattern.Solid, extent = {{-21, 7}, {21, -13}}), Ellipse(fillColor = {200, 200, 200}, fillPattern = FillPattern.Solid, extent = {{-60, 60}, {60, -60}}, endAngle = 360), Ellipse(origin = {-10, 10}, fillColor = {255, 255, 255}, fillPattern = FillPattern.Solid, extent = {{-20, 20}, {40, -40}}, endAngle = 360), Text(origin = {-46, -74}, lineColor = {0, 0, 255}, extent = {{-114, 14}, {206, -26}}, textString = \"%name\")}));\n"
	L"end RevoluteAssemble;\n"
	,
	L"model PrismaticAssemble\n"
	L"  parameter SI.Position r1[3] = {0, 0, 0};\n"
	L"  parameter SI.Position r2[3] = {0, 0, 0};\n"
	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation1(r = r1) annotation(Placement(visible = true, transformation(origin = {-50, 0}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation2(r = r2) annotation(Placement(visible = true, transformation(origin = {50, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Prismatic prismatic1 annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.Translational.Interfaces.Flange_b flange_b annotation(Placement(visible = true, transformation(origin = {-50, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-30, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_a frame_a annotation(Placement(visible = true, transformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_b frame_b annotation(Placement(visible = true, transformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.Translational.Interfaces.Flange_a flange_a annotation(Placement(visible = true, transformation(origin = {8, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {30, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
	L"  connect(flange_b, prismatic1.support) annotation(Line(points = {{-50, 100}, {-4, 100}, {-4, 6}, {-4, 6}}, color = {0, 127, 0}));\n"
	L"  connect(flange_a, prismatic1.axis) annotation(Line(points = {{8, 100}, {8, 6}}, color = {0, 127, 0}));\n"
	L"  connect(fixedrotation1.frame_b, frame_a) annotation(Line(points = {{-60, 0}, {-100, 0}, {-100, 0}, {-100, 0}}, color = {95, 95, 95}));\n"
	L"  connect(prismatic1.frame_b, fixedrotation1.frame_a) annotation(Line(points = {{10, 0}, {40, 0}, {40, 0}, {40, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_a, revolute1.frame_a) annotation(Line(points = {{-40, 0}, {-10, 0}, {-10, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_b, frame_b) annotation(Line(points = {{60, 0}, {100, 0}, {100, 0}, {100, 0}}, color = {95, 95, 95}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {-63, 5}, fillColor = {200, 200, 200}, fillPattern = FillPattern.Solid, extent = {{-37, 25}, {83, -35}}), Text(origin = {-46, -74}, lineColor = {0, 0, 255}, extent = {{-114, 14}, {206, -26}}, textString = \"%name\"), Rectangle(origin = {16, 0}, fillColor = {240, 240, 240}, fillPattern = FillPattern.Solid, extent = {{4, 10}, {84, -10}})}));\n"
	L"end PrismaticAssemble;\n"
	};
}

bool MoJoint::writeDefinition(FILE* moFile, MoJoint::Type type)
{
	switch (type)
	{
	case eRevolute:
		_ftprintf_s(moFile, jointDef[0]);
		break;

	case ePrismatic:
		_ftprintf_s(moFile, jointDef[1]);
		break;

	default:
		return false;
	}

	return true;
}

MoJoint::MoJoint(void) :
	MoBase(++m_lastId),
	m_type(eRevolute)
{
}

MoJoint::~MoJoint(void)
{
}

void MoJoint::init(MoBodyWPtr b1, const AcGeMatrix3d& bodyFrame1, MoBodyWPtr b2, const AcGeMatrix3d& bodyFrame2)
{
	m_body1 = b1;
	m_bodyFrame1 = bodyFrame1;

	m_body2 = b2;
	m_bodyFrame2 = bodyFrame2;
}

bool MoJoint::write(FILE* moFile) const
{
	TCHAR* typeNames[2] = { L"Revolute", L"Prismatic" };

	if (m_type > ePrismatic)
		return false;

	std::wstring nameStr = name();

	_ftprintf_s(moFile, L"  %s %s annotation(%s);\n\n",
		typeNames[m_type], name().c_str(),
		placement().c_str());

	return true;
}

bool MoJoint::connections(FILE* moFile) const
{
	MoBodyPtr b1, b2;
	TCHAR* frame1;
	TCHAR* frame2;
	if (flipHorizontal())
	{
		b1 = body(1);
		b2 = body(0);
		frame1 = L"frame_b";
		frame2 = L"frame_a";
	}
	else
	{
		b1 = body(0);
		b2 = body(1);
		frame1 = L"frame_a";
		frame2 = L"frame_b";
	}

	if (!b1 || !b2)
		return false;

	_ftprintf_s(moFile, L"  connect(%s.frame, %s.%s) annotation(%s));\n",
		b2->name().c_str(), name().c_str(), frame1, connection(b2->diagramX()+2, b2->diagramY()-10, diagramX()-12, diagramY()));

	_ftprintf_s(moFile, L"  connect(%s.%s, %s.frame) annotation(%s));\n",
		name().c_str(), frame2, b1->name().c_str(), connection(diagramX()+12, diagramY(), b1->diagramX(), b1->diagramY()-10));

	return true;
}

MoBodyPtr MoJoint::body(size_t index) const
{
	ASSERT(index < 2);
	if (index == 0)
		return m_body1.lock();
	else
		return m_body2.lock();
}

const AcGeMatrix3d& MoJoint::frame(size_t index) const
{
	ASSERT(index < 2);
	if (index == 0)
		return m_bodyFrame1;
	else
		return m_bodyFrame2;
}