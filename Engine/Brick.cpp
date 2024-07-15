#include "Brick.h"

Brick::Brick(float WidthInput, float HeightInput, Vec2 OriginPositionInput, Color ColorInput)
	:
	Rectangle(WidthInput, HeightInput, OriginPositionInput, ColorInput)
{
}

void Brick::SetRectangleProperty(float WidthInput, float HeightInput, Vec2 OriginPositionInput, Color ColorInput)
{
	Rectangle.Width = WidthInput;
	Rectangle.Height = HeightInput;
	Rectangle.OriginPosition = OriginPositionInput;
	Rectangle.RectangleColor = ColorInput;
}

float Brick::GetOriginPositionX() const
{
	return Rectangle.OriginPosition.x;
}

float Brick::GetOriginPositionY() const
{
	return Rectangle.OriginPosition.y;
}

float Brick::GetWidth() const
{
	return Rectangle.Width;
}

float Brick::GetHeight() const
{
	return Rectangle.Height;
}

bool Brick::GetState() const
{
	return IsDestroyed;
}

Color Brick::GetColor() const
{
	return Rectangle.RectangleColor;
}
