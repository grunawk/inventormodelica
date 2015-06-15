#include "types.h"
#include "MoBase.h"

MoBase::MoBase() :
	m_id(0),
	m_x(0.0),
	m_y(0.0),
	m_rotation(0.0),
	m_flipHorizontal(false),
	m_inDiagram(false)
{
}

MoBase::~MoBase(void)
{
}

void MoBase::name(const std::wstring& n)
{
	m_name = n;
	for (std::wstring::iterator i=m_name.begin(); i!=m_name.end(); ++i)
		if (*i == L' ')
			*i = L'_';
}

std::wstring MoBase::name() const
{
	wchar_t cstr[MAX_PATH];
	if (defaultNamed())
	{
		if (id() > 0)
		{
			swprintf_s(cstr, MAX_PATH, L"%s%d", baseName(), id());
			return cstr;
		}
		return baseName();
	}
	return m_name;
}

std::wstring MoBase::placement() const
{
	static double ext[] = {-10, -10, 10, 10};
	static double flip[] = {10, -10, -10, 10};

	wchar_t str[MAX_PATH];
	if (m_flipHorizontal)
		swprintf_s(str, MAX_PATH, L"Placement(visible = true, transformation(origin = {%f, %f}, extent = {{%f, %f}, {%f, %f}}, rotation = %f))", m_x, m_y, flip[0], flip[1], flip[2], flip[3], m_rotation);
	else
		swprintf_s(str, MAX_PATH, L"Placement(visible = true, transformation(origin = {%f, %f}, extent = {{%f, %f}, {%f, %f}}, rotation = %f))", m_x, m_y, ext[0], ext[1], ext[2], ext[3], m_rotation);

	return str;
}

bool MoBase::extendDiagram(double& xMax, double& yMin) const
{
	if (!inDiagram())
		return false;

	if (diagramX() > xMax)
		xMax = diagramX();

	if (diagramY() < yMin)
		yMin = diagramY();

	return true;
}
