#include "Circle2D.h"
#include "Rectangle2D.h"

void Circle2D::Collision(RECT rect)
{
	if (center.x < radius)
	{
		center.x = radius;
		dir.x *= -1;
	}

	if (center.x > rect.right - radius)
	{
		center.x = rect.right - radius;
		dir.x *= -1;
	}

	if (center.y < radius)
	{
		center.y = radius;
		dir.y *= -1;
	}

	if (center.y > rect.bottom - radius)
	{
		center.y = rect.bottom - radius;
		dir.y *= -1;
	}
}

// 참고 자료 : https://youtu.be/ebq7L2Wtbl4
// 참고 코드 : https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Balls1.cpp

void Circle2D::Collision(Shape2D* other)
{
	if (type > other->GetType())
	{
		other->Collision(this);
		return;
	}

	Circle2D *c = dynamic_cast<Circle2D *>(other);

	if (c)
	{
		double distance = GetDistance(c->GetCenter(), center);

		if (distance  <= c->GetRadius() + radius)
		{
			// 노멀 벡터 (원의 중심 - 원의 중심) 의 정규화
			double nx = (c->GetCenter().x - center.x) / distance;
			double ny = (c->GetCenter().y - center.y) / distance;

			// 노말과 접선 벡터를 인자로
			Bounce({ nx, ny }, {-ny, nx}, dir, other);
		}
		
		return;
	}

	Rectangle2D *r = dynamic_cast<Rectangle2D *>(other);
	
	if (r)
	{
		for (int i = 0; i < 4; ++i)
		{
			double distance = GetDistance(center, r->GetCenter() + r->GetPoint(i));

			if (distance <= radius + 5.0f)
			{
				double nx = (center.x - (r->GetPoint(i).x + r->GetCenter().x)) / distance;
				double ny = (center.y - (r->GetPoint(i).y + r->GetCenter().y)) / distance;

				Bounce({ nx, ny }, {-ny, nx}, dir, other);

				return;
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			double ux = (r->GetPoint((i + 1) % 4).x - r->GetPoint(i).x);
			double uy = (r->GetPoint((i + 1) % 4).y - r->GetPoint(i).y);

			// 원의 중심 - 꼭지점 벡터 c
			double cx = center.x - (r->GetPoint(i).x + r->GetCenter().x);
			double cy = center.y - (r->GetPoint(i).y + r->GetCenter().y);

			double dotProj = (ux * cx + uy * cy) / (r->GetLen() * r->GetLen());

			double pointX = r->GetPoint(i).x + r->GetCenter().x + dotProj * ux;
			double pointY = r->GetPoint(i).y + r->GetCenter().y + dotProj * uy;

			double minX = min(r->GetPoint(i).x + r->GetCenter().x, r->GetPoint((i + 1) % 4).x + r->GetCenter().x);
			double maxX = max(r->GetPoint(i).x + r->GetCenter().x, r->GetPoint((i + 1) % 4).x + r->GetCenter().x);

			double minY = min(r->GetPoint(i).y + r->GetCenter().y, r->GetPoint((i + 1) % 4).y + r->GetCenter().y);
			double maxY = max(r->GetPoint(i).y + r->GetCenter().y, r->GetPoint((i + 1) % 4).y + r->GetCenter().y);

			bool check = false;

			if (minX <= pointX && pointX <= maxX && minY <= pointY && pointY <= maxY) check = true;

			if (check && (distance = GetDistance(center, { pointX, pointY })) <= radius)
			{
				double nx = (center.x - pointX) / distance;
				double ny = (center.y - pointY) / distance;

				Bounce({ nx, ny }, { -ny, nx }, dir, other);
			}

			return;
		}
	}
}

void Circle2D::Overlap(Shape2D * other)
{
	Circle2D *c = dynamic_cast<Circle2D *>(other);

	if (c)
	{
		double distance = GetDistance(c->GetCenter(), center);

		if (distance < radius + c->radius)
		{
			double overlap = (distance - radius - c->GetRadius()) * 0.5f;

			center.x -= overlap * (center.x - c->GetCenter().x) / distance;
			center.y -= overlap * (center.y - c->GetCenter().y) / distance;

			double targetCX = c->GetCenter().x + overlap * (center.x - c->GetCenter().x) / distance;
			double targetCY = c->GetCenter().y + overlap * (center.y - c->GetCenter().y) / distance;
		
			c->SetCenter(targetCX, targetCY);
		}
	}

	Rectangle2D *r = dynamic_cast<Rectangle2D *>(other);

	if (r)
	{
		for (int i = 0; i < 4; ++i)
		{
			double distance = GetDistance(center, r->GetCenter() + r->GetPoint(i));

			if (distance < radius)
			{
				double nx = (center.x - (r->GetPoint(i).x + r->GetCenter().x)) / distance;
				double ny = (center.y - (r->GetPoint(i).y + r->GetCenter().y)) / distance;

				double overlap = (distance - radius) * 0.5f;

				center.x -= overlap * nx;
				center.y -= overlap * ny;

				double targetCX = r->GetCenter().x + overlap * nx;
				double targetCY = r->GetCenter().y + overlap * ny;

				r->SetCenter(targetCX, targetCY);
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			double ux = (r->GetPoint((i + 1) % 4).x - r->GetPoint(i).x);
			double uy = (r->GetPoint((i + 1) % 4).y - r->GetPoint(i).y);

			// 원의 중심 - 꼭지점 벡터 c
			double cx = center.x - (r->GetPoint(i).x + r->GetCenter().x);
			double cy = center.y - (r->GetPoint(i).y + r->GetCenter().y);

			double dotProj = (ux * cx + uy * cy) / (r->GetLen() * r->GetLen());

			double pointX = r->GetPoint(i).x + r->GetCenter().x + dotProj * ux;
			double pointY = r->GetPoint(i).y + r->GetCenter().y + dotProj * uy;

			double minX = min(r->GetPoint(i).x + r->GetCenter().x, r->GetPoint((i + 1) % 4).x + r->GetCenter().x);
			double maxX = max(r->GetPoint(i).x + r->GetCenter().x, r->GetPoint((i + 1) % 4).x + r->GetCenter().x);

			double minY = min(r->GetPoint(i).y + r->GetCenter().y, r->GetPoint((i + 1) % 4).y + r->GetCenter().y);
			double maxY = max(r->GetPoint(i).y + r->GetCenter().y, r->GetPoint((i + 1) % 4).y + r->GetCenter().y);

			bool check = false;

			if (minX <= pointX && pointX <= maxX && minY <= pointY && pointY <= maxY) check = true;

			double distance = GetDistance(center, { pointX, pointY });

			if (check && (distance = GetDistance(center, { pointX, pointY })) < radius)
			{
				double nx = (center.x - pointX) / distance;
				double ny = (center.y - pointY) / distance;

				double overlap = (distance - radius) * 0.5f;

				center.x -= overlap * nx;
				center.y -= overlap * ny;

				double targetCX = r->GetCenter().x + overlap * nx;
				double targetCY = r->GetCenter().y + overlap * ny;

				r->SetCenter(targetCX, targetCY);
			}
		}
	}
}

void Circle2D::Draw(HDC hdc)
{
	//DrawCircle(hdc, center, radius);
	Ellipse(hdc,
		(int)floor(center.x - radius + 0.5f),
		(int)floor(center.y - radius + 0.5f),
		(int)floor(center.x + radius + 0.5f), 
		(int)floor(center.y + radius + 0.5f)
	);
}
