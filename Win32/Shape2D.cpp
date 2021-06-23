#include "Shape2D.h"

void Shape2D::Bounce(const Point & normal, const Point & tangent, Shape2D * other)
{
	// dir 내적 접선 벡터 
	float dpTan1 = dir.x * tangent.x + dir.y * tangent.y;
	float dpTan2 = other->GetDir().x * tangent.x + other->GetDir().y * tangent.y;

	// dir 내적 노멀 벡터
	float dpNorm1 = dir.x * normal.x + dir.y * normal.y;
	float dpNorm2 = other->GetDir().x * normal.x + other->GetDir().y * normal.y;

	//float m1 = (dpNorm1 * (mass - c->GetMass()) + 2.0f * c->GetMass() * dpNorm2) / (mass + c->GetMass());
	//float m2 = (dpNorm2 * (c->GetMass() - mass) + 2.0f * mass * dpNorm1) / (mass + c->GetMass());

	float m1 = dpNorm2;
	float m2 = dpNorm1;

	SetDir(tangent.x * dpTan1 + normal.x * m1, tangent.y * dpTan1 + normal.y * m1);
	other->SetDir(tangent.x * dpTan2 + normal.x * m2, tangent.y * dpTan2 + normal.y * m2);
}
