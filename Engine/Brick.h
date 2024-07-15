#pragma once
#include "Rectangle.h"

class Brick
{	
public:
	Brick() = default;
	Brick(float WidthInput, float HeightInput, Vec2 OriginPositionInput, Color ColorInput);
	void SetRectangleProperty(float WidthInput, float HeightInput, Vec2 CenterPositionInput, Color ColorInput);
	void DestroySelf();
	float GetOriginPositionX() const;
	float GetOriginPositionY() const;
	float GetWidth() const;
	float GetHeight() const;
	bool GetState() const;
	Color GetColor() const;

private:
	RectangleElement Rectangle;
	bool IsDestroyed = false;
};