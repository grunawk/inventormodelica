#include "stdafx.h"
#include "MoAssembly.h"
#include "MoJoint.h"
#include "MoBody.h"
#include "MoBodyFrame.h"
#include "MoDiagram.h"

MoAssembly::MoAssembly(void)
{
}

MoAssembly::~MoAssembly(void)
{
}

bool MoAssembly::write(FILE* moFile) const
{
	MoDiagram moDiagram;

	double xMax = 20;
	double yMax = 30;
	for (auto moBody: m_bodies)
	{
		if (!moBody->inDiagram())
			return false;

		if (moBody->diagramX() > xMax)
			xMax = moBody->diagramX();
	}

	for (auto moJoint: m_joints)
	{
		if (!moJoint->inDiagram())
			return false;

		if (moJoint->diagramX() > xMax)
			xMax = moJoint->diagramX();
	}

	xMax +=

	_ftprintf_s(moFile, L"model %s\n", name().c_str());

	for (auto moBody: m_bodies)
		moBody->write(moFile, moDiagram);

	_ftprintf_s(moFile, L"  inner Modelica.Mechanics.MultiBody.World world annotation(%s);\n", moDiagram.placement(*this).c_str());

	for (auto moJoint: m_joints)
		moJoint->write(moFile, moDiagram);

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
		moJoint->connections(moFile, moDiagram);

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
	// world location in top/right
	diagramPosition(20.0,30.0);
	double y = 20.0;

	// first start with grounded bodies
	for (auto& body: m_bodies)
	{
		if (body->inDiagram())
			continue;

		if (body->grounded())
		{
			layout(body, 60, y);
		}
	}

	// add any remaining bodies
	for (auto& body: m_bodies)
	{
		if (body->inDiagram())
			continue;

		layout(body, 60, y);
	}
}

void MoAssembly::layout(MoBodyPtr& body, double x, double& nextY)
{
	body->diagramPosition(x, nextY);

	for (auto& joint: m_joints)
	{
		size_t frameIndex;

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
		nextY += 40;
	}
}

