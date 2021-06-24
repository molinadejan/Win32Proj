#pragma once

#ifndef __ROTATESHAPE2D_H__
#define __ROTATESHAPE2D_H__

#include "Shape2D.h"
#include "Geometry.h"

class Rectangle2D : public Shape2D
{
protected:

	// 회전 속도 (degree)
	float rsDegree;

	// 회전 속도 (radian)
	float rsRadian;

public:

	//Rectangle2D(SHAPE _type) : Shape2D(_type), rotate(0) { } 
	Rectangle2D(float _x, float _y, float _len) : Shape2D(_x, _y, 1, SHAPE::RECTANGLE), rsDegree(0), rsRadian(0) { }

	void SetRotationalSpeedDegree(float _rs);

	void Update() override;
	void Collision(RECT rect) override;
	void Collision(Shape2D* other) override;
	void Draw(HDC hdc) override;
	void Overlap(Shape2D* other) override;
};

#endif // !__ROTATESHAPE2D_H__
