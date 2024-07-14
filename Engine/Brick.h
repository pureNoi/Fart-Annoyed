#pragma once
//TestText
#include "Rectangle.h"

class Brick
{	
public:
	Brick() = default;
	Brick(float WidthInput, float HeightInput, Vec2 CenterPositionInput, Color ColorInput);
	void SetRectangleProperty(float WidthInput, float HeightInput, Vec2 CenterPositionInput, Color ColorInput);
	float GetOriginPositionX() const;
	float GetOriginPositionY() const;
	float GetWidth() const;
	float GetHeight() const;
	Color GetColor() const;

private:
	RectangleElement Rectangle;
};