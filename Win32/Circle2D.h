#pragma once
#ifndef __CIRCLE2D_H__
#define __CIRCLE2D_H__

#include "Shape2D.h"

class Circle2D : public Shape2D
{
private:

	float radius;   // ¹ÝÁö¸§

public:
	
	//Circle2D() : Shape2D(SHAPE::CIRCLE), radius(1) { }
	Circle2D(float _x, float _y, float _r, SHAPE _shape = SHAPE::CIRCLE) : Shape2D(_x, _y, 1, _shape), radius(_r) { }

	inline float GetRadius() const { return radius; }

	//void Update() override;
	void Collision(RECT rect) override;
	void Collision(Shape2D* other) override;
	void Overlap(Shape2D* other) override;
	void Draw(HDC hdc) override;
};

#endif // !__CIRCLE2D_H__

