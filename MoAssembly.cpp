#include "stdafx.h"
#include "MoAssembly.h"
#include "MoJoint.h"
#include "MoBody.h"
#include "MoDiagram.h"

MoAssembly::MoAssembly(void)
{
}

MoAssembly::~MoAssembly(void)
{
}

bool MoAssembly::write(FILE* moFile) const
{
	bool defineRevolute = false;
	bool definePrismatic = false;

	double xMax = 0;
	double yMin = 0;

	if (!extendDiagram(xMax, yMin))
		return false;

	for (auto moBody: m_bodies)
		if (!moBody->extendDiagram(xMax,yMin))
			return false;

	for (auto moJoint: m_joints)
	{
		if (!moJoint->extendDiagram(xMax,yMin))
			return false;
		else if (moJoint->type() == MoJoint::eRevolute)
			defineRevolute = true;
		else
			definePrismatic = true;
	}

	xMax += 30;
	yMin -= 30;

	_ftprintf_s(moFile, L"model %s\n", name().c_str());

	if (defineRevolute)
		MoJoint::writeDefinition(moFile, MoJoint::eRevolute);

	if (definePrismatic)
		MoJoint::writeDefinition(moFile, MoJoint::ePrismatic);

	for (auto moBody: m_bodies)
		moBody->write(moFile);

	_ftprintf_s(moFile, L"  inner Modelica.Mechanics.MultiBody.World world annotation(%s);\n", placement().c_str());

	for (auto moJoint: m_joints)
		moJoint->write(moFile);

	_ftprintf_s(moFile, L"equation\n");

	for (auto moBody: m_bodies)
	{
		if (moBody->grounded())
		{
			if (moBody->diagramX() > 60)
			{
				_ftprintf_s(moFile, L"  connect(world.frame_b, %s.frame) annotation(%s);\n",
					moBody->name().c_str(), connection(moBody->diagramX(), moBody->diagramY()-10, diagramX()+10, diagramY()));
			}
			else
			{
				_ftprintf_s(moFile, L"  connect(%s.frame, world.frame_b) annotation(%s);\n",
					moBody->name().c_str(), connection(diagramX()+10, diagramY(), moBody->diagramX(), moBody->diagramY()-10));
			}
		}
	}

	for (auto moJoint: m_joints)
		moJoint->connections(moFile);

	_ftprintf_s(moFile, L"  annotation("
						L"Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}))"
						L", Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})");

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
		}
	}

	// add any remaining bodies
	for (auto& body: m_bodies)
	{
		if (body->inDiagram())
			continue;

		layout(body, x, y);
	}
}

void MoAssembly::layout(MoBodyPtr& body, double x, double& nextY)
{
	body->diagramPosition(x, nextY);

	for (auto& joint: m_joints)
	{
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
			joint->diagramPosition(x, nextY+10);
	
			if (MoBodyPtr body2 = joint->body(bodyIndex == 1 ? 0 : 1))
			{
				if (!body2->inDiagram())
				{
					layout(body2, x + 40, nextY);
				}
			}
		}
		nextY -= 40;
	}
}

