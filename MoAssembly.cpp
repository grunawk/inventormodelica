#include "stdafx.h"
#include "MoAssembly.h"
#include "MoJoint.h"
#include "MoBody.h"

MoAssembly::MoAssembly(void)
{
}

MoAssembly::~MoAssembly(void)
{
}

bool MoAssembly::write(FILE* moFile) const
{
	_ftprintf_s(moFile, L"model %s\n", name().c_str());

	for (auto moBody: m_bodies)
		moBody->write(moFile);

	_ftprintf_s(moFile, L"  inner Modelica.Mechanics.MultiBody.World world annotation(Placement(visible = true, transformation(origin = {-72, 68}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n");

	for (auto moJoint: m_joints)
		moJoint->write(moFile);

	_ftprintf_s(moFile, L"equation\n");

	for (auto moBody: m_bodies)
		if (moBody->grounded())
			_ftprintf_s(moFile, L"  connect(%s.%s, world.frame_b) annotation(Line(points = {{-40, 70}, {-60, 70}}, color = {95, 95, 95}));\n",
				moBody->name().c_str(), moBody->bodyFrameBaseName());

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
	// treat assembly space as grid with 0,0 at lower left
	// put world at 0,0
	// put grounded at (2,0) (2,2) .. (n*2,2)
	// 


}

