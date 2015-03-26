#include "stdafx.h"
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

std::wstring MoBase::name() const
{
	if (m_name.empty())
	{
		TCHAR cstr[MAX_PATH];
		_stprintf_s<MAX_PATH>(cstr, L"%s%d", baseName(), id());
		return cstr;
	}

	return m_name;
}

std::wstring MoBase::placement() const
{
	static double ext[] = {-10, -10, 10, 10};
	static double flip[] = {10, -10, -10, 10};

	TCHAR str[MAX_PATH];
	if (m_flipHorizontal)
		_stprintf_s<MAX_PATH>(str,L"Placement(visible = true, transformation(origin = {%f, %f}, extent = {{%f, %f}, {%f, %f}}, rotation = %f))", m_x, m_y, flip[0], flip[1], flip[2], flip[3], m_rotation);
	else
		_stprintf_s<MAX_PATH>(str,L"Placement(visible = true, transformation(origin = {%f, %f}, extent = {{%f, %f}, {%f, %f}}, rotation = %f))", m_x, m_y, ext[0], ext[1], ext[2], ext[3], m_rotation);

	return str;
}

std::wstring MoBase::connection(double x1, double y1, double x2, double y2) const
{
	TCHAR str[MAX_PATH];
	if (x2 > x1)
	{
		if (y2 != y1)
			_stprintf_s<MAX_PATH>(str, L"Line(points = {{%f, %f}, {%f, %f}, {%f, %f}}, color = {95, 95, 95})", x1, y1, x1, y2, x2, y2);		
		else
			_stprintf_s<MAX_PATH>(str, L"Line(points = {{%f, %f}, {%f, %f}}, color = {95, 95, 95})", x1, y1, x2, y2);
	}
	else
	{
		_stprintf_s<MAX_PATH>(str, L"Line(points = {{%f, %f}, {%f, %f}, {%f, %f}, {%f, %f}}, color = {95, 95, 95})", x1, y1, x1, y1-10, x2, y1-10, x2, y2);
	}

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
