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

	MoId id() const { return m_id; }
	void id(MoId id) { m_id = id; }
	void name(const UTxString& n) { m_name = n; }
	UTxString name() const;
	virtual LPCTSTR baseName() const = 0;

private:
	MoId m_id;
	UTxString m_name;
};

