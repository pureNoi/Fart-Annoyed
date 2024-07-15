/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	PlayerPaddle(PaddleWidth, PaddleHeight, PaddleMovingSpeed, Vec2(PaddleStartPositionX, PaddleStartPositionY), PaddleColor),
	PlayerBall(BallRadius, Vec2(BallStartPositionX, BallStartPositionY), Vec2(BallStartSpeedX, BallStartSpeedY), BallColor)
{
	for (int i = 0; i < BrickNum; i++)
	{	
		int IndexX = i % BricksRowNum;
		int IndexY = i / BricksRowNum;
		int ColorIndex = (i / BricksRowNum) % ColorsNum;
		float RectanglePositionX = (IndexX * BrickWidth) + BrickSpreadingAreaOffsetX;
		float RectanglePositionY = (IndexY * BrickHeight) + BrickSpreadingAreaOffsetY;
		Vec2 RectangleOriginPosition = Vec2(RectanglePositionX, RectanglePositionY);
		BrickArray[i].SetRectangleProperty(BrickWidth, BrickHeight, RectangleOriginPosition, ColorArray[ColorIndex]);
	}
}

void Game::DrawWall()
{
	gfx.DrawRect(0, 0, int(WallThickness), Graphics::ScreenHeight, WallColor);
	gfx.DrawRect(0, 0, Graphics::ScreenWidth, int(WallThickness), WallColor);
	gfx.DrawRect(Graphics::ScreenWidth - int(WallThickness), 0, Graphics::ScreenWidth, Graphics::ScreenHeight, WallColor);
}

void Game::DrawBrickArray()
{
	for (int i = 0; i < BrickNum; i++)
	{	
		if(!BrickArray[i].GetState())
		{
			const float Width = BrickArray[i].GetWidth();
			const float Height = BrickArray[i].GetHeight();
			const float OriginX = BrickArray[i].GetOriginPositionX();
			const float OriginY = BrickArray[i].GetOriginPositionY();

			gfx.DrawRect(int(OriginX), int(OriginY), int(Width + OriginX), int(Height + OriginY), Colors::Black);
			gfx.DrawRect(int(OriginX + 2.0f), int(OriginY + 2.0f), int(Width + OriginX - 2.0f), int(Height + OriginY - 2.0f), BrickArray[i].GetColor());
		}
	}
}

void Game::DrawPaddle()
{
	const float Width = PlayerPaddle.GetWidth();
	const float Height = PlayerPaddle.GetHeight();
	const float OriginX = PlayerPaddle.GetOriginPositionX();
	const float OriginY = PlayerPaddle.GetOriginPositionY();
	gfx.DrawRect(int(OriginX), int(OriginY), int(Width + OriginX), int(Height + OriginY), PlayerPaddle.GetColor());
}

void Game::DrawBall()
{
	gfx.DrawCircle(
		int(PlayerBall.GetCenterPositionX()),
		int(PlayerBall.GetCenterPositionY()),
		int(PlayerBall.GetRadius()),
		PlayerBall.GetColor()
	);
}


void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel(DeltaTime);
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float DeltaTime)
{
	if (!PlayerBall.GetState())
	{
		PlayerPaddle.Update(wnd.kbd, DeltaTime, WallThickness);
		bool IsBallCollidedWithBrick = false;
		for (int i = 0; i < BrickNum; i++)
		{
			PlayerBall.DetectCollisionWithBrick(BrickArray[i], DeltaTime);
		}
		PlayerBall.DetectCollisionWithBoard(WallThickness, DeltaTime);
		PlayerBall.DetectCollisionWithPaddle(PlayerPaddle, DeltaTime);
		PlayerBall.Update(DeltaTime);
	}
}

void Game::ComposeFrame()
{
	DrawWall();
	if(!PlayerBall.GetState())
	{
		DrawBrickArray();
		DrawPaddle();
		DrawBall();
	}
}
