#pragma once

#ifndef __STAR2D_H__
#define __STAR2D_H__

#include "Circle2D.h"

class Star2D : public Circle2D
{
private:

	// 회전 속도 (degree)
	float rsDegree;
	// 회전 속도 (radian)
	float rsRadian;

	Point points[10];

public:

	Star2D(float _x, float _y, float _r);

	void SetRotationalSpeedDegree(float _rs);

	void Update() override;
	void Draw(HDC hdc) override;
};

#endif // !__STAR2D_H__
