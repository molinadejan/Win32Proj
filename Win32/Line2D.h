#pragma once

#ifndef __LINE2D_H__
#define __LINE2D_H__

#include "Shape2D.h"

class Line2D : public Shape2D
{
private:

	// 회전 속도 (degree)
	float rsDegree;

	// 회전 속도 (radian)
	float rsRadian;

	// 끝 (중심 기준 벡터)
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
