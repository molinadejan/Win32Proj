#pragma once

#include <windows.h>

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

// ÁÂÇ¥ ±¸Á¶Ã¼
struct Point
{
	float x, y;
};

void DrawGrid(HDC hdc, const Point &p, int colCnt, int rowCnt, int colGap, int rowGap);
void DrawCircle(HDC hdc, const Point &p, int radius);
void DrawSunflowerByRadius(HDC hdc, const Point &center, int radius, int leafRadius);
void DrawSunflowerByCount(HDC hdc, const Point &center, int radius, int cnt);
void DrawRectangle(HDC hdc, const Point &p, int width, int height);
void DrawStar(HDC hdc, const Point &center, const int radius, int degree);

Point GetIntersection(const Point &p1, const Point &p2, const Point &p3, const Point &p4, bool &check);

Point Rotate(const Point &center, const Point &p, const float radian);

float Rad2Deg(const float radian);
float Deg2Rad(const float degree);

float GetDistance(const Point &p1, const Point &p2);
float GetDistance(float p1x, float p1y, float p2x, float p2y);

#endif // !__GEOMETRY_H__