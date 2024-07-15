#include "Ball.h"

Ball::Ball(float RadiusInput, Vec2 CenterPositionInput, Vec2 VelocityInput, Color ColorInput)
	:
	Radius(RadiusInput),
	CenterPosition(CenterPositionInput),
	Velocity(VelocityInput),
	BallColor(ColorInput)
{
}

void Ball::Update(float DeltaTime)
{			
	CenterPosition += Velocity * DeltaTime;
}

void Ball::DetectCollisionWithBoard(float WallThickness, float DeltaTime)
{
	const float BallTopSidePosition = CenterPosition.y + Velocity.y * DeltaTime - Radius;
	const float BallBottomSidePosition = CenterPosition.y + Velocity.y * DeltaTime + Radius;
	const float BallLeftSidePosition = CenterPosition.x + Velocity.x * DeltaTime - Radius;
	const float BallRightSidePosition = CenterPosition.x + Velocity.x * DeltaTime + Radius;

	if (BallTopSidePosition <= WallThickness)
	{
		CenterPosition.y = Radius + WallThickness;
		BounceY();
	}
	else if (BallBottomSidePosition >= Graphics::ScreenHeight)
	{
		CenterPosition.y = Graphics::ScreenHeight - Radius - WallThickness;
		BounceY();
		GameIsOver = true;
	}
	else if (BallLeftSidePosition <= WallThickness)
	{
		CenterPosition.x = Radius + WallThickness;
		BounceX();
	}
	else if (BallRightSidePosition >= Graphics::ScreenWidth - WallThickness)
	{
		CenterPosition.x = Graphics::ScreenWidth - Radius - WallThickness;
		BounceX();
	}
}

void Ball::DetectCollisionWithPaddle(const Paddle& PlayerPaddle, float DeltaTime)
{	
	const float BallTopSidePosition = CenterPosition.y + Velocity.y * DeltaTime - Radius;
	const float BallBottomSidePosition = CenterPosition.y + Velocity.y * DeltaTime + Radius;
	const float BallLeftSidePosition = CenterPosition.x + Velocity.x * DeltaTime - Radius;
	const float BallRightSidePosition = CenterPosition.x + Velocity.x * DeltaTime + Radius;

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
	}
}

void Ball::DetectCollisionWithBrick(Brick& Brick, float DeltaTime)
{
	if (!Brick.GetState())
	{

		const float BallTopSidePosition = CenterPosition.y + Velocity.y * DeltaTime - Radius;
		const float BallBottomSidePosition = CenterPosition.y + Velocity.y * DeltaTime + Radius;
		const float BallLeftSidePosition = CenterPosition.x + Velocity.x * DeltaTime - Radius;
		const float BallRightSidePosition = CenterPosition.x + Velocity.x * DeltaTime + Radius;

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
		}
	}
}

bool Ball::GetState() const
{
	return GameIsOver;
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


