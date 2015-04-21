#include "types.h"
#include "MoBody.h"

MoBody::MoBody(void) :
	MoBase(),
	m_cg(),
	m_mass(0.0),
	m_inertia(Vector3d::kZero, Vector3d::kZero)
{
}

MoBody::~MoBody(void)
{
}

void MoBody::addMass(double mass, const Vector3d& cg, const InertiaTensor& inertia)
{
	m_mass += mass;
	m_cg += cg;
	m_inertia += inertia;
}

std::wstring MoBody::definitionName() const
{
	std::wstring def = name();
	def += L"Model";
	return def;
}

bool MoBody::write(FILE* moFile) const
{
	std::wstring nameStr = name();
	std::wstring defStr = definitionName();

	// --- begin definition of body

	fwprintf_s(moFile, L"  model %s\n", defStr.c_str());

	fwprintf_s(moFile, L"    Modelica.Mechanics.MultiBody.Parts.Body body1 (m = %.8g, I_11 = %.8g, I_22 = %.8g, I_33 = %.8g, I_21 = %.8g, I_31 = %.8g, I_32 = %.8g, r_CM = {%.8g, %.8g, %.8g}) "
						L"annotation(Placement(visible = true, transformation(origin = {0, 10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n",
				m_mass,
				m_inertia.moments()[0],  m_inertia.moments()[1],  m_inertia.moments()[2],
				m_inertia.products()[0], m_inertia.products()[1], m_inertia.products()[2],
				m_cg.x(), m_cg.y(), m_cg.z());

	// frame interface
	fwprintf_s(moFile, L"    Modelica.Mechanics.MultiBody.Interfaces.Frame_a frame annotation(Placement(visible = true, transformation(origin = {0, -100}, extent = {{-10, -10}, {10, 10}}, rotation = 90), iconTransformation(origin = {0, -100}, extent = {{-10, -10}, {10, 10}}, rotation = 90)));\n");

	fwprintf_s(moFile, L"  equation\n");

	// connect frame interface to body frame
	fwprintf_s(moFile, L"    connect(body1.frame_a, frame) annotation(Line(points = {{0, 0}, {0, -100}}, color = {95, 95, 95}));\n");

	// --- diagram and icon annotations for definition

	fwprintf_s(moFile, L"    annotation("
						L"Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}))"
						L", Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})");
//						L", Text(origin = {-12, 121}, extent = {{-128, 19}, {152, -21}}, textString = \"%%name%%\")");

	// icon thumbnail if present
	if (m_thumbnail.empty())
		fwprintf_s(moFile, L"));\n"); // close Icon and annotation
	else
		fwprintf_s(moFile, L", graphics = {Bitmap(origin = {0, 0}, extent = {{-100, -100}, {100, 100}}, imageSource = \"%S\"), Text(extent = {{-150, 145}, {150, 105}}, textString = \"%%name\", lineColor = {0, 0, 255})}));\n",
			m_thumbnail.c_str());

	fwprintf_s(moFile, L"  end %s;\n\n", defStr.c_str());

	// --- end definition

	// occurrence
	fwprintf_s(moFile, L"  %s %s annotation(%s);\n\n", defStr.c_str(), nameStr.c_str(), placement().c_str());

	return true;
}
