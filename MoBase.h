#pragma once
#include "StdAfx.h"
#include <io.h>
#include <memory>
#include <string>

class MoDiagram;

class MoBase
{
public:
	MoBase();
	virtual ~MoBase(void);

	virtual bool write(FILE* moFile) const = 0;
	virtual LPCTSTR baseName() const = 0;

	MoId id() const { return m_id; }
	void id(MoId id) { m_id = id; }
	void name(const std::wstring& n) { m_name = n; }
	std::wstring name() const;

	// diagram properties and methods

	bool inDiagram() const { return m_inDiagram; }
	void diagramPosition(double x, double y) { m_x=x; m_y=y; m_inDiagram=true; }
	double diagramX() const { return m_x; }
	double diagramY() const { return m_y;}
	bool flipHorizontal() const { return m_flipHorizontal; }
	void flipHorizontal(bool flip) { m_flipHorizontal = flip; }
	double rotation() const { return m_rotation; }
	void rotation(double r) { m_rotation = r; }
	bool extendDiagram(double& xMax, double& yMin) const;
	std::wstring placement() const;

private:
	MoId m_id;
	std::wstring m_name;
	int m_diagramRow;
	int m_diagramCol;
	double m_x, m_y;
	bool m_flipHorizontal;
	double m_rotation;
	bool m_inDiagram;
};

