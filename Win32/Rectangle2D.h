#pragma once

#ifndef __ROTATESHAPE2D_H__
#define __ROTATESHAPE2D_H__

#include "Shape2D.h"
#include "Geometry.h"

class Rectangle2D : public Shape2D
{
protected:

	// ȸ�� �ӵ� (degree)
	double rsDegree;

	// ȸ�� �ӵ� (radian)
	double rsRadian;

	// �»� - ��� - ���� - ����
	Point points[4];

	double len;
public:

	Rectangle2D(double _x, double _y, double _len);

	Point GetRelativePoint(int idx) { return points[idx]; }
	Point GetAbsolutePoint(int idx) { return points[idx] + center; }
	double GetLen() { return len; }

	void SetRotationalSpeedDegree(double _rs);

	void Update() override;
	void Collision(RECT rect) override;
	void Collision(Shape2D* other) override;
	void Draw(HDC hdc) override;
	void Overlap(Shape2D* other) override;
};

#endif // !__ROTATESHAPE2D_H__
