#include "stdafx.h"
#include "MoBody.h"
#include "MoBodyFrame.h"

static double gap = 20.0;
static double width = 20.0;
static double height = 20.0;

MoId MoBody::m_lastId = 0;

MoBody::MoBody(void) :
	MoBase(++m_lastId),
	m_cg(AcGePoint3d::kOrigin),
	m_mass(0.0)
{
	m_placement.x = gap + (m_lastId-1) * (width + gap) + width/2;
	m_placement.y = gap + height/2;
	m_width = width;
	m_height = height;
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

void MoBody::addBodyFrame(MoBodyFramePtr bodyFrame)
{
	m_bodyFrames.push_back(bodyFrame);
	bodyFrame->id(static_cast<MoId>(m_bodyFrames.size()));
}

bool MoBody::write(FILE* moFile, MoDiagram& moDiagram) const
{
	double halfWidth = m_width/2;
	double halfHeight = m_height/2;

	UTxString nameStr = name();

	_ftprintf_s(moFile, L"  model %s\n", nameStr.c_str());

	//  Modelica.Mechanics.MultiBody.Parts.Body body1(m = .5, I_11 = 0.1, I_22 = 0.1, I_33 = 0.1, I_21 = 0.2, I_31 = 0.3, I_32 = 0.4, 
	//  r_CM = {1, 2, 3}, r_0(start = {2, 3, 4})) annotation(Placement(visible = true, transformation(origin = {-44, 18}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));

	_ftprintf_s(moFile, L"    Modelica.Mechanics.MultiBody.Parts.Body body1 (m = %g, I_11 = %g, I_22 = %g, I_33 = %g, I_21 = %g, I_31 = %g, I_32 = %g, r_CM = {%g, %g, %g}) "
						L"annotation(Placement(visible = true, transformation(origin = {0, 10}, extent = {{-10, -10}, {10, 10}}, rotation = 90)));\n",
				m_mass,
				m_inertia.m_momentsOfInertia[0],  m_inertia.m_momentsOfInertia[1],  m_inertia.m_momentsOfInertia[2],
				m_inertia.m_productsOfInertia[0], m_inertia.m_productsOfInertia[1], m_inertia.m_productsOfInertia[2],
				m_cg[0], m_cg[1], m_cg[2]);

	_ftprintf_s(moFile, L"    Modelica.Mechanics.MultiBody.Interfaces.Frame_a %s annotation(Placement(visible = true, transformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {-100, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n",
						bodyFrameBaseName());

	for (auto bodyFrame: m_bodyFrames)
		bodyFrame->write(moFile);

	_ftprintf_s(moFile, L"  equation\n");

	_ftprintf_s(moFile, L"    connect(body1.frame_a, %s) annotation(Line(points = {{0, 0}, {-48, 0}}, color = {95, 95, 95}));\n",
						bodyFrameBaseName());

	for (auto bodyFrame: m_bodyFrames)
		bodyFrame->connections(moFile);

	_ftprintf_s(moFile, L"    annotation("
						L"Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}))"
						L", Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})");

	if (m_thumbnail.empty())
		_ftprintf_s(moFile, L"));\n"); // close Icon and annotation
	else
		_ftprintf_s(moFile, L", graphics = {Bitmap(origin = {-43, 30}, extent = {{143, -130}, {-57, 70}}, imageSource = \"%S\")}));\n",
			m_thumbnail.c_str());

	_ftprintf_s(moFile, L"  end %s;\n", name().c_str());

	_ftprintf_s(moFile, L"  %s %s_1 annotation(Placement(visible = true, transformation(origin = {%g, %g}, extent = {{-%g, -%g}, {%g, %g}}, rotation = 0)));\n",
		nameStr.c_str(), nameStr.c_str(),
		m_placement.x, m_placement.y,
		halfWidth, halfHeight, halfWidth, halfHeight);

	return true;
}

void MoBody::nextDiagramInterface(MoBodyFramePtr& frame)
{
	if (std::find(m_bodyFrames.begin(), m_bodyFrames.end(), frame) == m_bodyFrames.end())
	{
		ASSERT(0);
	}

	frame->diagramInterface(m_nextDiagramInferface++);
}
