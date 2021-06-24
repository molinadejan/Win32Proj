#include "Shape2D.h"

void Shape2D::Bounce(const Point & normal, const Point & tangent, const Point& myDir, Shape2D * other)
{
	// dir 내적 접선 벡터 
	double dpTan1 = myDir.x * tangent.x + myDir.y * tangent.y;
	double dpTan2 = other->GetDir().x * tangent.x + other->GetDir().y * tangent.y;

	// dir 내적 노멀 벡터
	double dpNorm1 = myDir.x * normal.x + myDir.y * normal.y;
	double dpNorm2 = other->GetDir().x * normal.x + other->GetDir().y * normal.y;

	//double m1 = (dpNorm1 * (mass - c->GetMass()) + 2.0f * c->GetMass() * dpNorm2) / (mass + c->GetMass());
	//double m2 = (dpNorm2 * (c->GetMass() - mass) + 2.0f * mass * dpNorm1) / (mass + c->GetMass());

	double m1 = dpNorm2;
	double m2 = dpNorm1;

	SetDir(tangent.x * dpTan1 + normal.x * m1, tangent.y * dpTan1 + normal.y * m1);
	other->SetDir(tangent.x * dpTan2 + normal.x * m2, tangent.y * dpTan2 + normal.y * m2);
}
