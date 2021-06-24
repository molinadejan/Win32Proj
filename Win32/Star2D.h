#pragma once

#ifndef __STAR2D_H__
#define __STAR2D_H__

#include "Circle2D.h"

class Star2D : public Circle2D
{
private:

	// ȸ�� �ӵ� (degree)
	float rsDegree;
	// ȸ�� �ӵ� (radian)
	float rsRadian;

	Point points[10];

public:

	Star2D(float _x, float _y, float _r);

	void SetRotationalSpeedDegree(float _rs);

	void Update() override;
	void Draw(HDC hdc) override;
};

#endif // !__STAR2D_H__
