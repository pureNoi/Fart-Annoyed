#include "Ball.h"

Ball::Ball(float RadiusInput, Vec2 CenterPositionInput, Vec2 VelocityInput, Color ColorInput)
	:
	Radius(RadiusInput),
	CenterPosition(CenterPositionInput),
	Velocity(VelocityInput),
	BallColor(ColorInput)
{
}

void Ball::Update()
{		
	CenterPosition += Velocity;
}

bool Ball::DetectCollisionWithBoard()
{
	const float TopSidePosition = CenterPosition.y + Velocity.y - Radius;
	const float BottomSidePosition = CenterPosition.y + Velocity.y + Radius;
	const float LeftSidePosition = CenterPosition.x + Velocity.x - Radius;
	const float RightSidePosition = CenterPosition.x + Velocity.x + Radius;

	if (TopSidePosition <= 0)
	{
		CenterPosition.y = Radius;
		BounceY();
		return true;
	}
	else if (BottomSidePosition >= Graphics::ScreenHeight)
	{
		CenterPosition.y = Graphics::ScreenHeight - Radius;
		BounceY();
		return true;
	}
	else if (LeftSidePosition <= 0)
	{
		CenterPosition.x = Radius;
		BounceX();
		return true;
	}
	else if (RightSidePosition >= Graphics::ScreenWidth)
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
	const float PaddleBottomSidePosition = PlayerPaddle.GetOriginPositionY() + PlayerPaddle.GetHeight();
	const float PaddleLeftSidePosition = PlayerPaddle.GetOriginPositionX() - SqrtRadius;
	const float PaddleRightSidePosition = PlayerPaddle.GetOriginPositionX() + PlayerPaddle.GetWidth();

	if (CenterPosition.y <= PaddleTopSidePosition
		&&
		BallBottomSidePosition >= PaddleTopSidePosition
		&&
		CenterPosition.x >= PaddleLeftSidePosition - SqrtRadius
		&&
		CenterPosition.x <= PaddleRightSidePosition + SqrtRadius)
	{	
		CenterPosition.y = PaddleTopSidePosition - Radius;
		BounceY();
		return true;
	}
	else if(CenterPosition.y >= PaddleBottomSidePosition
		&&
		BallTopSidePosition <= PaddleBottomSidePosition
		&&
		CenterPosition.x >= PaddleLeftSidePosition - SqrtRadius
		&&
		CenterPosition.x <= PaddleRightSidePosition + SqrtRadius)
	{
		CenterPosition.y = PaddleBottomSidePosition + Radius;
		BounceY();
		return true;
	}
	else if (CenterPosition.x <= PaddleLeftSidePosition
		&&
		BallRightSidePosition >= PaddleLeftSidePosition
		&&
		CenterPosition.y >= PaddleTopSidePosition - SqrtRadius
		&&
		CenterPosition.y <= PaddleBottomSidePosition + SqrtRadius)
	{
		CenterPosition.x = PaddleLeftSidePosition - Radius;
		BounceX();
		return true;
	}
	else if (CenterPosition.x >= PaddleRightSidePosition
		&&
		BallLeftSidePosition <= PaddleRightSidePosition
		&&
		CenterPosition.y >= PaddleTopSidePosition - SqrtRadius
		&&
		CenterPosition.y <= PaddleBottomSidePosition + SqrtRadius)
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

bool Ball::DetectCollisionWithBrick(Brick& Brick)
{
	if (Brick.GetState())
	{
		return false;
	}

	const float BallTopSidePosition = CenterPosition.y + Velocity.y - Radius;
	const float BallBottomSidePosition = CenterPosition.y + Velocity.y + Radius;
	const float BallLeftSidePosition = CenterPosition.x + Velocity.x - Radius;
	const float BallRightSidePosition = CenterPosition.x + Velocity.x + Radius;

	const float BrickTopSidePosition = Brick.GetOriginPositionY() - SqrtRadius;
	const float BrickBottomSidePosition = Brick.GetOriginPositionY() + Brick.GetHeight();
	const float BrickLeftSidePosition = Brick.GetOriginPositionX() - SqrtRadius;
	const float BrickRightSidePosition = Brick.GetOriginPositionX() + Brick.GetWidth();

	if (CenterPosition.y <= BrickTopSidePosition
		&&
		BallBottomSidePosition >= BrickTopSidePosition
		&&
		CenterPosition.x >= BrickLeftSidePosition - SqrtRadius
		&&
		CenterPosition.x <= BrickRightSidePosition + SqrtRadius)
	{
		CenterPosition.y = BrickTopSidePosition - Radius;
		BounceY();
		Brick.DestroySelf();
		return true;
	}
	else if (CenterPosition.y >= BrickBottomSidePosition
		&&
		BallTopSidePosition <= BrickBottomSidePosition
		&&
		CenterPosition.x >= BrickLeftSidePosition - SqrtRadius
		&&
		CenterPosition.x <= BrickRightSidePosition + SqrtRadius)
	{
		CenterPosition.y = BrickBottomSidePosition + Radius;
		BounceY();
		Brick.DestroySelf();
		return true;
	}
	else if (CenterPosition.x <= BrickLeftSidePosition
		&&
		BallRightSidePosition >= BrickLeftSidePosition
		&&
		CenterPosition.y >= BrickTopSidePosition - SqrtRadius
		&&
		CenterPosition.y <= BrickBottomSidePosition + SqrtRadius)
	{
		CenterPosition.x = BrickLeftSidePosition - Radius;
		BounceX();
		Brick.DestroySelf();
		return true;
	}
	else if (CenterPosition.x >= BrickRightSidePosition
		&&
		BallLeftSidePosition <= BrickRightSidePosition
		&&
		CenterPosition.y >= BrickTopSidePosition - SqrtRadius
		&&
		CenterPosition.y <= BrickBottomSidePosition + SqrtRadius)
	{
		CenterPosition.x = BrickRightSidePosition + Radius;
		BounceX();
		Brick.DestroySelf();
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


