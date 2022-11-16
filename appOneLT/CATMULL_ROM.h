#pragma once
#include<vector>
#include"VECTOR.h"
class CATMULL_ROM {
public:
	std::vector<VECTOR> points;
	VECTOR compute(size_t startIdx, float t)const;
	VECTOR derivative(size_t startIdx, float t)const;
	VECTOR compute(size_t startIdx, float t, float tension) const;
	VECTOR derivative(size_t startIdx, float t, float tension)const;
	void setPoint(float x, float y, float z = 0) {
		points.emplace_back(x, y, z);
	}
	size_t numPoints()const {
		return points.size(); 
	}
};