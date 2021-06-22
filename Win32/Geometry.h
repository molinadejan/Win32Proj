#pragma once

#include <windows.h>

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

void DrawGrid(HDC hdc, const POINT &p, int colCnt, int rowCnt, int colGap, int rowGap);
void DrawCircle(HDC hdc, const POINT &p, int radius);
void DrawSunflowerByRadius(HDC hdc, const POINT &center, int radius, int leafRadius);
void DrawSunflowerByCount(HDC hdc, const POINT &center, int radius, int cnt);
void DrawRectangle(HDC hdc, const POINT &p, int width, int height);
void DrawStar(HDC hdc, const POINT &center, const int radius, int degree);

POINT GetIntersection(const POINT &p1, const POINT &p2, const POINT &p3, const POINT &p4, bool &check);

POINT Rotate(const POINT &center, const POINT &p, const double radian);

double Rad2Deg(const double radian);
double Deg2Rad(const double degree);

#endif // !__GEOMETRY_H__