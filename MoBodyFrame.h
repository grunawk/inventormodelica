#pragma once
#include "MoBase.h"
#include <gemat3d.h>

class MoBodyFrame : public MoBase
{
public:
	MoBodyFrame(MoBodyPtr body, const AcGeMatrix3d& transform);
	virtual ~MoBodyFrame();

	const AcGeMatrix3d transform() const { return m_transform; }

	virtual bool write(FILE* moFile) const;
	bool connections(FILE* moFile) const;

	UTxString frame() const;

	virtual LPCTSTR baseName() const { return L"bodyFrame"; }

private:
	MoBodyWPtr m_body;
	AcGeMatrix3d m_transform;
};

