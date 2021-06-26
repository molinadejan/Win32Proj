#pragma once

#ifndef __SHAPE2D_H__
#define __SHAPE2D_H__

#include <windows.h>
#include <math.h>
#include "Geometry.h"

enum SHAPE
{
	NONE,
	LINE,
	CIRCLE,
	STAR,
	RECTANGLE,
};

class Shape2D
{
protected:
	
	Point  center;   // 중심 좌표
	Point  dir;      // 이동방향
	double mass;     // 도형 질량 (아직 미적용)
	//double  distance; // 다른 도형과의 거리를 저장할 변수
	SHAPE  type;     // 도형 타입

	//Shape2D(SHAPE _type) : center({ 0, 0 }), dir({ 0, 0 }), mass(1), distance(0), type(_type) { }
	Shape2D(double _x, double _y, double _mass, SHAPE _type) : center({ _x, _y }), dir({ 0, 0 }), mass(_mass), type(_type) { }

public:

	Point  GetCenter() const { return center; }
	Point  GetDir()    const { return dir;    }
	double GetMass()   const { return mass;   }
	int    GetType()   const { return type;   }

	inline void SetCenter(double _x, double _y) { center = { _x, _y }; }
	void SetCenter(const Point& p) { center = p; }
	void SetDir(double _x, double _y)    { dir = { _x, _y };    }
	void SetMass(double _mass)          { mass = _mass;        }

	// 도형의 위치 갱신
	virtual void Update() { center.x += dir.x; center.y += dir.y; }
	
	// 도형과 윈도우 창 충돌 체크
	virtual void Collision(RECT rect) = 0;

	// 도형과 다른 도형 충돌 체크
	virtual void Collision(Shape2D* other) = 0;

	// 도형 그리기
	virtual void Draw(HDC hdc) = 0;

	// 겹칠때 처리
	virtual void Overlap(Shape2D* other) = 0;

	void Bounce(const Point& normal, const Point& myDir, Shape2D* other);
};

#endif // !__CIRCLE2D_H__
