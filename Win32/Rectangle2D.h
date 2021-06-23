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
	Rectangle2D(float _x, float _y, float _mass, float _rs) : Shape2D(_x, _y, _mass, SHAPE::RECTANGLE), rsDegree(_rs), rsRadian(Deg2Rad(_rs)) { }

	inline float GetRotate() const { return rsDegree; }


};

#endif // !__ROTATESHAPE2D_H__
