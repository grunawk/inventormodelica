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

	for (auto moJoint: m_joints)
		moJoint->connections(moFile);

	_ftprintf_s(moFile, L"end %s;\n", name().c_str());

	return true;
}

