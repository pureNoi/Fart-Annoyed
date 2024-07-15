#include "Paddle.h"

Paddle::Paddle(float WidthInput, float HeightInput, float PaddleMovingSpeedInput, Vec2 OriginPositionInput, Color ColorInput)
	:
	Rectangle(WidthInput, HeightInput, OriginPositionInput, ColorInput),
	PaddleMovingSpeed(PaddleMovingSpeedInput)
{
}

void Paddle::Update(const Keyboard& kbd, float DeltaTime, float WallThickness)
{
	if (kbd.KeyIsPressed( VK_RIGHT ))
	{	
		const float RightSidePosition = Rectangle.OriginPosition.x + DeltaTime * PaddleMovingSpeed + Rectangle.Width;
		if(RightSidePosition > Graphics::ScreenWidth - WallThickness)
		{
			Rectangle.OriginPosition.x = Graphics::ScreenWidth - Rectangle.Width - WallThickness;
		}
		else 
		{
			Rectangle.OriginPosition.x = Rectangle.OriginPosition.x + DeltaTime * PaddleMovingSpeed;
		}
	}
	if (kbd.KeyIsPressed( VK_LEFT ))
	{	
		const float LeftSidePosition = Rectangle.OriginPosition.x - DeltaTime * PaddleMovingSpeed;
		if (LeftSidePosition < WallThickness)
		{
			Rectangle.OriginPosition.x = WallThickness;
		}
		else 
		{
			Rectangle.OriginPosition.x = Rectangle.OriginPosition.x - DeltaTime * PaddleMovingSpeed;
		}
	}
}

float Paddle::GetOriginPositionX() const
{
	return Rectangle.OriginPosition.x;
}

float Paddle::GetOriginPositionY() const
{
	return Rectangle.OriginPosition.y;
}

float Paddle::GetWidth() const
{
	return Rectangle.Width;
}

float Paddle::GetHeight() const
{
	return Rectangle.Height;
}

Color Paddle::GetColor() const
{
	return Rectangle.RectangleColor;
}
