#include "Paddle.h"

Paddle::Paddle(float WidthInput, float HeightInput, float PaddleMovingSpeedInput, Vec2 OriginPositionInput, Color ColorInput)
	:
	Rectangle(WidthInput, HeightInput, OriginPositionInput, ColorInput),
	PaddleMovingSpeed(PaddleMovingSpeedInput)
{
}

void Paddle::Update(const Keyboard& kbd, float DeltaTime, Vec2 HorizonMovingRange)
{
	if (kbd.KeyIsPressed( VK_RIGHT ))
	{	
		const float RightSidePosition = Rectangle.OriginPosition.x + DeltaTime * PaddleMovingSpeed + Rectangle.Width;
		if(RightSidePosition > HorizonMovingRange.y/*Graphics::ScreenWidth - WallThickness*/)
		{
			Rectangle.OriginPosition.x = HorizonMovingRange.y - Rectangle.Width;
		}
		else 
		{
			Rectangle.OriginPosition.x = Rectangle.OriginPosition.x + DeltaTime * PaddleMovingSpeed;
		}
	}
	if (kbd.KeyIsPressed( VK_LEFT ))
	{	
		const float LeftSidePosition = Rectangle.OriginPosition.x - DeltaTime * PaddleMovingSpeed;
		if (LeftSidePosition < HorizonMovingRange.x/*WallThickness*/)
		{
			Rectangle.OriginPosition.x = HorizonMovingRange.x;
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
