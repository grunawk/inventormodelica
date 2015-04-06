#include "stdafx.h"
#include "MoJoint.h"
#include "MoUtil.h"

namespace {

	TCHAR* jointBaseDef =
	L"model PartialPositioned\n"
	L"  extends Modelica.Mechanics.MultiBody.Interfaces.PartialTwoFrames;\n"
	L"  parameter Modelica.SIunits.Position r1[3] = {0, 0, 0};\n"
	L"  parameter Modelica.SIunits.Position r2[3] = {0, 0, 0};\n"
	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n1_x = {1, 0, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n1_y = {0, 1, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n2_x = {1, 0, 0};\n"
  	L"  parameter Modelica.Mechanics.MultiBody.Types.Axis n2_y = {0, 1, 0};\n"
  	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation1(r = r1, n_x = n1_x, n_y = n1_y, rotationType = Modelica.Mechanics.MultiBody.Types.RotationTypes.TwoAxesVectors) annotation(Placement(visible = true, transformation(origin = {-50, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
  	L"  Modelica.Mechanics.MultiBody.Parts.FixedRotation fixedrotation2(r = r2, n_x = n2_x, n_y = n2_y, rotationType = Modelica.Mechanics.MultiBody.Types.RotationTypes.TwoAxesVectors) annotation(Placement(visible = true, transformation(origin = {50, 0}, extent = {{10, -10}, {-10, 10}}, rotation = 0)));\n"
	L"equation\n"
    L"	connect(fixedrotation1.frame_a, frame_a) annotation(Line(points = {{-60, 0}, {-100, 0}}, color = {95, 95, 95}));\n"
    L"	connect(fixedrotation2.frame_a, frame_b) annotation(Line(points = {{60, 0}, {100, 0}}, color = {95, 95, 95}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})));\n"
	L"end PartialPositioned;\n\n";

	TCHAR* jointDef[MoJoint::eUnknown] =
	{
	L"model RevolutePositioned\n"
	L"  extends PartialPositioned;\n"
	L"  parameter Boolean useAxisFlange = false \"= true, if axis flange is enabled\" annotation(Evaluate = true, HideResult = true, choices(checkBox = true));\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Revolute joint(useAxisFlange=useAxisFlange) annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"	Modelica.Mechanics.Rotational.Interfaces.Flange_a axis if useAxisFlange annotation(Placement(visible = true, transformation(origin = {0, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-50, 70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"	Modelica.Mechanics.Rotational.Interfaces.Flange_b support if useAxisFlange annotation(Placement(visible = true, transformation(origin = {-52, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {0, 70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
    L"	connect(fixedrotation1.frame_b, joint.frame_a) annotation(Line(points = {{-40, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
    L"	connect(fixedrotation2.frame_b, joint.frame_b) annotation(Line(points = {{40, 0}, {10, 0}}, color = {95, 95, 95}));\n"
	L"  connect(support, joint.support) annotation(Line(points = {{-52, 100}, {-52, 55}, {-6, 55}, {-6, 10}}));\n"
	L"  connect(axis, joint.axis) annotation(Line(points = {{0, 100}, {0, 10}}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {-12, 10}, lineColor = {85, 170, 255}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-8, 40}, {12, -60}}), Rectangle(origin = {10, 0}, lineColor = {175, 175, 175}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-10, 50}, {10, -50}}), Rectangle(origin = {-47, 0}, lineColor = {85, 170, 255}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-33, 10}, {27, -10}}), Rectangle(origin = {37, 0}, lineColor = {175, 175, 175}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-17, 10}, {43, -10}}), Text(origin = {20, -90}, lineColor = {0, 0, 255}, extent = {{-140, 30}, {100, -10}}, textString = \"%%name\")}));\n"
	L"end RevolutePositioned;\n\n"
	,
	L"model PrismaticPositioned\n"
	L"  extends PartialPositioned;\n"
	L"  parameter Boolean useAxisFlange = false \"= true, if axis flange is enabled\" annotation(Evaluate = true, HideResult = true, choices(checkBox = true));\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Prismatic joint(n={0,0,1}, useAxisFlange=useAxisFlange) annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"	Modelica.Mechanics.Translational.Interfaces.Flange_a axis if useAxisFlange annotation(Placement(visible = true, transformation(origin = {0, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-50, 70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"	Modelica.Mechanics.Translational.Interfaces.Flange_b support if useAxisFlange annotation(Placement(visible = true, transformation(origin = {-52, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {0, 70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
    L"	connect(fixedrotation1.frame_b, joint.frame_a) annotation(Line(points = {{-40, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
    L"	connect(fixedrotation2.frame_b, joint.frame_b) annotation(Line(points = {{40, 0}, {10, 0}}, color = {95, 95, 95}));\n"
	L"  connect(support, joint.support) annotation(Line(points = {{-50, 100}, {-50, 51}, {-6, 51}, {-6, 6}}));\n"
	L"  connect(axis, joint.axis) annotation(Line(points = {{6, 102}, {6, 6}}));\n"
	L"	annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {-47, 10}, lineColor = {85, 170, 255}, fillColor = {85, 170, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-33, 10}, {47, -30}}), Rectangle(origin = {37, 0}, lineColor = {175, 175, 175}, fillColor = {175, 175, 175}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-37, 10}, {43, -10}}), Text(origin = {20, -90}, lineColor = {0, 0, 255}, extent = {{-140, 30}, {100, -10}}, textString = \"%%name\")}));\n"
	L"end PrismaticPositioned;\n\n"
	,
	L"model CylindricalPositioned\n"
	L"  extends PartialPositioned;\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Cylindrical joint(n={0,0,1}) annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
    L"	connect(fixedrotation1.frame_b, joint.frame_a) annotation(Line(points = {{-40, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
    L"	connect(fixedrotation2.frame_b, joint.frame_b) annotation(Line(points = {{40, 0}, {10, 0}}, color = {95, 95, 95}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {-47, 10}, lineColor = {85, 170, 255}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-33, 10}, {47, -30}}), Rectangle(origin = {37, 0}, lineColor = {175, 175, 175}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-37, 10}, {43, -10}}), Text(origin = {20, -90}, lineColor = {0, 0, 255}, extent = {{-140, 30}, {100, -10}}, textString = \"%%name\")}));\n"
	L"end CylindricalPositioned;\n\n"
	,
	L"model PlanarPositioned\n"
	L"  extends PartialPositioned;\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Planar joint annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
    L"	connect(fixedrotation1.frame_b, joint.frame_a) annotation(Line(points = {{-40, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
    L"	connect(fixedrotation2.frame_b, joint.frame_b) annotation(Line(points = {{40, 0}, {10, 0}}, color = {95, 95, 95}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(origin = {10, -12}, fillColor = {85, 170, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-30, -60}, {-10, 60}}), Rectangle(origin = {-10, 0}, fillColor = {192, 192, 192}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{10, -60}, {30, 60}}), Rectangle(origin = {10, -12}, lineColor = {85, 170, 255}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-90, -10}, {-30, 10}}), Rectangle(origin = {-20, 0}, lineColor = {200, 200, 200}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{100, -10}, {40, 10}}), Text(lineColor = {0, 0, 255}, extent = {{-150, 110}, {150, 70}}, textString = \"%%name\")}));\n"
	L"end PlanarPositioned;\n\n"
	,
	L"model SphericalPositioned\n"
	L"  extends PartialPositioned;\n"
	L"  Modelica.Mechanics.MultiBody.Joints.Spherical joint annotation(Placement(visible = true, transformation(origin = {0, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n"
	L"equation\n"
    L"	connect(fixedrotation1.frame_b, joint.frame_a) annotation(Line(points = {{-40, 0}, {-10, 0}}, color = {95, 95, 95}));\n"
    L"	connect(fixedrotation2.frame_b, joint.frame_b) annotation(Line(points = {{40, 0}, {10, 0}}, color = {95, 95, 95}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(lineColor = {85, 170, 255}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-80, -10}, {-20, 10}}), Text(lineColor = {0, 0, 255}, extent = {{-150, 110}, {150, 70}}, textString = \"%%name\"), Ellipse(lineColor = {72, 144, 216}, fillColor = {85, 170, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-50, 50}, {54, -50}}, endAngle = 360), Rectangle(origin = {30, 0}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-30, 68}, {30, -68}}), Rectangle(origin = {100, 0}, lineColor = {220, 220, 220}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.HorizontalCylinder, extent = {{-80, -10}, {-20, 10}}), Ellipse(origin = {-1, -1}, lineColor = {140, 140, 140}, fillColor = {255, 255, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Sphere, extent = {{-29, 31}, {29, -29}}, endAngle = 360)}));\n"
	L"end SphericalPositioned;\n\n"
	,
	L"model RigidPositioned\n"
	L"  extends PartialPositioned;\n"
	L"equation\n"
	L"  connect(fixedrotation1.frame_b, fixedrotation2.frame_b) annotation(Line(points = {{10, 0}, {40, 0}, {40, 0}, {40, 0}}, color = {95, 95, 95}));\n"
	L"  annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Rectangle(lineColor = {85, 170, 255}, fillColor = {85, 170, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{-80, -10}, {-20, 10}}), Rectangle(lineColor = {200, 200, 200}, fillColor = {180, 180, 180}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{80, -10}, {20, 10}}), Text(lineColor = {0, 0, 255}, extent = {{-150, 110}, {150, 70}}, textString = \"%%name\"), Rectangle(origin = {-80, -50}, lineColor = {200, 200, 200}, fillColor = {180, 180, 180}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, extent = {{100, 0}, {60, 100}}), Polygon(origin = {-5.28, 0}, fillColor = {85, 170, 255}, pattern = LinePattern.None, fillPattern = FillPattern.Solid, points = {{-14.7236, -50}, {15.2764, -50}, {-4.72361, -40}, {13.2764, -30}, {-4.72361, -20}, {13.2764, -10}, {-4.72361, 0}, {13.2764, 10}, {-4.72361, 20}, {13.2764, 30}, {-4.72361, 40}, {15.2764, 50}, {-14.7236, 50}, {-14.7236, -50}})}));\n"
	L"end RigidPositioned;\n\n"
	};
}

using namespace MoUtil;

bool MoJoint::writeDefinitions(FILE* moFile, const std::vector<MoJointPtr>& joints)
{
	bool defined[eUnknown] = { false, false, false };

	if (joints.empty())
		return true;

	// all joints extend a base that includes positioning within two frames
	_ftprintf_s(moFile, jointBaseDef);

	for (auto& joint: joints)
	{
		if (joint->type() >= eUnknown)
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
	m_type(eUnknown)
{
}

MoJoint::~MoJoint(void)
{
}

void MoJoint::init(MoBodyWPtr b1, const Matrix3d& bodyFrame1, MoBodyWPtr b2, const Matrix3d& bodyFrame2)
{
	m_body1 = b1;
	m_bodyFrame1 = bodyFrame1;
	m_bodyFrame1 *= .01;
	m_body2 = b2;
	m_bodyFrame2 = bodyFrame2;
	m_bodyFrame2 *= .01;
}

bool MoJoint::write(FILE* moFile) const
{
	TCHAR* typeNames[eUnknown] = { L"RevolutePositioned", L"PrismaticPositioned", L"CylindricalPositioned", L"PlanarPositioned", L"SphericalPositioned", L"RigidPositioned" };

	if (m_type >= eUnknown)
	{
		ASSERT(0);
		return false;
	}

	std::wstring nameStr = name();

	std::wstring initialValues;

	switch(m_type)
	{
		case eRevolute:
		{
			Vector3d xAxis1(m_bodyFrame1(0,0), m_bodyFrame1(1,0), m_bodyFrame1(2,0));
			Vector3d xAxis2(m_bodyFrame2(0,0), m_bodyFrame2(1,0), m_bodyFrame2(2,0));
			Vector3d zAxis1(m_bodyFrame1(0,2), m_bodyFrame1(1,2), m_bodyFrame1(2,2));
			double angle = xAxis1.angle(xAxis2, zAxis1);
			TCHAR str[MAX_PATH];
			_stprintf_s<MAX_PATH>(str, L"joint.phi(start = %s, fixed = true), ", angleString(angle).c_str());
			initialValues = str;
		}
		break;

		case ePrismatic:
		{
			Vector3d origin1(m_bodyFrame1(0,3), m_bodyFrame1(1,3), m_bodyFrame1(2,3));
			Vector3d origin2(m_bodyFrame2(0,3), m_bodyFrame2(1,3), m_bodyFrame2(2,3));
			Vector3d delta = origin2 - origin1;
			double distance = delta.length();
			TCHAR str[MAX_PATH];
			_stprintf_s<MAX_PATH>(str, L"joint.s(start = %s, fixed = true), ", distanceString(distance).c_str());
			initialValues = str;
		}
		break;

		case eCylindrical:
		{
			Vector3d xAxis1(m_bodyFrame1(0,0), m_bodyFrame1(1,0), m_bodyFrame1(2,0));
			Vector3d xAxis2(m_bodyFrame2(0,0), m_bodyFrame2(1,0), m_bodyFrame2(2,0));
			Vector3d zAxis1(m_bodyFrame1(0,2), m_bodyFrame1(1,2), m_bodyFrame1(2,2));
			double angle = xAxis1.angle(xAxis2, zAxis1);
			Vector3d origin1(m_bodyFrame1(0,3), m_bodyFrame1(1,3), m_bodyFrame1(2,3));
			Vector3d origin2(m_bodyFrame2(0,3), m_bodyFrame2(1,3), m_bodyFrame2(2,3));
			Vector3d delta = origin2 - origin1;
			double distance = delta.length();
			TCHAR str[MAX_PATH];
			_stprintf_s<MAX_PATH>(str, L"joint.s(start = %s, fixed = true), joint.phi(start = %s, fixed = true),",
				distanceString(distance).c_str(), angleString(angle).c_str());
			initialValues = str;
		}
		break;

		case ePlanar:
		{
			// it is not clear that we will get different planes that will create values
			Vector3d xAxis1(m_bodyFrame1(0,0), m_bodyFrame1(1,0), m_bodyFrame1(2,0));
			Vector3d yAxis1(m_bodyFrame1(0,1), m_bodyFrame1(1,1), m_bodyFrame1(2,1));
			Vector3d xAxis2(m_bodyFrame2(0,0), m_bodyFrame2(1,0), m_bodyFrame2(2,0));
			Vector3d zAxis1(m_bodyFrame1(0,2), m_bodyFrame1(1,2), m_bodyFrame1(2,2));
			double angle = xAxis1.angle(xAxis2, zAxis1);
			Vector3d origin1(m_bodyFrame1(0,3), m_bodyFrame1(1,3), m_bodyFrame1(2,3));
			Vector3d origin2(m_bodyFrame2(0,3), m_bodyFrame2(1,3), m_bodyFrame2(2,3));
			Vector3d delta = origin2 - origin1;
			double distanceX = delta.dot(xAxis1);
			double distanceY = delta.dot(yAxis1);
			TCHAR str[MAX_PATH];
			_stprintf_s<MAX_PATH>(str, L"joint.s_x(start = %s, fixed = true), joint.s_y(start = %s, fixed = true), joint.phi(start = %s, fixed = true),",
				distanceString(distanceX).c_str(), distanceString(distanceY).c_str(), angleString(angle).c_str());
			initialValues = str;
		}
		break;

		case eSpherical:
		{
			// since we don't get axis info from kMatePointPointSphere, the initial angles will be 0,0,0
		}
		break;
	}

	_ftprintf_s(moFile, L"  %s %s(%sr1 = %s, n1_x = %s, n1_y = %s, r2 = %s, n2_x = %s, n2_y = %s) annotation(%s);\n\n",
		typeNames[m_type], name().c_str(),

		initialValues.c_str(),

		pointString (m_bodyFrame1(0,3), m_bodyFrame1(1,3), m_bodyFrame1(2,3)).c_str(),
		vectorString(m_bodyFrame1(0,0), m_bodyFrame1(1,0), m_bodyFrame1(2,0)).c_str(),
		vectorString(m_bodyFrame1(0,1), m_bodyFrame1(1,1), m_bodyFrame1(2,1)).c_str(),

		pointString (m_bodyFrame2(0,3), m_bodyFrame2(1,3), m_bodyFrame2(2,3)).c_str(),
		vectorString(m_bodyFrame2(0,0), m_bodyFrame2(1,0), m_bodyFrame2(2,0)).c_str(),
		vectorString(m_bodyFrame2(0,1), m_bodyFrame2(1,1), m_bodyFrame2(2,1)).c_str(),

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

const Matrix3d& MoJoint::frame(size_t index) const
{
	ASSERT(index < 2);
	if (index == 0)
		return m_bodyFrame1;
	else
		return m_bodyFrame2;
}


LPCTSTR MoJoint::baseName() const
{
	static TCHAR* baseNames[eUnknown] = { L"revolute", L"slider", L"cylindrical", L"planar", L"spherical", L"rigid" };
	if (type() >= eUnknown)
	{
		ASSERT(0);
		return L"unknown";
	}

	return baseNames[type()];
}
