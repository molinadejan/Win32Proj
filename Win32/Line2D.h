#pragma once

#ifndef __LINE2D_H__
#define __LINE2D_H__

#include "Shape2D.h"

class Line2D : public Shape2D
{
private:

	// ȸ�� �ӵ� (degree)
	float rsDegree;

	// ȸ�� �ӵ� (radian)
	float rsRadian;

	// �� (�߽� ���� ����)
	Point start, end;

	Point contact;

public:

	Line2D(float cx, float cy, float length);
	Line2D(float sx, float sy, float ex, float ey);

	void SetRotationalSpeedDegree(float _rs);

	void Update() override;
	virtual void Collision(RECT rect);
	virtual void Collision(Shape2D* other);
	virtual void Draw(HDC hdc);
	virtual void Overlap(Shape2D* other);
};

#endif // !__LINE2D_H__
