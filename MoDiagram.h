#pragma once
#include "StdAfx.h"
#include <gepnt2d.h>

class MoDiagram
{
public:
	MoDiagram(void);
	~MoDiagram(void);

	static void writeLineLR(FILE* moFile, const AcGePoint2d& p1, const AcGePoint2d& p2);
};

