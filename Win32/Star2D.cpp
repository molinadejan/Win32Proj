#include "Star2D.h"
#include "Geometry.h"

Star2D::Star2D(float _x, float _y, float _r)
	: Circle2D(_x, _y, _r, SHAPE::STAR), rsDegree(0), rsRadian(0)
{
	float angleRadian = Deg2Rad(72);

	points[0] = { 0.0f, -GetRadius() };

	for (int i = 2; i < 10; i += 2)
		points[i] = Rotate({ 0, 0 }, points[i - 2], angleRadian);

	bool check = false;

	points[1] = GetIntersection(points[0], points[4], points[8], points[2], check);

	for (int i = 3; i < 10; i += 2)
		points[i] = Rotate({ 0,0 }, points[i - 2], angleRadian);
}

void Star2D::SetRotationalSpeedDegree(float _rs)
{
	rsDegree = _rs;
	rsRadian = Deg2Rad(_rs);
}

void Star2D::Update()
{
	Shape2D::Update();

	for (int i = 0; i < 10; ++i)
		points[i] = Rotate({ 0, 0 }, points[i], rsRadian);
}

void Star2D::Draw(HDC hdc)
{
	for (int i = 0; i < 10; ++i)
	{
		MoveToEx(hdc, points[i].x + center.x, points[i].y + center.y, NULL);
		LineTo(hdc, points[(i + 1) % 10].x + center.x, points[(i + 1) % 10].y + center.y);
	}
}
