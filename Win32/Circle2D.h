#pragma once
#ifndef __CIRCLE2D_H__
#define __CIRCLE2D_H__

#include "Shape2D.h"
#include "Shape2D.cpp"

class Circle2D : public Shape2D
{
private:

	float radius; // ¹ÝÁö¸§

public:
	
	Circle2D() : Shape2D(1), radius(1) { }
	Circle2D(float _x, float _y, float _r) : Shape2D(_x, _y, _r * _r * 3.14f / 10.0f, 1), radius(_r) { }

	inline float GetRadius() const { return radius; }

	void Update() override;
	void Collision(RECT rect) override;
	void Collision(Shape2D* other) override;

	void Draw(HDC hdc) override;
};

#endif // !__CIRCLE2D_H__

