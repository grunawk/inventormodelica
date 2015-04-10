#include "stdafx.h"
#include "MoAssembly.h"
#include "MoJoint.h"
#include "MoBody.h"
#include "MoUtil.h"

using namespace MoUtil;

MoAssembly::MoAssembly(void) :
	m_lastBodyId(0),
	m_lastJointId(0),
	m_gravity(eUniformGravity),
	m_gravityVec(0,-1,0)
{
}

MoAssembly::~MoAssembly(void)
{
}

void MoAssembly::addBody(const MoBodyPtr& body)
{
	m_bodies.push_back(body);
	body->id(++m_lastBodyId);
}

void MoAssembly::addJoint(const MoJointPtr& joint)
{
	m_joints.push_back(joint);
	joint->id(++m_lastJointId);
}

bool MoAssembly::write(FILE* moFile) const
{
	bool defineRevolute = false;
	bool definePrismatic = false;

	// diagram upperleft is 0,0 and lowerright is -X,Y

	double xMax = 0;
	double yMin = 0;

	// include "world" in diagram extents
	if (!extendDiagram(xMax, yMin))
		return false;

	// include bodies in diagram extents
	for (auto moBody: m_bodies)
		if (!moBody->extendDiagram(xMax,yMin))
			return false;

	// include joints in diagram extents and also check for needed definitions
	for (auto moJoint: m_joints)
	{
		if (!moJoint->extendDiagram(xMax,yMin))
			return false;
		else if (moJoint->type() == MoJoint::eRevolute)
			defineRevolute = true;
		else
			definePrismatic = true;
	}

	// add border
	xMax += 30;
	yMin -= 30;

	_ftprintf_s(moFile, L"model %s\n\n", name().c_str());

	MoJoint::writeDefinitions(moFile, m_joints);

	switch(m_gravity)
	{
	case eNoGravity:
		_ftprintf_s(moFile, L"  inner Modelica.Mechanics.MultiBody.World world(gravityType = Modelica.Mechanics.MultiBody.Types.GravityTypes.NoGravity) annotation(%s);\n\n",
			placement().c_str());
		break;

	case eUniformGravity:
		_ftprintf_s(moFile, L"  inner Modelica.Mechanics.MultiBody.World world(n=%s) annotation(%s);\n\n",
			vectorString(m_gravityVec).c_str(), placement().c_str());
		break;

	default:
		_ftprintf_s(moFile, L"  inner Modelica.Mechanics.MultiBody.World world(gravityType = Modelica.Mechanics.MultiBody.Types.GravityTypes.PointGravity, n=%s) annotation(%s);\n\n",
			vectorString(m_gravityVec).c_str(), placement().c_str());
	}


	for (auto moBody: m_bodies)
		moBody->write(moFile);

	for (auto moJoint: m_joints)
		moJoint->write(moFile);

	_ftprintf_s(moFile, L"equation\n");

	for (auto moBody: m_bodies)
	{
		if (moBody->grounded())
		{
			if (moBody->diagramX() > 60)
			{
				_ftprintf_s(moFile, L"  connect(%s.frame, world.frame_b) annotation(%s);\n",
					moBody->name().c_str(), connection(moBody->diagramX(), moBody->diagramY()-10, diagramX()+10, diagramY()).c_str());
			}
			else
			{
				_ftprintf_s(moFile, L"  connect(world.frame_b, %s.frame) annotation(%s);\n",
					moBody->name().c_str(), connection(diagramX()+10, diagramY(), moBody->diagramX(), moBody->diagramY()-10).c_str());
			}
		}
	}

	for (auto moJoint: m_joints)
		moJoint->connections(moFile);

	_ftprintf_s(moFile, L"  annotation("
						L"Diagram(coordinateSystem(extent = {{0, 0}, {%f, %f}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}))"
						L", Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})",
						xMax, yMin);

	if (m_thumbnail.empty())
		_ftprintf_s(moFile, L"));\n"); // close Icon and annotation
	else
		_ftprintf_s(moFile, L", graphics = {Bitmap(origin = {-43, 30}, extent = {{143, -130}, {-57, 70}}, imageSource = \"%S\")}));\n",
			m_thumbnail.c_str());

	_ftprintf_s(moFile, L"end %s;\n", name().c_str());

	return true;
}

void MoAssembly::layout()
{
	// world location in top/right. y goes negative, x goes positive
	diagramPosition(20.0,-30.0);
	double x = 60;	// 20 + 10 to edge of world + gap of 20 + 10 to center of next = 60
	double y = -20; // -10 gap from top - 10 to center of next element (body)

	// first start with grounded bodies
	for (auto& body: m_bodies)
	{
		if (body->inDiagram())
			continue;

		if (body->grounded())
		{
			layout(body, x, y);
			y -= 40;
		}
	}

	// add any remaining bodies
	for (auto& body: m_bodies)
	{
		if (body->inDiagram())
			continue;

		layout(body, x, y);
		y -= 40;
	}
}

void MoAssembly::layout(MoBodyPtr& body, double x, double& nextY)
{
	body->diagramPosition(x, nextY);
	x += 40;

	bool firstJoint = true;
	for (auto& joint: m_joints)
	{
		if (joint->inDiagram())
			continue;

		int bodyIndex = -1;

		if (joint->body(0) == body)
			bodyIndex = 0;
		else if (joint->body(1) == body)
		{
			bodyIndex = 1;
			joint->flipHorizontal(true);
		}

		if (bodyIndex >= 0)
		{
			if (firstJoint)
				firstJoint = false;
			else
				nextY -= 40;

			joint->diagramPosition(x, nextY-10);
	
			if (MoBodyPtr body2 = joint->body(bodyIndex == 1 ? 0 : 1))
			{
				if (!body2->inDiagram())
				{
					layout(body2, x + 40, nextY);
				}
			}
		}
	}
}

