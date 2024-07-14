#pragma once
#include "Vec2.h"
#include "Colors.h"

class RectangleElement
{	
public:
	RectangleElement() = default;
	RectangleElement(float WidthInput, float HeightInput, Vec2 OriginPositionInput, Color ColorInput);

public:
	float Width;
	float Height;
	Vec2 OriginPosition;
	Color RectangleColor;
};