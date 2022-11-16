#include"mathUtil.h"
#include"CATMULL_ROM.h"
VECTOR CATMULL_ROM::compute(size_t startIdx, float t) const
{
	//startIdxが範囲外
	//if (startIdx >= points.size())
	//	return points.back();
	//else if (startIdx == 0)
	//	return points[startIdx];
	//else if (startIdx >= points.size()-2)
	//	return points[startIdx];

	//p0からp3までの制御点を取得
	VECTOR p0 = points[startIdx-1];
	VECTOR p1 = points[startIdx];
	VECTOR p2 = points[startIdx+1];
	VECTOR p3 = points[startIdx+2];

	//Catmull-Rom方程式
	return 0.5f * (
		(2.0f * p1) + 
		(-p0 + p2) * t +
		(2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t +
		(-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t
		);
}
VECTOR CATMULL_ROM::compute(size_t startIdx, float t, float r) const
{
	////startIdxが範囲外
	//if (startIdx >= points.size())
	//	return points.back();
	//else if (startIdx == 0)
	//	return points[startIdx];
	//else if (startIdx >= points.size() - 2)
	//	return points[startIdx];

	//p0からp3までの制御点を取得
	VECTOR p0 = points[startIdx - 1];
	VECTOR p1 = points[startIdx];
	VECTOR p2 = points[startIdx + 1];
	VECTOR p3 = points[startIdx + 2];

	//Catmull-Rom テンションあり
	return p1 +
		(-r * p0 + r * p2) * t +
		(2 * r * p0 + (r - 3) * p1 + (3 - 2 * r) * p2 + -r * p3) * t * t +
		(-r * p0 + (2 - r) * p1 + (r - 2) * p2 + r * p3) * t * t * t;

}
VECTOR CATMULL_ROM::derivative(size_t startIdx, float t, float r) const
{
	//startIdxが範囲外
	//if (startIdx >= points.size())
	//	return points.back();
	//else if (startIdx == 0)
	//	return points[startIdx];
	//else if (startIdx >= points.size() - 2)
	//	return points[startIdx];

	//p0からp3までの制御点を取得
	VECTOR p0 = points[startIdx - 1];
	VECTOR p1 = points[startIdx];
	VECTOR p2 = points[startIdx + 1];
	VECTOR p3 = points[startIdx + 2];

	//Derivative Catmull-Rom テンションあり
	return 
		(-r * p0 + r * p2) +
		(2 * r * p0 + (r - 3) * p1 + (3 - 2 * r) * p2 + -r * p3) * 2 * t +
		(-r * p0 + (2 - r) * p1 + (r - 2) * p2 + r * p3) * 3 * t * t;

}
VECTOR CATMULL_ROM::derivative(size_t startIdx, float t) const
{
	//startIdxが範囲外
	//if (startIdx >= points.size())
	//	return points.back();
	//else if (startIdx == 0)
	//	return points[startIdx];
	//else if (startIdx >= points.size() - 2)
	//	return points[startIdx];

	//p0からp3までの制御点を取得
	VECTOR p0 = points[startIdx - 1];
	VECTOR p1 = points[startIdx];
	VECTOR p2 = points[startIdx + 1];
	VECTOR p3 = points[startIdx + 2];

	return 0.5f * ( 
		(-1.0f * p0 + p2) +
		(2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * 2 * t +
		(-1.0f * p0 + 3.0f * p1 - 3.0f * p2 + p3) * 3 * t * t
		);
}
