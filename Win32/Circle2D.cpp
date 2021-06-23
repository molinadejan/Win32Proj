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
		distance = (float)sqrt(pow(c->GetCenter().x - center.x, 2) + pow(c->GetCenter().y - center.y, 2));

		if (distance  <= c->GetRadius() + radius)
		{
			// 노멀 벡터 (원의 중심 - 원의 중심) 의 정규화
			float nx = (c->GetCenter().x - center.x) / distance;
			float ny = (c->GetCenter().y - center.y) / distance;

			// 접선 벡터 
			float tx = -ny;
			float ty = nx;

			// dir 내적 접선 벡터 
			float dpTan1 = dir.x * tx + dir.y * ty;
			float dpTan2 = c->GetDir().x * tx + c->GetDir().y * ty;

			// dir 내적 노멀 벡터
			float dpNorm1 = dir.x * nx + dir.y * ny;
			float dpNorm2 = c->GetDir().x * nx + c->GetDir().y * ny;

			//float m1 = (dpNorm1 * (mass - c->GetMass()) + 2.0f * c->GetMass() * dpNorm2) / (mass + c->GetMass());
			//float m2 = (dpNorm2 * (c->GetMass() - mass) + 2.0f * mass * dpNorm1) / (mass + c->GetMass());

			float m1 = dpNorm2;
			float m2 = dpNorm1;

			SetDir(tx * dpTan1 + nx * m1, ty * dpTan1 + ny * m1);
			c->SetDir(tx * dpTan2 + nx * m2, ty * dpTan2 + ny * m2);

			// 겹칠 경우 처리

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
