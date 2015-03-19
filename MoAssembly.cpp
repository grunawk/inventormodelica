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

	for (auto moBody: m_bodies)
		if (!moDiagram.addExtent(*moBody))
			return false;

	for (auto moJoint: m_joints)
		if (!moDiagram.addExtent(*moJoint))
			return false;

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
			_ftprintf_s(moFile, L"  connect(%s.%s, world.frame_b) annotation(Line(points = {{%f, %f}, {-60, -70}}, color = {95, 95, 95}));\n",
				moBody->name().c_str(), moBody->bodyFrameBaseName(), moBody->frameDiagramPos().x, moBody->frameDiagramPos().y);
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
	// world location in top/right
	diagramRowColumn(0,0);

	for (auto& body: m_bodies)
	{
		if (body->inDiagram())
			continue;

		int r = 0;
		if (body->grounded())
		{
			layout(body, r, 1);
		}
	}
}

void MoAssembly::layout(MoBodyPtr& body, int& nextRow, int column)
{
	body->diagramRowColumn(nextRow, column);

	int nextColumn = column + 1;
	for (auto& joint: m_joints)
	{
		size_t frameIndex;
		if (joint->inDiagram())
		{
			if (MoBodyFramePtr frame = joint->frame(body, frameIndex))
			{
				body->nextDiagramInterface(frame);
			}
		}

		if (MoBodyFramePtr frame1 = joint->frame(body, frameIndex))
		{
			joint->diagramRowColumn(nextRow, nextColumn);
			if (frameIndex == 1)
				joint->diagramFlipHorizontal(true);
			body->nextDiagramInterface(frame1);

			MoBodyFrameWPtr wFrame2 = frameIndex == 0 ? joint->frame1() : joint->frame2();
			if (auto frame2 = wFrame2.lock())
			{
				if (MoBodyPtr body2 = frame2->body())
				{
					if (!body2->inDiagram())
					{
						if (!body2->grounded())
						{
							layout(body2, nextRow, nextColumn + 1);
						}
					}
					else
					{
						body2->nextDiagramInterface(frame2);
					}
				}
			}
		}
		++nextRow;
	}
}

