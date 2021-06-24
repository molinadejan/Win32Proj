#pragma once

#ifndef __STAR2D_H__
#define __STAR2D_H__

#include "Circle2D.h"

class Star2D : public Circle2D
{
private:

	// 회전 속도 (degree)
	double rsDegree;
	// 회전 속도 (radian)
	double rsRadian;

	Point points[10];

public:

	Star2D(double _x, double _y, double _r);

	void SetRotationalSpeedDegree(double _rs);

	void Update() override;
	void Draw(HDC hdc) override;
};

#endif // !__STAR2D_H__
