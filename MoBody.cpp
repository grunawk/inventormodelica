#include "stdafx.h"
#include "MoBody.h"
#include "MoDiagram.h"

MoId MoBody::m_lastId = 0;

MoBody::MoBody(void) :
	MoBase(++m_lastId),
	m_cg(AcGePoint3d::kOrigin),
	m_mass(0.0)
{
}

MoBody::~MoBody(void)
{
}

void MoBody::addMass(double mass, const AcGePoint3d& cg, const MIxInertiaTensor& inertia)
{
	m_mass += mass;
	m_cg += cg.asVector();
	m_inertia += inertia;
}

bool MoBody::write(FILE* moFile) const
{
	std::wstring nameStr = name();

	// --- begin definition of body

	_ftprintf_s(moFile, L"  model %s\n", nameStr.c_str());

	//  Modelica.Mechanics.MultiBody.Parts.Body body1(m = .5, I_11 = 0.1, I_22 = 0.1, I_33 = 0.1, I_21 = 0.2, I_31 = 0.3, I_32 = 0.4, 
	//  r_CM = {1, 2, 3}, r_0(start = {2, 3, 4})) annotation(Placement(visible = true, transformation(origin = {-44, 18}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));

	_ftprintf_s(moFile, L"    Modelica.Mechanics.MultiBody.Parts.Body body1 (m = %g, I_11 = %g, I_22 = %g, I_33 = %g, I_21 = %g, I_31 = %g, I_32 = %g, r_CM = {%g, %g, %g}) "
						L"annotation(Placement(visible = true, transformation(origin = {0, 10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n",
				m_mass,
				m_inertia.m_momentsOfInertia[0],  m_inertia.m_momentsOfInertia[1],  m_inertia.m_momentsOfInertia[2],
				m_inertia.m_productsOfInertia[0], m_inertia.m_productsOfInertia[1], m_inertia.m_productsOfInertia[2],
				m_cg[0], m_cg[1], m_cg[2]);

	// frame interface
	_ftprintf_s(moFile, L"    Modelica.Mechanics.MultiBody.Interfaces.Frame_a frame annotation(Placement(visible = true, transformation(origin = 0, -100}, extent = {{-10, -10}, {10, 10}}, rotation = 90), iconTransformation(origin = {0, -100}, extent = {{-10, -10}, {10, 10}}, rotation = 90)));\n");

	_ftprintf_s(moFile, L"  equation\n");

	// connect frame interface to body frame
	_ftprintf_s(moFile, L"    connect(body1.frame_a, frame) annotation(Line(points = {{0, 0}, {0, -100}}, color = {95, 95, 95}));\n");

	// --- diagram and icon annotations for definition

	_ftprintf_s(moFile, L"    annotation("
						L"Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}))"
						L", Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})");

	// icon thumbnail if present
	if (m_thumbnail.empty())
		_ftprintf_s(moFile, L"));\n"); // close Icon and annotation
	else
		_ftprintf_s(moFile, L", graphics = {Bitmap(origin = {0, 0}, extent = {-100, -100}, {100, 100}}, imageSource = \"%S\")}));\n",
			m_thumbnail.c_str());

	_ftprintf_s(moFile, L"  end %s;\n", name().c_str());

	// --- end definition

	// occurrence
	_ftprintf_s(moFile, L"  %s %s_1 annotation(%s);\n", nameStr.c_str(), nameStr.c_str(), placement().c_str());

	return true;
}
