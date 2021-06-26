#include "Rectangle2D.h"
#include "Circle2D.h"

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

	Rectangle2D *r = dynamic_cast<Rectangle2D*>(other);

	if (r)
	{
		Point stdPoint = GetAbsolutePoint(0);

		Point stdX = GetAbsolutePoint(1) - stdPoint;
		Point stdY = GetAbsolutePoint(3) - stdPoint;

		for (int i = 0; i < 4; ++i)
		{
			Point stdToOtherPoint = r->GetAbsolutePoint(i) - stdPoint;

			double projX = Dot(stdX, stdToOtherPoint) / (len * len);
			double projY = Dot(stdY, stdToOtherPoint) / (len * len);

			if (projX >= 0 && projX <= 1 && projY >= 0 && projY <= 1)
			{
				Point normal;

				if (projX < projY)
					normal = stdY;
				else if (projX > projY)
					normal = stdX;
				else
					normal = stdToOtherPoint;

				normal /= GetDistance(normal, { 0, 0 });

				Bounce(normal, dir, other);

				return;
			}
		}
		
		stdPoint = r->GetAbsolutePoint(0);

		stdX = r->GetAbsolutePoint(1) - stdPoint;
		stdY = r->GetAbsolutePoint(3) - stdPoint;

		for (int i = 0; i < 4; ++i)
		{
			Point stdToOtherPoint = GetAbsolutePoint(i) - stdPoint;

			double projX = Dot(stdX, stdToOtherPoint) / (r->GetLen() * r->GetLen());
			double projY = Dot(stdY, stdToOtherPoint) / (r->GetLen() * r->GetLen());

			if (projX >= 0 && projX <= 1 && projY >= 0 && projY <= 1)
			{
				Point normal;

				if (projX < projY)
					normal = stdY;
				else if (projX > projY)
					normal = stdX;
				else
					normal = stdToOtherPoint;

				normal /= GetDistance(normal, { 0, 0 });

				Bounce(normal, dir, other);

				return;
			}
		}
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
	if (type > other->GetType())
	{
		other->Overlap(this);
		return;
	}

	return;

	Rectangle2D *r = dynamic_cast<Rectangle2D *>(other);

	if (r)
	{
	//	double s1x = points[1].x - points[0].x;
	//	double s1y = points[1].y - points[0].y;

	//	double s2x = points[2].x - points[1].x;
	//	double s2y = points[2].y - points[1].y;

	//	// ±‚¡ÿ¿∫ points[0];

	//	for (int i = 0; i < 4; ++i)
	//	{
	//		double px = r->GetCenter().x + r->GetRelativePoint(i).x - (points[0].x + center.x);
	//		double py = r->GetCenter().y + r->GetRelativePoint(i).y - (points[0].y + center.y);

	//		double dotProj1 = (s1x * px + s1y * py) / (len * len);
	//		double dotProj2 = (s2x * px + s2y * py) / (len * len);

	//		if ((dotProj1 > 0 && dotProj1 < 1) && (dotProj2 > 0 && dotProj2 < 1))
	//		{
	//			double distance = GetDistance({ 0, 0 }, {px, py});

	//			double nx = px / distance;
	//			double ny = py / distance;

	//			float overlap;

	//			if (dotProj1 > dotProj2)
	//				overlap = distance / dotProj1 * (1.0f - dotProj1) / 2;
	//			else
	//				overlap = distance / dotProj2 * (1.0f - dotProj2) / 2;

	//			center.x -= overlap * nx;
	//			center.y -= overlap * ny;

	//			double targetCX = r->GetCenter().x + overlap * nx;
	//			double targetCY = r->GetCenter().y + overlap * ny;

	//			r->SetCenter(targetCX, targetCY);

	//			return;
	//		}
	//	}

	//	s1x = r->GetRelativePoint(1).x - r->GetRelativePoint(0).x;
	//	s1y = r->GetRelativePoint(1).y - r->GetRelativePoint(0).y;

	//	s2x = r->GetRelativePoint(2).x - r->GetRelativePoint(1).x;
	//	s2y = r->GetRelativePoint(2).y - r->GetRelativePoint(1).y;

	//	for (int i = 0; i < 4; ++i)
	//	{
	//		double px = (points[i].x + center.x) - (r->GetCenter().x + r->GetRelativePoint(0).x);
	//		double py = (points[i].y + center.y) - (r->GetCenter().y + r->GetRelativePoint(0).y);

	//		double dotProj1 = (s1x * px + s1y * py) / (r->GetLen() * r->GetLen());
	//		double dotProj2 = (s2x * px + s2y * py) / (r->GetLen() * r->GetLen());

	//		if ((dotProj1 > 0 && dotProj1 < 1) && (dotProj2 > 0 && dotProj2 < 1))
	//		{
	//			float distance = GetDistance({ 0, 0 }, { px, py });

	//			double nx = px / distance;
	//			double ny = py / distance;

	//			float overlap;

	//			if (dotProj1 > dotProj2)
	//				overlap = distance / dotProj1 * (1.0f - dotProj1) / 2;
	//			else
	//				overlap = distance / dotProj2 * (1.0f - dotProj2) / 2;

	//			double targetCX = r->GetCenter().x - overlap * nx;
	//			double targetCY = r->GetCenter().y - overlap * ny;

	//			r->SetCenter(targetCX, targetCY);

	//			center.x += overlap * nx;
	//			center.y += overlap * ny;

	//			return;
	//		}
	//	}
	}
}
