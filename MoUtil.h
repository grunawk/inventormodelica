#pragma once
#include "types.h"

class InertiaTensor;

namespace MoUtil
{
	// model functions

	std::wstring angleString(double angle);
	std::wstring distanceString(double distance);
	std::wstring massString(double mass);
	std::wstring inertiaString(const InertiaTensor& inertia);
	std::wstring vectorString(double x, double y, double z);
	std::wstring pointString(double x, double y, double z);

	// diagram functions

	std::wstring connection(double x1, double y1, double x2, double y2);
};


