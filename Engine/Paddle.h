#pragma once
#include "Rectangle.h"
#include "Keyboard.h"
#include "Graphics.h"

class Paddle 
{
public:
	Paddle(float WidthInput, float HeightInput, float PaddleMovingSpeedInput, Vec2 OriginPositionInput, Color ColorInput);
	void Update(const Keyboard& kbd, float DeltaTime, Vec2 HorizonMovingRange);
	float GetOriginPositionX() const;
	float GetOriginPositionY() const;
	float GetWidth() const;
	float GetHeight() const;
	Color GetColor() const;
private:
	RectangleElement Rectangle;
	float PaddleMovingSpeed;
};