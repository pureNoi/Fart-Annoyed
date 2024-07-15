#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "Graphics.h"
#include "Brick.h"
#include "Paddle.h"
#include <cmath>

class Ball 
{	
public:
	Ball(float RadiusInput, Vec2 CenterPositionInput, Vec2 VelocityInput, Color ColorInput);
	void Update(Brick& Brick, const Paddle& PlayerPaddle);
	bool DetectCollisionWithBoard();
	bool DetectCollisionWithPaddle(const Paddle& PlayerPaddle);
	bool DetectCollisionWithBrick(Brick& Brick);
	void BounceX();
	void BounceY();
	float GetCenterPositionX() const;
	float GetCenterPositionY() const;
	float GetRadius() const;
	Color GetColor() const;

private:
	float Radius;
	float SqrtRadius = std::sqrt(Radius);
	Vec2 CenterPosition;
	Vec2 Velocity;
	Color BallColor;
	bool GameIsOver = false;

};