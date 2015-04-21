#pragma once
#include "mobase.h"
#include "Vector3d.h"

class MoAssembly :
	public MoBase
{
public:
	MoAssembly(void);
	virtual ~MoAssembly(void);

	virtual bool write(FILE* moFile) const;
	virtual wchar_t* baseName() const { return L"Assembly"; }

	void addBody(const MoBodyPtr& body);
	void addJoint(const MoJointPtr& joint);

	void thumbnail(const std::string& thumbnail) { m_thumbnail = thumbnail; }

	void layout();

	enum GravityType { eNoGravity, eUniformGravity, ePointGravity };
	void gravityNone() { m_gravity = eNoGravity; }
	void gravityPoint(const Vector3d& vec) { m_gravity = ePointGravity; m_gravityVec = vec; }
	void gravityUniform(const Vector3d& vec) { m_gravity = eUniformGravity; m_gravityVec = vec; m_gravityVec.normalize(); }

private:
	void layout(MoBodyPtr& body, double x, double& nextY);

	MoId m_lastBodyId;
	MoId m_lastJointId;

	std::vector<MoBodyPtr> m_bodies;
	std::vector<MoJointPtr> m_joints;
	GravityType m_gravity;
	Vector3d m_gravityVec;

	std::string m_thumbnail;
};

