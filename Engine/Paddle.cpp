#include "Paddle.h"

Paddle::Paddle(float WidthInput, float HeightInput, Vec2 OriginPositionInput, Color ColorInput)
	:
	Rectangle(WidthInput, HeightInput, OriginPositionInput, ColorInput)
{
}

void Paddle::Update(const Keyboard& kbd, float DeltaTime)
{
	if (kbd.KeyIsPressed( VK_RIGHT ))
	{	
		const float RightSidePosition = Rectangle.OriginPosition.x + DeltaTime * PaddleMovingSpeed + Rectangle.Width;
		if(RightSidePosition > Graphics::ScreenWidth)
		{
			Rectangle.OriginPosition.x = Graphics::ScreenWidth - Rectangle.Width;
		}
		else 
		{
			Rectangle.OriginPosition.x = Rectangle.OriginPosition.x + DeltaTime * PaddleMovingSpeed;
		}
	}
	if (kbd.KeyIsPressed( VK_LEFT ))
	{	
		const float LeftSidePosition = Rectangle.OriginPosition.x - DeltaTime * PaddleMovingSpeed;
		if (LeftSidePosition < 0)
		{
			Rectangle.OriginPosition.x = 0;
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
