#pragma once

#ifndef __SHAPE2D_H__
#define __SHAPE2D_H__

#include <windows.h>
#include <math.h>

// ��ǥ ����ü
struct Point
{
	float x, y;
};

class Shape2D
{
protected:
	
	Point  center;   // �߽� ��ǥ
	Point  dir;      // �̵�����
	float  mass;     // ���� ���� (���� ������)
	float  distance; // �ٸ� �������� �Ÿ��� ������ ����
	int    type;     // ���� Ÿ��

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

	// ������ ��ġ ����
	virtual void Update()      = 0;
	
	// ������ ������ â �浹 üũ
	virtual void Collision(RECT rect) = 0;

	// ������ �ٸ� ���� �浹 üũ
	virtual void Collision(Shape2D* other) = 0;

	// ���� �׸���
	virtual void Draw(HDC hdc) = 0;

	// ��ĥ�� ó��
	virtual void Overlap(Shape2D* other) = 0;
};

#endif // !__CIRCLE2D_H__
