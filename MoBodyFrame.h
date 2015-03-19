#pragma once
#include "MoBase.h"
#include <gemat3d.h>

class MoBodyFrame : public MoBase
{
public:
	MoBodyFrame(MoBodyPtr body, const AcGeMatrix3d& transform);
	virtual ~MoBodyFrame();

	const AcGeMatrix3d transform() const { return m_transform; }

	virtual bool write(FILE* moFile, MoDiagram& moDiagram) const;
	bool connections(FILE* moFile, MoDiagram& moDiagram) const;

	MoBodyPtr body() { return m_body.lock(); }

	UTxString frame() const;

	virtual LPCTSTR baseName() const { return L"bodyFrame"; }

	void diagramInterface(size_t i) { m_diagramInterface = i; }

private:
	MoBodyWPtr m_body;
	AcGeMatrix3d m_transform;

	bool m_diagramLeft;
	float m_diagramRightIndex;
	size_t m_diagramInterface;
};

