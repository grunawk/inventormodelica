#include "stdafx.h"
#include "MoDiagram.h"
#include "MoBase.h"

MoDiagram::MoDiagram(void) :
	m_maxRow(-1),
	m_maxCol(-1)
{
}


MoDiagram::~MoDiagram(void)
{
}

void MoDiagram::writeLineLR(FILE* moFile, const AcGePoint2d& p1, const AcGePoint2d& p2)
{
	if (p1.y == p2.y)
	{
		_ftprintf_s(moFile, L"Line(points = {{%f, %f}, {%f, %f}}, color = {95, 95, 95})", p1.x, p1.y, p2.x, p2.y);
	}
	else
	{
		_ftprintf_s(moFile, L"Line(points = {{%f, %f}, {%f, %f}, {%f, %f}, {%f, %f}}, color = {95, 95, 95})", p1.x, p1.y, p2.x, p2.y);
	}
}

bool MoDiagram::addExtent(const MoBase& moBase)
{
	if (moBase.inDiagram())
	{
		if (moBase.diagramRow() > m_maxRow)
			m_maxRow = moBase.diagramRow();
		if (moBase.diagramColumn() > m_maxCol)
			m_maxCol = moBase.diagramColumn();
	}
	else
		return false;

	return true;
}

UTxString MoDiagram::placement(const MoBase& moBase) const
{
	double x = 20.0 + moBase.diagramColumn() * 20.0 + 10.0;
	double y = 20.0 + moBase.diagramRow() * 20.0 + 10.0;

	TCHAR str[MAX_PATH];
	_stprintf_s<MAX_PATH>(str,L"Placement(visible = true, transformation(origin = {%f, %f}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));\n", x, y);
	return str;
}
