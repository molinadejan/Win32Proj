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
	
	Point  center;   // �߽� ��ǥ
	Point  dir;      // �̵�����
	double mass;     // ���� ���� (���� ������)
	double  distance; // �ٸ� �������� �Ÿ��� ������ ����
	SHAPE  type;     // ���� Ÿ��

	//Shape2D(SHAPE _type) : center({ 0, 0 }), dir({ 0, 0 }), mass(1), distance(0), type(_type) { }
	Shape2D(double _x, double _y, double _mass, SHAPE _type) : center({ _x, _y }), dir({ 0, 0 }), mass(_mass), distance(0), type(_type) { }

public:

	inline Point  GetCenter() const { return center; }
	inline Point  GetDir()    const { return dir;    }
	inline double  GetMass()   const { return mass;   }
	inline int    GetType()   const { return type;   }

	inline void SetCenter(double _x, double _y) { center = { _x, _y }; }
	inline void SetDir(double _x, double _y)    { dir = { _x, _y };    }
	inline void SetMass(double _mass)          { mass = _mass;        }

	// ������ ��ġ ����
	virtual void Update() { center.x += dir.x; center.y += dir.y; }
	
	// ������ ������ â �浹 üũ
	virtual void Collision(RECT rect) = 0;

	// ������ �ٸ� ���� �浹 üũ
	virtual void Collision(Shape2D* other) = 0;

	// ���� �׸���
	virtual void Draw(HDC hdc) = 0;

	// ��ĥ�� ó��
	virtual void Overlap(Shape2D* other) = 0;

	void Bounce(const Point& normal, const Point& tangent, const Point& myDir, Shape2D* other);
};

#endif // !__CIRCLE2D_H__
