#pragma once

#include "MoBase.h"
#include "MoBody.h"

class MoJoint : public MoBase
{
public:
	MoJoint(void);
	virtual ~MoJoint(void);

	virtual bool write(FILE* moFile) const;
	bool connections(FILE* moFile) const;

	void frame1(MoBodyFrameWPtr frame) { m_frame1 = frame; }
	void frame2(MoBodyFrameWPtr frame) { m_frame2 = frame; }

	MoBodyFrameWPtr frame1() const { return m_frame1; }
	MoBodyFrameWPtr frame2() const { return m_frame2; }

	enum Type { eRevolute, ePrismatic };

	Type type() const { return m_type; }
	void type(Type t) { m_type = t; }

	MoBodyFramePtr frame(MoBodyPtr& body, size_t& frameIndex);

	MoBodyPtr body(size_t index);

	void diagramFlipHorizontal(bool flip) { m_diagramFlipHorizontal = flip; }

	virtual LPCTSTR baseName() const
	{
		switch(m_type)
		{
		case eRevolute:		return L"revolute";
		case ePrismatic:	return L"slider";
		default:			return L"joint";
		}
	}

private:
	static int m_lastId;

private:
	Type m_type;
	MoBodyFrameWPtr m_frame1, m_frame2;
	bool m_diagramFlipHorizontal;
};




