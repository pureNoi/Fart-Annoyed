#include "Ball.h"

Ball::Ball(float RadiusInput, Vec2 CenterPositionInput, Vec2 VelocityInput, Color ColorInput)
	:
	Radius(RadiusInput),
	CenterPosition(CenterPositionInput),
	Velocity(VelocityInput),
	BallColor(ColorInput)
{
}

void Ball::Update(Brick& Brick, const Paddle& PlayerPaddle)
{		
	if (!(DetectCollisionWithBoard() || DetectCollisionWithPaddle(PlayerPaddle)))
	{
		CenterPosition += Velocity;
	}
}

bool Ball::DetectCollisionWithBoard()
{
	const float TopSidePosition = CenterPosition.y + Velocity.y - Radius;
	const float BottomSidePosition = CenterPosition.y + Velocity.y + Radius;
	const float LeftSidePosition = CenterPosition.x + Velocity.x - Radius;
	const float RightSidePosition = CenterPosition.x + Velocity.x + Radius;

	if (TopSidePosition < 0)
	{
		CenterPosition.y = Radius;
		BounceY();
		return true;
	}
	else if (BottomSidePosition > Graphics::ScreenHeight)
	{
		CenterPosition.y = Graphics::ScreenHeight - Radius;
		BounceY();
		return true;
	}
	else if (LeftSidePosition < 0)
	{
		CenterPosition.x = Radius;
		BounceX();
		return true;
	}
	else if (RightSidePosition > Graphics::ScreenWidth)
	{
		CenterPosition.x = Graphics::ScreenWidth - Radius;
		BounceX();
		return true;
	}
	else 
	{
		return false;
	}
}

bool Ball::DetectCollisionWithPaddle(const Paddle& PlayerPaddle)
{	
	const float BallTopSidePosition = CenterPosition.y + Velocity.y - Radius;
	const float BallBottomSidePosition = CenterPosition.y + Velocity.y + Radius;
	const float BallLeftSidePosition = CenterPosition.x + Velocity.x - Radius;
	const float BallRightSidePosition = CenterPosition.x + Velocity.x + Radius;

	const float PaddleTopSidePosition = PlayerPaddle.GetOriginPositionY() - SqrtRadius;
	const float PaddleBottomSidePosition = PlayerPaddle.GetOriginPositionY() + PlayerPaddle.GetHeight() + SqrtRadius;
	const float PaddleLeftSidePosition = PlayerPaddle.GetOriginPositionX() - SqrtRadius;
	const float PaddleRightSidePosition = PlayerPaddle.GetOriginPositionX() + PlayerPaddle.GetWidth() + SqrtRadius;

	if (CenterPosition.y <= PaddleTopSidePosition
		&&
		BallBottomSidePosition >= PaddleTopSidePosition
		&&
		CenterPosition.x >= PaddleLeftSidePosition
		&&
		CenterPosition.x <= PaddleRightSidePosition)
	{	
		CenterPosition.y = PaddleTopSidePosition - Radius;
		BounceY();
		return true;
	}
	else if(CenterPosition.y >= PaddleBottomSidePosition
		&&
		BallTopSidePosition <= PaddleBottomSidePosition
		&&
		CenterPosition.x >= PaddleLeftSidePosition
		&&
		CenterPosition.x <= PaddleRightSidePosition)
	{
		CenterPosition.y = PaddleBottomSidePosition + Radius;
		BounceY();
		return true;
	}
	else if (CenterPosition.x <= PaddleLeftSidePosition
		&&
		BallRightSidePosition >= PaddleLeftSidePosition
		&&
		CenterPosition.y >= PaddleTopSidePosition
		&&
		CenterPosition.y <= PaddleBottomSidePosition)
	{
		CenterPosition.x = PaddleLeftSidePosition - Radius;
		BounceX();
		return true;
	}
	else if (CenterPosition.x >= PaddleRightSidePosition
		&&
		BallLeftSidePosition <= PaddleRightSidePosition
		&&
		CenterPosition.y >= PaddleTopSidePosition
		&&
		CenterPosition.y <= PaddleBottomSidePosition)
	{
		CenterPosition.x = PaddleRightSidePosition + Radius;
		BounceX();
		return true;
	}
	else
	{
		return false;
	}
}

void Ball::BounceX()
{
	Velocity.x *= -1;
}

void Ball::BounceY()
{
	Velocity.y *= -1;
}

float Ball::GetCenterPositionX() const
{
	return CenterPosition.x;
}

float Ball::GetCenterPositionY() const
{
	return CenterPosition.y;
}

float Ball::GetRadius() const
{
	return Radius;
}

Color Ball::GetColor() const
{
	return BallColor;
}


