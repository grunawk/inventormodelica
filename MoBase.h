#pragma once
#include "StdAfx.h"
#include <io.h>
#include <memory>

class MoBase
{
public:
	MoBase(MoId id=0);
	virtual ~MoBase(void);

	virtual bool write(FILE* moFile) const = 0;
	virtual LPCTSTR baseName() const = 0;

	MoId id() const { return m_id; }
	void id(MoId id) { m_id = id; }
	void name(const UTxString& n) { m_name = n; }
	UTxString name() const;

	bool inDiagram() { return m_diagramRow >= 0; }
	void diagramRowColumn(int row, int col);

private:
	MoId m_id;
	UTxString m_name;
	int m_diagramRow;
	int m_diagramCol;
};

