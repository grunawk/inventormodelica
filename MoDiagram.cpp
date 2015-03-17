#include "stdafx.h"
#include "MoDiagram.h"

MoDiagram::MoDiagram(void)
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
