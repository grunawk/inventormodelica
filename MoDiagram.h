#pragma once
#include "StdAfx.h"
#include <gepnt2d.h>

class MoDiagram
{
public:
	MoDiagram(void);
	~MoDiagram(void);

	static void writeLineLR(FILE* moFile, const AcGePoint2d& p1, const AcGePoint2d& p2);

	bool addExtent(const MoBase& moBase);
	std::wstring placement(const MoBase& moBase) const;

private:
	int m_maxRow;
	int m_maxCol;
};

