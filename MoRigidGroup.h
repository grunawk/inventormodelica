#pragma once
#include "StdAfx.h"
#include "MoBody.h"

class MoRigidGroup
{
public:
	MoRigidGroup(void);
	virtual ~MoRigidGroup(void);

	HRESULT add(;

	bool write(FILE* moFile) const;

private:
	std::vector<MoBody*> m_bodies;
};

