#include "Circle2D.h"

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
		distance = (float)sqrt(pow(c->GetCenter().x - center.x, 2) + pow(c->GetCenter().y - center.y, 2));

		if (distance  <= c->GetRadius() + radius)
		{
			// ��� ���� (���� �߽� - ���� �߽�) �� ����ȭ
			float nx = (c->GetCenter().x - center.x) / distance;
			float ny = (c->GetCenter().y - center.y) / distance;

			// �븻�� ���� ���͸� ���ڷ�
			Bounce({ nx, ny }, {-ny, nx}, dir, other);

			// ��ĥ ��� ó��
			if (distance < c->GetRadius() + radius)
				Overlap(other);
		}
	}
}

void Circle2D::Overlap(Shape2D * other)
{
	Circle2D *c = dynamic_cast<Circle2D *>(other);

	if (c)
	{
		if (distance < radius + c->radius)
		{
			float overlap = (distance - radius - c->GetRadius()) * 0.5f;

			center.x -= overlap * (center.x - c->GetCenter().x) / distance;
			center.y -= overlap * (center.y - c->GetCenter().y) / distance;

			float targetCX = c->GetCenter().x + overlap * (center.x - c->GetCenter().x) / distance;
			float targetCY = c->GetCenter().y + overlap * (center.y - c->GetCenter().y) / distance;
		
			c->SetCenter(targetCX, targetCY);
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
