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
	PlayerPaddle(PaddleWidth, PaddleHeight, Vec2(PaddleStartPositionX, PaddleStartPositionY), PaddleColor),
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

			gfx.DrawRect(OriginX, OriginY, Width + OriginX, Height + OriginY, Colors::Black);
			gfx.DrawRect(OriginX + 2, OriginY + 2, Width + OriginX - 2, Height + OriginY - 2, BrickArray[i].GetColor());
		}
	}
}

void Game::DrawPaddle()
{
	const float Width = PlayerPaddle.GetWidth();
	const float Height = PlayerPaddle.GetHeight();
	const float OriginX = PlayerPaddle.GetOriginPositionX();
	const float OriginY = PlayerPaddle.GetOriginPositionY();
	gfx.DrawRect(OriginX, OriginY, Width + OriginX, Height + OriginY, PlayerPaddle.GetColor());
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
	PlayerPaddle.Update(wnd.kbd, DeltaTime);
	bool test = false;
	for (int i = 0; i < BrickNum; i++)
	{
		if (PlayerBall.DetectCollisionWithBrick(BrickArray[i]))
		{
			test = true;
			break;
		}
	}
	if (!(PlayerBall.DetectCollisionWithBoard() || PlayerBall.DetectCollisionWithPaddle(PlayerPaddle) || test))
	{
		PlayerBall.Update();
	}
}

void Game::ComposeFrame()
{
	DrawBrickArray();
	DrawPaddle();
	DrawBall();
}
