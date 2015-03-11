#include "stdafx.h"
#include "MoBase.h"


MoBase::MoBase(MoId id) :
	m_id(id)
{
}


MoBase::~MoBase(void)
{
}

UTxString MoBase::name() const
{
	if (m_name.empty())
	{
		TCHAR cstr[MAX_PATH];
		_stprintf_s<MAX_PATH>(cstr, L"%s%d", baseName(), id());
		return cstr;
	}

	return m_name;
}