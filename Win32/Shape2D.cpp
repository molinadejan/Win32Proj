#include "Shape2D.h"

void Shape2D::Bounce(const Point & normal, const Point& myDir, Shape2D * other)
{
	Point tangent = { -1 * normal.y, normal.x };

	// dir 내적 접선 벡터 
	double dpTan1 = Dot(myDir, tangent);          
	double dpTan2 = Dot(other->GetDir(), tangent);

	// dir 내적 노멀 벡터
	double dpNorm1 = Dot(myDir, normal);          
	double dpNorm2 = Dot(other->GetDir(), normal);

	//double m1 = (dpNorm1 * (mass - c->GetMass()) + 2.0f * c->GetMass() * dpNorm2) / (mass + c->GetMass());
	//double m2 = (dpNorm2 * (c->GetMass() - mass) + 2.0f * mass * dpNorm1) / (mass + c->GetMass());

	double m1 = dpNorm2;
	double m2 = dpNorm1;

	SetDir(tangent * dpTan1 + normal * m1);
	other->SetDir(tangent * dpTan2 + normal * m2);
}
