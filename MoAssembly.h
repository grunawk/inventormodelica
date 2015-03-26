#pragma once
#include "mobase.h"

class MoAssembly :
	public MoBase
{
public:
	MoAssembly(void);
	virtual ~MoAssembly(void);

	virtual bool write(FILE* moFile) const;
	virtual LPCTSTR baseName() const { return L"Assembly"; }

	void addBody(const MoBodyPtr& body);
	void addJoint(const MoJointPtr& joint);

	void thumbnail(const std::string& thumbnail) { m_thumbnail = thumbnail; }

	void layout();

private:
	void layout(MoBodyPtr& body, double x, double& nextY);

	MoId m_lastBodyId;
	MoId m_lastJointId;

	std::vector<MoBodyPtr> m_bodies;
	std::vector<MoJointPtr> m_joints;

	std::string m_thumbnail;
};

