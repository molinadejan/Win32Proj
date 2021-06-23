#include "Line2D.h"
#include "Circle2D.h"

#include <math.h>
#include "Geometry.h"

Line2D::Line2D(float cx, float cy, float length)
	: Shape2D(cx, cy, 1, SHAPE::LINE)
{
	float half = length / 2;

	start = { -half, 0 };
	end = { half, 0 };
}

Line2D::Line2D(float sx, float sy, float ex, float ey)
	: Shape2D((sx + ex) / 2, (sy + ey) / 2, 1, SHAPE::LINE)
{
	start = { sx - center.x, sy - center.y };
	end = { ex - center.x, ey - center.y };
}

void Line2D::SetRotationalSpeedDegree(float _rs)
{
	rsDegree = _rs;
	rsRadian = Deg2Rad(_rs);
}

void Line2D::Update()
{
	Shape2D::Update();

	start = Rotate({0, 0}, start, rsRadian);
	end = Rotate({ 0, 0 }, end, rsRadian);
}

void Line2D::Collision(RECT rect)
{
	float limitX = (float)fabs(start.x);
	float limitY = (float)fabs(start.y);
	
	if (center.x < limitX)
	{
		dir.x *= -1;
		center.x = limitX;
	}

	if (center.x > rect.right - limitX)
	{
		dir.x *= -1;
		center.x = rect.right - limitX;
	}

	if (center.y < limitY)
	{
		dir.y *= -1;
		center.y = limitY;
	}

	if (center.y > rect.bottom - limitY)
	{
		dir.y *= -1;
		center.y = rect.bottom - limitY;
	}
}

void Line2D::Collision(Shape2D * other)
{
	Circle2D *c = dynamic_cast<Circle2D *>(other);
	
	if (c)
	{
		bool isCollision = false;

		if (GetDistance(c->GetCenter(), start) <= c->GetRadius() || GetDistance(c->GetCenter(), end) <= c->GetRadius())
			isCollision = true;

		// 직선 벡터
		float lx = end.x - start.x;
		float ly = end.y - start.y;

		//// 한 점(start)에서 원의 중심까지의 벡터
		//float px = c->GetCenter().x - (start.x + center.x);
		//float py = c->GetCenter().y - (start.y + center.y);

		float lineLen = sqrt(lx * lx + ly * ly);

		//float dot = (lx * px + ly * py) / lineLen * lineLen;

		//if (dot >= 0 && dot <= lineLen)
		//{
		//	float contactX = start.x + center.x + dot * lx;
		//	float contactY = start.y + center.y + dot * ly;

		//	distance = GetDistance(c->GetCenter(), { contactX, contactY });
		//}
		
		if (isCollision /*|| distance <= c->GetRadius()*/)
		{
			// 접선 벡터 
			float tx = lx / lineLen;
			float ty = ly / lineLen;

			// 노멀 벡터 접선과 수직
			float nx = -ty;
			float ny = tx;

			// dir 내적 접선 벡터 
			float dpTan1 = dir.x * tx + dir.y * ty;
			float dpTan2 = c->GetDir().x * tx + c->GetDir().y * ty;

			// dir 내적 노멀 벡터
			float dpNorm1 = dir.x * nx + dir.y * ny;
			float dpNorm2 = c->GetDir().x * nx + c->GetDir().y * ny;

			float m1 = dpNorm2;
			float m2 = dpNorm1;

			SetDir(tx * dpTan1 + nx * m1, ty * dpTan1 + ny * m1);
			c->SetDir(tx * dpTan2 + nx * m2, ty * dpTan2 + ny * m2);
		}
	}
}

void Line2D::Draw(HDC hdc)
{
	int sx = (int)floor(center.x + start.x + 0.5f);
	int sy = (int)floor(center.y + start.y + 0.5f);

	int ex = (int)floor(center.x + end.x + 0.5f);
	int ey = (int)floor(center.y + end.y + 0.5f);

	MoveToEx(hdc, sx, sy, NULL);
	LineTo(hdc, ex, ey);
}

void Line2D::Overlap(Shape2D * other)
{
}
