#include "stdafx.h"
#include "MoJoint.h"

namespace {
	TCHAR* jointDef[] =
	{
	L"model RevolutePositioned\n"
	L"  parameter Modelica.SIunits.Position r1[3] = {0, 0, 0};\n"
	L"  parameter Modelica.SIunits.Position r2[3] = {0, 0, 0};\n"
	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n1_x = {1, 0, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n1_y = {0, 1, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n2_x = {1, 0, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n2_y = {0, 1, 0};\n"
  	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation1(r = r1, n_x = n1_x, n_y = n1_y, rotationType = Modelica.Mechanics.MultiBody.Types.RotationTypes.TwoAxesVectors) annotation(Placement(visible = true, transformation(origin = {-50, 0}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));\n"
  	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation2(r = r2, n_x = n2_x, n_y = n2_y, rotationType = Modelica.Mechanics.MultiBody.Types.RotationTypes.TwoAxesVectors) annotation(Placement(visible = true, transformation(origin = {50, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_a frame_a annotation(Placement(visible = true, transformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_b frame_b annotation(Placement(visible = true, transformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Revolute revolute1 annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
//	L"  Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation(Placement(visible = true, transformation(origin = {0, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {0, 70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
//	L"  Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_b annotation(Placement(visible = true, transformation(origin = {-50, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-50, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
//	L"  connect(flange_a, revolute1.axis) annotation(Line(points = {{0, 100}, {0, 10}}));\n"
//	L"  connect(flange_b, revolute1.support) annotation(Line(points = {{-50, 100}, {-50, 40}, {-6, 40}, {-6, 10}}));\n"
	L"  connect(fixedrotation1.frame_b, frame_a) annotation(Line(points = {{-60, 0}, {-100, 0}, {-100, 0}, {-100, 0}}, color = {95, 95, 95}));\n"
	L"  connect(revolute1.frame_a, fixedrotation1.frame_a) annotation(Line(points = {{10, 0}, {40, 0}, {40, 0}, {40, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_a, revolute1.frame_b) annotation(Line(points = {{-40, 0}, {-10, 0}, {-10, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_b, frame_b) annotation(Line(points = {{60, 0}, {100, 0}, {100, 0}, {100, 0}}, color = {95, 95, 95}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {-12, 10}, lineColor = {85, 170, 255}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-8, 40}, {12, -60}}), Rectangle(origin = {10, 0}, lineColor = {175, 175, 175}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-10, 50}, {10, -50}}), Rectangle(origin = {-47, 0}, lineColor = {85, 170, 255}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-33, 10}, {27, -10}}), Rectangle(origin = {37, 0}, lineColor = {175, 175, 175}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-17, 10}, {43, -10}}), Text(origin = {20, -90}, lineColor = {0, 0, 255}, extent = {{-140, 30}, {100, -10}}, textString = \"%%name\")}));\n"
	L"end RevolutePositioned;\n\n"
	,
	L"model PrismaticPositioned\n"
	L"  parameter Modelica.SIunits.Position r1[3] = {0, 0, 0};\n"
	L"  parameter Modelica.SIunits.Position r2[3] = {0, 0, 0};\n"
	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n1_x = {1, 0, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n1_y = {0, 1, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n2_x = {1, 0, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n2_y = {0, 1, 0};\n"
	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation1(r = r1, n_x = n1_x, n_y = n1_y) annotation(Placement(visible = true, transformation(origin = {-50, 0}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation2(r = r2, n_x = n2_x, n_y = n2_y) annotation(Placement(visible = true, transformation(origin = {50, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Prismatic prismatic1 annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_a frame_a annotation(Placement(visible = true, transformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_b frame_b annotation(Placement(visible = true, transformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
//	L"  Modelica.Mechanics.Translational.Interfaces.Flange_a flange_a annotation(Placement(visible = true, transformation(origin = {8, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {30, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
//	L"  Modelica.Mechanics.Translational.Interfaces.Flange_b flange_b annotation(Placement(visible = true, transformation(origin = {-50, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-30, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
//	L"  connect(flange_b, prismatic1.support) annotation(Line(points = {{-50, 100}, {-4, 100}, {-4, 6}, {-4, 6}}, color = {0, 127, 0}));\n"
//	L"  connect(flange_a, prismatic1.axis) annotation(Line(points = {{8, 100}, {8, 6}}, color = {0, 127, 0}));\n"
	L"  connect(fixedrotation1.frame_b, frame_a) annotation(Line(points = {{-60, 0}, {-100, 0}, {-100, 0}, {-100, 0}}, color = {95, 95, 95}));\n"
	L"  connect(prismatic1.frame_a, fixedrotation1.frame_a) annotation(Line(points = {{10, 0}, {40, 0}, {40, 0}, {40, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_a, prismatic1.frame_b) annotation(Line(points = {{-40, 0}, {-10, 0}, {-10, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_b, frame_b) annotation(Line(points = {{60, 0}, {100, 0}, {100, 0}, {100, 0}}, color = {95, 95, 95}));\n"
	L"	annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {-47, 10}, lineColor = {85, 170, 255}, fillColor = {85, 170, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-33, 10}, {47, -30}}), Rectangle(origin = {37, 0}, lineColor = {175, 175, 175}, fillColor = {175, 175, 175}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-37, 10}, {43, -10}}), Text(origin = {20, -90}, lineColor = {0, 0, 255}, extent = {{-140, 30}, {100, -10}}, textString = \"%%name\")}));\n"
	L"end PrismaticPositioned;\n\n"
	,
	L"model RigidPositioned\n"
	L"  parameter Modelica.SIunits.Position r1[3] = {0, 0, 0};\n"
	L"  parameter Modelica.SIunits.Position r2[3] = {0, 0, 0};\n"
	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n1_x = {1, 0, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n1_y = {0, 1, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n2_x = {1, 0, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n2_y = {0, 1, 0};\n"
	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation1(r = r1, n_x = n1_x, n_y = n1_y) annotation(Placement(visible = true, transformation(origin = {-50, 0}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation2(r = r2, n_x = n2_x, n_y = n2_y) annotation(Placement(visible = true, transformation(origin = {50, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_a frame_a annotation(Placement(visible = true, transformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"  Modelica.Mechanics.MultiBody.Interfaces.Frame_b frame_b annotation(Placement(visible = true, transformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
	L"  connect(fixedrotation1.frame_b, frame_a) annotation(Line(points = {{-60, 0}, {-100, 0}, {-100, 0}, {-100, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation1.frame_a, fixedrotation2.frame_a) annotation(Line(points = {{10, 0}, {40, 0}, {40, 0}, {40, 0}}, color = {95, 95, 95}));\n"
	L"  connect(fixedrotation2.frame_b, frame_b) annotation(Line(points = {{60, 0}, {100, 0}, {100, 0}, {100, 0}}, color = {95, 95, 95}));\n"
	L"	annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {-51, 10}, lineColor = {85, 170, 255}, fillColor = {85, 170, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{27, 30}, {47, -50}}), Rectangle(origin = {41, 0}, lineColor = {175, 175, 175}, fillColor = {175, 175, 175}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-37, 40}, {-17, -40}}), Text(origin = {20, -90}, lineColor = {0, 0, 255}, extent = {{-140, 30}, {100, -10}}, textString = \"%%name\"), Rectangle(origin = {-105, -20}, lineColor = {85, 170, 255}, fillColor = {85, 170, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{25, 30}, {81, 10}}), Rectangle(origin = {59, -26}, rotation = -90, lineColor = {175, 175, 175}, fillColor = {175, 175, 175}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-37, 22}, {-17, -36}}), Rectangle(origin = {-29, 10}, lineColor = {85, 170, 255}, fillColor = {170, 0, 0}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{25, 30}, {33, -50}})}));\n"
	L"end RigidPositioned;\n\n"
	};
}

bool MoJoint::writeDefinitions(FILE* moFile, const std::vector<MoJointPtr>& joints)
{
	bool defined[eLastJoint+1] = { false, false, false };

	for (auto& joint: joints)
	{
		if (joint->type() > eLastJoint)
		{
			ASSERT(0);
			continue;
		}

		if (!defined[joint->type()])
		{
			defined[joint->type()] = true;
			_ftprintf_s(moFile, jointDef[joint->type()]);
		}
	}

	return true;
}

MoJoint::MoJoint(void) :
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
	TCHAR* typeNames[eLastJoint+1] = { L"RevolutePositioned", L"PrismaticPositioned", L"RigidPositioned" };

	if (m_type > eLastJoint)
	{
		ASSERT(0);
		return false;
	}

	std::wstring nameStr = name();

	_ftprintf_s(moFile, L"  %s %s(r1 = {%f, %f, %f}, n1_x = {%f, %f, %f}, n1_y = {%f, %f, %f}, r2 = {%f, %f, %f}, n2_x = {%f, %f, %f}, n2_y = {%f, %f, %f}) annotation(%s);\n\n",
		typeNames[m_type], name().c_str(),

		m_bodyFrame1(0,3), m_bodyFrame1(1,3), m_bodyFrame1(2,3),
		m_bodyFrame1(0,0), m_bodyFrame1(1,0), m_bodyFrame1(2,0),
		m_bodyFrame1(0,1), m_bodyFrame1(1,1), m_bodyFrame1(2,1),

		m_bodyFrame2(0,3), m_bodyFrame2(1,3), m_bodyFrame2(2,3),
		m_bodyFrame2(0,0), m_bodyFrame2(1,0), m_bodyFrame2(2,0),
		m_bodyFrame2(0,1), m_bodyFrame2(1,1), m_bodyFrame2(2,1),

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

	_ftprintf_s(moFile, L"  connect(%s_1.frame, %s.%s) annotation(%s);\n",
		b1->name().c_str(), name().c_str(), frame1, connection(b1->diagramX(), b1->diagramY()-10, diagramX()-10, diagramY()).c_str());

	_ftprintf_s(moFile, L"  connect(%s.%s, %s_1.frame) annotation(%s);\n",
		name().c_str(), frame2, b2->name().c_str(), connection(diagramX()+10, diagramY(), b2->diagramX(), b2->diagramY()-10).c_str());

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


LPCTSTR MoJoint::baseName() const
{
	static TCHAR* baseNames[eLastJoint+1] = { L"revolute", L"slider", L"rigid" };
	if (type() > eLastJoint)
	{
		ASSERT(0);
		return L"unknown";
	}

	return baseNames[type()];
}
