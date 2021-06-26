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

// ���� �ڷ� : https://youtu.be/ebq7L2Wtbl4
// ���� �ڵ� : https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Balls1.cpp

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
			Point normal = (c->GetCenter() - center) / distance;
			Bounce(normal, dir, other);
		}
		
		return;
	}

	Rectangle2D *r = dynamic_cast<Rectangle2D *>(other);
	
	if (r)
	{
		for (int i = 0; i < 4; ++i)
		{
			double distance = GetDistance(center,r->GetAbsolutePoint(i));

			if (distance <= radius)
			{
				Point normal = (center - r->GetAbsolutePoint(i)) / distance;
				Bounce(normal, dir, other);

				return;
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			// �簢���� ������
			Point stdPoint = r->GetAbsolutePoint(i);

			// �簢���� �� �� ����
			Point recSide = r->GetAbsolutePoint((i + 1) % 4) - stdPoint;

			// ������ -> ���� �߽� ����
			Point stdToCircleCenter = center - stdPoint;

			// ���翵�� ������ ����
			double proj = Dot(recSide, stdToCircleCenter) / (r->GetLen() * r->GetLen());

			// �浹 ����
			Point colPoint = stdPoint + recSide * proj;

			// �浹 �������� ���� �߽ɱ����� �Ÿ�
			double distance = GetDistance(colPoint, center);

			if (proj >= 0 && proj <= 1 && distance <= radius)
			{
				Point normal = (center - colPoint) / distance;
				Bounce(normal, dir, other);
				return;
			}
		}
	}
}

void Circle2D::Overlap(Shape2D * other)
{
	if (type > other->GetType())
	{
		other->Overlap(this);
		return;
	}

	Circle2D *c = dynamic_cast<Circle2D *>(other);

	if (c)
	{
		double distance = GetDistance(c->GetCenter(), center);

		if (distance < radius + c->radius)
		{
			double overlap = (distance - radius - c->GetRadius()) * 0.5f;

			center = center - overlap * (center - c->GetCenter()) / distance;

			Point newOtherCenter = c->GetCenter() + overlap * (center - c->GetCenter()) / distance;
			c->SetCenter(newOtherCenter);

			return;
		}
	}

	Rectangle2D *r = dynamic_cast<Rectangle2D *>(other);

	if (r)
	{
		for (int i = 0; i < 4; ++i)
		{
			double distance = GetDistance(center,r->GetAbsolutePoint(i));

			if (distance < radius)
			{
				Point normal = (center - r->GetAbsolutePoint(i)) / distance;

				double overlap = (distance - radius) * 0.5f;

				center = center - normal * overlap;

				Point newOtherCenter = r->GetCenter() + overlap * normal;

				r->SetCenter(newOtherCenter);

				return;
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			// �簢���� ������
			Point stdPoint = r->GetAbsolutePoint(i);

			// �簢���� �� �� ����
			Point recSide = r->GetAbsolutePoint((i + 1) % 4) - stdPoint;

			// ������ -> ���� �߽� ����
			Point stdToCircleCenter = center - stdPoint;

			// ���翵�� ������ ����
			double proj = Dot(recSide, stdToCircleCenter) / (r->GetLen() * r->GetLen());

			// �浹 ����
			Point colPoint = stdPoint + recSide * proj;

			// �浹 �������� ���� �߽ɱ����� �Ÿ�
			double distance = GetDistance(colPoint, center);

			if (proj >= 0 && proj <= 1 && distance < radius)
			{
				Point normal = (center - colPoint) / distance;

				double overlap = (distance - radius) * 0.5f;

				center = center - overlap * normal;

				Point newOtherCenter = r->GetCenter() + overlap * normal;
				r->SetCenter(newOtherCenter);

				return;
			}
		}
	}
}

void Circle2D::Draw(HDC hdc)
{
	Ellipse(hdc,
		(int)floor(center.x - radius + 0.5f),
		(int)floor(center.y - radius + 0.5f),
		(int)floor(center.x + radius + 0.5f), 
		(int)floor(center.y + radius + 0.5f)
	);
}
