#include "stdafx.h"
#include "MoUtil.h"

#define MAX_STRING 200

namespace MoUtil {

std::wstring angleString(double angle)
{
	TCHAR str[MAX_STRING];
	// radians
	_stprintf_s<MAX_STRING>(str, L"%.8g", angle);		
	return str;
}

std::wstring distanceString(double distance)
{
	TCHAR str[MAX_STRING];
	// meters
	_stprintf_s<MAX_STRING>(str, L"%.8g", distance);		
	return str;
}

std::wstring vectorString(double x, double y, double z)
{
	TCHAR str[MAX_STRING];
	// unit vector
	_stprintf_s<MAX_STRING>(str, L"{%.8g, %.8g, %.8g}", x, y, z);		
	return str;
}

std::wstring pointString(double x, double y, double z)
{
	TCHAR str[MAX_STRING];
	// unit vector
	_stprintf_s<MAX_STRING>(str, L"{%.8g, %.8g, %.8g}", x, y, z);		
	return str;
}

std::wstring connection(double x1, double y1, double x2, double y2)
{
	TCHAR str[MAX_STRING];
	if (x2 > x1)
	{
		if (y2 != y1)
			_stprintf_s<MAX_STRING>(str, L"Line(points = {{%f, %f}, {%f, %f}, {%f, %f}}, color = {95, 95, 95})", x1, y1, x1, y2, x2, y2);		
		else
			_stprintf_s<MAX_STRING>(str, L"Line(points = {{%f, %f}, {%f, %f}}, color = {95, 95, 95})", x1, y1, x2, y2);
	}
	else
	{
		_stprintf_s<MAX_STRING>(str, L"Line(points = {{%f, %f}, {%f, %f}, {%f, %f}, {%f, %f}}, color = {95, 95, 95})", x1, y1, x1, y1-10, x2, y1-10, x2, y2);
	}

	return str;
}

}