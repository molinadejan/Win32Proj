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

// 충돌하는 접점의 작용 힘도 생각

void Line2D::Collision(Shape2D * other)
{
	Circle2D *c = dynamic_cast<Circle2D *>(other);
	
	if (c)
	{
		if ((distance = GetDistance(c->GetCenter(), start + center)) <= c->GetRadius())
		{
			float nx = (c->GetCenter().x - (start.x + center.x)) / distance;
			float ny = (c->GetCenter().y - (start.y + center.y)) / distance;

			Bounce({ nx, ny }, { -ny, nx }, dir, other);

			if (distance < c->GetRadius())
			{
				float overlap = (distance - c->GetRadius()) * 0.5f;

				center.x -= overlap * (start.x + center.x - c->GetCenter().x) / distance;
				center.y -= overlap * (start.y + center.y - c->GetCenter().y) / distance;

				float targetCX = c->GetCenter().x + overlap * (start.x + center.x - c->GetCenter().x) / distance;
				float targetCY = c->GetCenter().y + overlap * (start.y + center.y - c->GetCenter().y) / distance;

				c->SetCenter(targetCX, targetCY);
			}

			contact = start + center;
		}
		else if ((distance = GetDistance(c->GetCenter(), end + center)) <= c->GetRadius())
		{
			float nx = (c->GetCenter().x - (end.x + center.x)) / distance;
			float ny = (c->GetCenter().y - (end.y + center.y)) / distance;

			Bounce({ nx, ny }, { -ny, nx }, dir, other);

			if (distance < c->GetRadius())
			{
				float overlap = (distance - c->GetRadius()) * 0.5f;

				center.x -= overlap * (end.x + center.x - c->GetCenter().x) / distance;
				center.y -= overlap * (end.y + center.y - c->GetCenter().y) / distance;

				float targetCX = c->GetCenter().x + overlap * (end.x + center.x - c->GetCenter().x) / distance;
				float targetCY = c->GetCenter().y + overlap * (end.y + center.y - c->GetCenter().y) / distance;

				c->SetCenter(targetCX, targetCY);
			}

			contact = end + center;
		}
		else
		{
			float ux = end.x - start.x;
			float uy = end.y - start.y;

			float uLen = sqrt(ux * ux + uy * uy);

			float scx = c->GetCenter().x - (start.x + center.x);
			float scy = c->GetCenter().y - (start.y + center.y);

			float dotProj = (ux * scx + uy * scy) / (uLen * uLen);

			float pointX = start.x + center.x + dotProj * ux;
			float pointY = start.y + center.y + dotProj * uy;

			contact = { pointX, pointY };

			if (GetDistance(center, contact) <= uLen / 2 && (distance = GetDistance(c->GetCenter(), { pointX, pointY })) <= c->GetRadius())
			{
				float nx = (c->GetCenter().x - pointX) / distance;
				float ny = (c->GetCenter().y - pointY) / distance;

				/*
				Point newDir = { dir.x + c->GetCenter().x - pointX, dir.y + c->GetCenter().y - pointY };
				
				float newDirLen = sqrt(newDir.x * newDir.x + newDir.y * newDir.y);

				newDir.x /= newDirLen;
				newDir.y /= newDirLen;

				float dirLen = sqrt(dir.x * dir.x + dir.y * dir.y);

				newDir.x *= dirLen;
				newDir.y *= dirLen;
				*/

				Bounce({ nx, ny }, { -ny, nx }, dir, other);

				/*
				rsDegree *= -1;
				rsRadian = Deg2Rad(rsDegree);
				*/

				if (distance < c->GetRadius())
				{
					float overlap = (distance - c->GetRadius()) * 0.5f;

					center.x -= overlap * (pointX - c->GetCenter().x) / distance;
					center.y -= overlap * (pointY - c->GetCenter().y) / distance;

					float targetCX = c->GetCenter().x + overlap * (pointX - c->GetCenter().x) / distance;
					float targetCY = c->GetCenter().y + overlap * (pointY - c->GetCenter().y) / distance;

					c->SetCenter(targetCX, targetCY);
				}
			}
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

	/*Ellipse(hdc,
		(int)floor(contact.x - 10 + 0.5f),
		(int)floor(contact.y - 10 + 0.5f),
		(int)floor(contact.x + 10 + 0.5f),
		(int)floor(contact.y + 10 + 0.5f)
	);

	DrawRectangle(hdc, center, 10, 10);*/
}

void Line2D::Overlap(Shape2D * other)
{
}
