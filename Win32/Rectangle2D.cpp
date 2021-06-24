#include "Rectangle2D.h"

Rectangle2D::Rectangle2D(double _x, double _y, double _len)
	: Shape2D(_x, _y, 1, SHAPE::RECTANGLE), rsDegree(0), rsRadian(0), len(_len)
{
	double half = _len / 2;

	points[0] = { -half, -half };
	points[1] = { half, -half };
	points[2] = { half, half };
	points[3] = { -half, half };
}

void Rectangle2D::SetRotationalSpeedDegree(double _rs)
{
	rsDegree = _rs;
	rsRadian = Deg2Rad(_rs);
}

void Rectangle2D::Update()
{
	Shape2D::Update();

	for (int i = 0; i < 4; ++i)
		points[i] = Rotate({ 0, 0 }, points[i], rsRadian);
}

void Rectangle2D::Collision(RECT rect)
{
	for (int i = 0; i < 4; ++i)
	{
		if (points[i].x + center.x < 0)
		{
			dir.x *= -1;
			center.x = fabs(points[i].x);
		}

		if (points[i].x + center.x > rect.right)
		{
			dir.x *= -1;
			center.x = rect.right - points[i].x;
		}

		if (points[i].y + center.y < 0)
		{
			dir.y *= -1;
			center.y = fabs(points[i].y);
		}

		if (points[i].y + center.y > rect.bottom)
		{
			dir.y *= -1;
			center.y = rect.bottom - points[i].y;
		}
	}
}

void Rectangle2D::Collision(Shape2D * other)
{
	if (type > other->GetType())
	{
		other->Collision(this);
		return;
	}


}

void Rectangle2D::Draw(HDC hdc)
{
	for (int i = 0; i < 4; ++i)
	{
		MoveToEx(hdc, points[i].x + center.x, points[i].y + center.y, NULL);
		LineTo(hdc, points[(i + 1) % 4].x + center.x, points[(i + 1) % 4].y + center.y);
	}
}

void Rectangle2D::Overlap(Shape2D * other)
{

}
