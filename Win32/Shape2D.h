#pragma once

#ifndef __SHAPE2D_H__
#define __SHAPE2D_H__

#include <windows.h>
#include <math.h>

// 좌표 구조체
struct Point
{
	float x, y;
};

class Shape2D
{
protected:
	
	Point  center;   // 중심 좌표
	Point  dir;      // 이동방향
	float  mass;     // 도형 질량 (아직 미적용)
	float  distance; // 다른 도형과의 거리를 저장할 변수
	int    type;     // 도형 타입

	Shape2D(int _type) : center({ 0, 0 }), dir({ 0, 0 }), mass(1), distance(0), type(_type) { }
	Shape2D(float _x, float _y, float _mass, int _type) : center({ _x, _y }), dir({ 0, 0 }), mass(_mass), distance(0), type(_type) { }

public:

	inline Point  GetCenter() const { return center; }
	inline Point  GetDir()    const { return dir;    }
	inline float  GetMass()   const { return mass;   }
	inline int    GetType()   const { return type;   }

	inline void SetCenter(float _x, float _y) { center = { _x, _y }; }
	inline void SetDir(float _x, float _y)    { dir = { _x, _y };    }
	inline void SetMass(float _mass)          { mass = _mass;        }

	// 도형의 위치 갱신
	virtual void Update()      = 0;
	
	// 도형과 윈도우 창 충돌 체크
	virtual void Collision(RECT rect) = 0;

	// 도형과 다른 도형 충돌 체크
	virtual void Collision(Shape2D* other) = 0;

	// 도형 그리기
	virtual void Draw(HDC hdc) = 0;

	// 겹칠때 처리
	virtual void Overlap(Shape2D* other) = 0;
};

#endif // !__CIRCLE2D_H__
